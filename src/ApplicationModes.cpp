/*
 * UDPServer.cpp
 *
 *  Created on: Oct 22, 2018
 *      Author: jdellaria
 */


#include <stdio.h>
#include <stdlib.h>

#include "ApplicationModes.h"




ApplicationModes::ApplicationModes() {
	// TODO Auto-generated constructor stub

}

ApplicationModes::~ApplicationModes() {
	// TODO Auto-generated destructor stub
}

void ApplicationModes::setPlayMode(playActions mode) {
	playMode = mode;
}

playActions ApplicationModes::getPlayMode() {
	return(playMode);
}


void ApplicationModes::setNetworkMode(networkActions mode) {
	networkMode = mode;
}

networkActions ApplicationModes::getNetworkMode() {
	return(networkMode);
}


void ApplicationModes::setManual() {
	applicationMode = APPLICATION_ACTION_MANUAL;
}

void ApplicationModes::setContinuous() {
	applicationMode = APPLICATION_ACTION_CONTINUOUS;
}


applicationActions ApplicationModes::getApplicationMode() {
	return(applicationMode);
}