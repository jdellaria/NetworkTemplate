/*
 * configurationFile.h
 *
 *  Created on: Sep 10, 2009
 *      Author: jdellaria
 */

#ifndef CONFIGURATIONFILE_H_
#define CONFIGURATIONFILE_H_
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <fstream>


class configurationFile {
public:
	configurationFile();
	virtual ~configurationFile();

	void help(char *);
	int getConfiguration(char *);

	std::string airportAddress;
	std::string logFileName;
	std::string logValue;
	bool logPrintScreen;
	bool logPrintFile;
	bool logPrintTime;
};

#endif /* CONFIGURATIONFILE_H_ */
