/*
 * UDPServer.cpp
 *
 *  Created on: Oct 22, 2018
 *      Author: jdellaria
 */

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

#include "UDPServer.h"
#include "APMusic.h"

#include "configurationFile.h"

extern DLog myLog;

UDPServer::UDPServer() {
	// TODO Auto-generated constructor stub

}

UDPServer::~UDPServer() {
	// TODO Auto-generated destructor stub
}


int UDPServer::Start(int portNumber)
{
	int length;
	struct sockaddr_in socketAddress;
	string message;

	dataGramPort = portNumber;
	dataGramSocket=socket(AF_INET, SOCK_DGRAM, 0);
	if (dataGramSocket < 0)
	{
		message = __func__;
		message.append(": Error opening socket");
		myLog.print(logWarning, message);

	}

	length = sizeof(struct sockaddr_in);
	bzero(&socketAddress, length );
	socketAddress.sin_family=AF_INET;
	socketAddress.sin_addr.s_addr=INADDR_ANY;
	socketAddress.sin_port=htons(dataGramPort);

	if (bind(dataGramSocket, (struct sockaddr *) &socketAddress, length) < 0)
	{
		message = __func__;
		message.append(": Error binding socket");
		myLog.print(logWarning, message);
	}

	return (dataGramSocket);
}

int UDPServer::GetMessage(char *buffer)
{
	int n;
	struct sockaddr socketAddress;
	socklen_t fromlen = sizeof(struct sockaddr_in);

	n = recvfrom(dataGramSocket, buffer, 1024, MSG_DONTWAIT, &socketAddress, &fromlen);
	return(n);

}

int UDPServer::Close()
{
	close (dataGramSocket);

}
