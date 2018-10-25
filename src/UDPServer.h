/*
 * TCPSocket.h
 *
 *  Created on: Apr 6, 2010
 *      Author: jdellaria
 */

#ifndef UDPSERVER_H_
#define UDPSERVER_H_

#include <asm/types.h>

class UDPServer {
public:
	UDPServer();
	virtual ~UDPServer();

	int Start(int portNumber);
	int GetMessage(char *buffer);
	int SendMessage(char *buffer);
	int Close();

	int dataGramPort;
	struct sockaddr_in serverAddress;
	struct sockaddr_in fromAddress;
	int dataGramSocket;
};

#endif /* UDPSERVER_H_ */
