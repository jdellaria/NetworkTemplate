/*
 * APTalk.h
 *
 *  Created on: Feb 17, 2010
 *      Author: jdellaria
 */

#ifndef APTALK_H_
#define APTALK_H_
#define SLEEP_SEC(val) sleep(val)
#define SLEEP_MSEC(val) usleep(val*1000)
#define SLEEP_USEC(val) usleep(val)

#ifdef USE_SYSLOG
#include <syslog.h>
#define ERRMSG(args...) syslog(LOG_ERR, args)
#define INFMSG(args...) syslog(LOG_INFO, args)
#define DBGMSG(args...) syslog(LOG_DEBUG, args)
#else
#define ERRMSG(args...) fprintf(stderr,"ERR: " args)
#define INFMSG(args...) fprintf(stderr,"INFO: " args)
#define DBGMSG(args...) fprintf(stderr,"DBG: " args)
#endif

#define DEFAULT_SAMPLE_RATE 44100
#define MAX_SAMPLES_IN_CHUNK 4096

int read_line(int fd, char *line, int maxlen, int timeout, int no_poll);

#endif /* APTALK_H_ */
