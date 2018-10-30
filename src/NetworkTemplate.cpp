//============================================================================
// Name        : AirPortMusic.cpp
// Author      : Jon Dellaria
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include <DLog.h>

#include <unistd.h>


#include "client_http.hpp"
#include "server_http.hpp"
// Added for the json-example
#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

// Added for the default_resource example
#include <algorithm>
#include <boost/filesystem.hpp>
#include <fstream>
#include <vector>
#ifdef HAVE_OPENSSL
#include "crypto.hpp"
#endif


#include "UDPServer.h"
#include "APMusic.h"

#include "configurationFile.h"


int main_event_handler();
int eventHandler();
int configApp();

using namespace std;
// Added for the json-example:
using namespace boost::property_tree;

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

int songFD = 0;
DLog myLog;

int FDflags;

extern int playAutomatic;

#define SERVER_PORT 5000
#define DATA_GRAM_SERVER_PORT 1234
#define HTTP_SERVER_PORT 8080

#define GET_BIGENDIAN_INT(x) (*(__u8*)(x)<<24)|(*((__u8*)(x)+1)<<16)|(*((__u8*)(x)+2)<<8)|(*((__u8*)(x)+3))

typedef enum playActions {
	PLAY_ACTION_STOP = 0,
	PLAY_ACTION_PAUSE,
	PLAY_ACTION_PLAY,
	PLAY_ACTION_QUIT,
	PLAY_ACTION_EXIT,
	PLAY_ACTION_VOLUME,
	PLAY_ACTION_NEXTALBUM,
	PLAY_ACTION_NEXTSONG,
	PLAY_ACTION_UPDATE,
	PLAY_ACTION_NORMAL,
	PLAY_ACTION_PLAY_TILL_END,
} playActions;

typedef enum finishSongActions {
	NETWORK_ACTION_CONNECT = 0,
	NETWORK_ACTION_DISCONNECT,
	NETWORK_ACTION_NORMAL,
	NETWORK_ACTION_WAIT,
} NetworkActions;

typedef enum applicationActions {
	APPLICATION_ACTION_MANUAL = 0,
	APPLICATION_ACTION_CONTINUOUS,
} ApplicationActions;


class ApplicationModes {
public:
	ApplicationModes();
	virtual ~ApplicationModes();

	void setPlayMode(playActions mode);
	int getPlayMode();

	void setNetworkMode(NetworkActions mode);
	int getNetworkMode();

	void setManual();
	void setContinuous();
	int getApplicationMode();

	ApplicationActions applicationMode = APPLICATION_ACTION_MANUAL;
	playActions playMode = PLAY_ACTION_PLAY;
	NetworkActions networkMode = NETWORK_ACTION_DISCONNECT;

};


playActions playMode = PLAY_ACTION_PLAY;
playActions exitMode = PLAY_ACTION_PLAY;
NetworkActions networkMode = NETWORK_ACTION_DISCONNECT;

configurationFile myConfig;

ApplicationModes myAppModes;

UDPServer dataGramServer;



int main(int argc, char* const argv[])
{
//	int dataGramPort=DATA_GRAM_SERVER_PORT;


	int returnValue;
	string message;
	char ibuffer [33];


	if (argc == 2) // if there is an argument, then assume it is the configuration file
	{
		myConfig.getConfiguration(argv[1]);
	}
	else //otherwise assume there is a file in the default with the name "config.conf"
	{
		myConfig.getConfiguration("config.xml");
	}

	configApp();

	dataGramServer.Start(DATA_GRAM_SERVER_PORT);

	HttpServer server;
	server.config.port =  HTTP_SERVER_PORT;

	server.resource["^/status"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
	stringstream stream;
	string json_string = "{\"firstName\": \"John\",\"lastName\": \"Smith\",\"age\": 25}";
	string json_status_string;

	stream << "{";
	stream << "exitMode: " << exitMode << ",";
	stream << "playMode: " << playMode << ",";
	stream << "networkMode: " << networkMode;
	stream << "}";

//	stream << json_string;

	response->write(stream);
	};

	// GET-example for the path /info
	// Responds with request-information
	server.resource["^/info$"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
	stringstream stream;
	stream << "<h1>Request from " << request->remote_endpoint_address() << ":" << request->remote_endpoint_port() << "</h1>";

	stream << request->method << " " << request->path << " HTTP/" << request->http_version;

	stream << "<h2>Query Fields</h2>";
	auto query_fields = request->parse_query_string();
	for(auto &field : query_fields)
	{
		stream << field.first << ": " << field.second << "<br>";
	}

	stream << "<h2>Header Fields</h2>";
	for(auto &field : request->header)
	{
		stream << field.first << ": " << field.second << "<br>";
	}

	response->write(stream);
	};


  server.on_error = [](shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code & /*ec*/) {
    // Handle errors here
    // Note that connection timeouts will also call this handle with ec set to SimpleWeb::errc::operation_canceled
  };

  thread server_thread([&server]() {
    // Start server
    server.start();
  });

	while (exitMode != PLAY_ACTION_EXIT)
	{
//		playMode = PLAY_ACTION_PLAY;
		myAppModes.setPlayMode (PLAY_ACTION_PLAY);
		myAppModes.setNetworkMode(NETWORK_ACTION_DISCONNECT);
//		networkMode = NETWORK_ACTION_DISCONNECT;
		message = "airportAddress is: ";
		message.append(myConfig.airportAddress + "\n");
		myLog.print(logWarning, message);


		while (myAppModes.getPlayMode() != PLAY_ACTION_QUIT)
		{
			message = __func__;
			message.append(": Wile Loop - ");
			message.append("networkMode = ");
			sprintf(ibuffer, "%d", networkMode);
			message.append(ibuffer);
			sprintf(ibuffer, "%d", playMode);
			message.append("playMode = ");
			message.append(ibuffer);
			myLog.print(logDebug, message);

			returnValue = eventHandler();
		}
		message = __func__;
		message.append(": AirportTalk closing all connections and resting for 5 seconds.");
		myLog.print(logWarning, message);

	}
//	server_thread.join();
	server_thread.detach();
	server.stop();
	dataGramServer.Close();
	message = __func__;
	message.append(": AirportTalk exiting Normally");
	myLog.print(logWarning, message);
}




#define MAIN_EVENT_TIMEOUT 3 // sec unit


int configApp()
{
	string message;

	myLog.logFileName = myConfig.logFileName;
	myLog.printFile = myConfig.logPrintFile;
	myLog.printScreen = myConfig.logPrintScreen;
	myLog.printTime = myConfig.logPrintTime;

	if (myConfig.logValue.find("logDebug")!=string::npos)
	{
		myLog.logValue = logDebug;
		message = "myLog.logValue = logDebug";
		myLog.print(logInformation, message);
	}
	if (myConfig.logValue.find("logInformation")!=string::npos)
	{
		myLog.logValue = logInformation;
		message = "myLog.logValue = logInformation";
		myLog.print(logInformation, message);
	}
	if (myConfig.logValue.find("logWarning")!=string::npos)
	{
		myLog.logValue = logWarning;
		message = "myLog.logValue = logWarning";
		myLog.print(logInformation, message);
	}
	if (myConfig.logValue.find("logError")!=string::npos)
	{
		myLog.logValue = logError;
		message = "myLog.logValue = logError";
		myLog.print(logInformation, message);
	}
	return (1);
}

int eventHandler()
{
	int n;
	int iVolume;
	char buffer[1024];
	struct sockaddr_in from;
	char *ps=NULL;
	int returnValue = PLAY_ACTION_NORMAL;
	string message;

//	playMode = PLAY_ACTION_PLAY;
	bzero(buffer,1024);

	n = dataGramServer.GetMessage( buffer);
	if (n > 0)
	{
		if(strstr(buffer,"quit") != NULL )
		{
			playMode = PLAY_ACTION_QUIT;
			myAppModes.setPlayMode (PLAY_ACTION_QUIT);
			message = __func__;
			message.append(": Play Quit Signal Received");
			myLog.print(logWarning, message);
		}
		else if(strstr(buffer,"pause") != NULL )
		{
			playMode = PLAY_ACTION_PAUSE;
			myAppModes.setPlayMode (PLAY_ACTION_PAUSE);
			message = __func__;
			message.append(": Play Pause Signal Received");
			myLog.print(logWarning, message);
		}
		else if(strstr(buffer,"playautomatic") != NULL )
		{

			networkMode = NETWORK_ACTION_CONNECT;
			myAppModes.setNetworkMode (NETWORK_ACTION_CONNECT);

			playMode = PLAY_ACTION_PLAY;
			myAppModes.setPlayMode (PLAY_ACTION_PLAY);
			message = __func__;
			message.append(": Play Automatic Signal Received");
			myLog.print(logWarning, message);
		}
		else if(strstr(buffer,"playmanual") != NULL )
		{

			message = __func__;
			message.append(": Play Manual Signal Received");
			myLog.print(logWarning, message);
		}
		else if(strstr(buffer,"stop") != NULL )
		{
			playMode = PLAY_ACTION_STOP;
			myAppModes.setPlayMode (PLAY_ACTION_STOP);
			message = __func__;
			message.append(": Play Stop Signal Received");
			myLog.print(logWarning, message);
		}
		else if(strstr(buffer,"play") != NULL )
		{
			playMode = PLAY_ACTION_PLAY;
			myAppModes.setPlayMode (PLAY_ACTION_PLAY);
			networkMode = NETWORK_ACTION_CONNECT;
			myAppModes.setNetworkMode (NETWORK_ACTION_CONNECT);

			message = __func__;
			message.append(": Play Play Signal Received");
			myLog.print(logWarning, message);
		}
		else if(strstr(buffer,"exit") != NULL )
		{
			playMode = PLAY_ACTION_QUIT;
			myAppModes.setPlayMode (PLAY_ACTION_QUIT);
			exitMode = PLAY_ACTION_EXIT;

			message = __func__;
			message.append(": Exit Signal Received");
			myLog.print(logWarning, message);
		}

		else if( (ps = strstr(buffer,"volume")) != NULL )
		{
			iVolume = atoi(ps+7);
			message = __func__;
			message.append(": Volume Signal Received with a value of:");
			message.append(ps+7);
			myLog.print(logWarning, message);

		}
		else if(strstr(buffer,"nextalbum") != NULL )
		{
			playMode = PLAY_ACTION_NEXTALBUM;
			myAppModes.setPlayMode (PLAY_ACTION_NEXTALBUM);

			message = __func__;
			message.append(": Next Album Signal Received");
			myLog.print(logWarning, message);
		}
		else if(strstr(buffer,"nextsong") != NULL ) // next is for going to the next song via the web site... without finishing the song.
		{
			playMode = PLAY_ACTION_NEXTSONG;
			myAppModes.setPlayMode (PLAY_ACTION_NEXTSONG);
			returnValue = PLAY_ACTION_NEXTSONG;

			message = __func__;
			message.append(": Next Song Signal Received");
			myLog.print(logWarning, message);
		}
		else if(strstr(buffer,"next") != NULL )// next is for going to the next song naturally.
		{
			playMode = PLAY_ACTION_NEXTSONG;
			myAppModes.setPlayMode (PLAY_ACTION_NEXTSONG);
			returnValue = PLAY_ACTION_NEXTSONG;
			message = __func__;
			message.append(": Next (Song) Signal Received");
			myLog.print(logWarning, message);
		}

		else if(strstr(buffer,"update") != NULL )
		{
//			playMode = PLAY_ACTION_UPDATE;
		}
	}
	usleep(1000); // let other processes have the CPU for 1000 microseconds

	return (returnValue);
}

ApplicationModes::ApplicationModes() {
	// TODO Auto-generated constructor stub

}

ApplicationModes::~ApplicationModes() {
	// TODO Auto-generated destructor stub
}

void ApplicationModes::setPlayMode(playActions mode) {
	playMode = mode;
}

int ApplicationModes::getPlayMode() {
	return(playMode);
}


void ApplicationModes::setNetworkMode(NetworkActions mode) {
	networkMode = mode;
}

int ApplicationModes::getNetworkMode() {
	return(networkMode);
}


void ApplicationModes::setManual() {
	applicationMode = APPLICATION_ACTION_MANUAL;
}

void ApplicationModes::setContinuous() {
	applicationMode = APPLICATION_ACTION_CONTINUOUS;
}


int ApplicationModes::getApplicationMode() {
	return(applicationMode);
}
