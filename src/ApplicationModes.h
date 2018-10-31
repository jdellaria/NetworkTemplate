/*
 * ApplicationModes.h
 *
 *  Created on: Oct 31, 2018
 *      Author: jdellaria
 */

#ifndef APPLICATIONMODES_H_
#define APPLICATIONMODES_H_



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
} networkActions;

typedef enum applicationActions {
	APPLICATION_ACTION_MANUAL = 0,
	APPLICATION_ACTION_CONTINUOUS,
} applicationActions;


class ApplicationModes {
public:
	ApplicationModes();
	virtual ~ApplicationModes();

	void setPlayMode(playActions mode);
	playActions getPlayMode();

	void setNetworkMode(networkActions mode);
	networkActions getNetworkMode();

	void setManual();
	void setContinuous();
	applicationActions getApplicationMode();

	applicationActions applicationMode = APPLICATION_ACTION_MANUAL;
	playActions playMode = PLAY_ACTION_PLAY;
	networkActions networkMode = NETWORK_ACTION_DISCONNECT;

};


#endif /* APPLICATIONMODES_H_ */
