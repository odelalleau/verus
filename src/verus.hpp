#ifndef VERUS_H_
#define VERUS_H_

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/time.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>

#ifndef __ANDROID__
#include <atomic>
#include <queue>
#include <map>

// ALGLIB library
#include "../lib/alglib/src/ap.h"
#include "../lib/alglib/src/interpolation.h"
using namespace alglib;

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/assign/std/vector.hpp>

#endif

// VERUS PARAMETERS
#define  MTU 1448
#define  VERUS_M_DECREASE 0.7
#define  CURVE_TIMER 1e6  // timer in microseconds, how often do we update the curve
#define  EPOCH 5e3 // Verus epoch in microseconds
#define  DELTA1 1.0 // delta decrease
#define  DELTA2 2.0 // delta increase
#define  VERUS_R 6.0 // verus ratio of Dmax/Dmin
#define	 SS_EXIT_THRESHOLD 500.0
#define  SS_INIT_TIMEOUT 1000.0
#define  MAX_TIMEOUT 1000.0
#define  MIN_TIMEOUT 150.0
#define  MISSING_PKT_EXPIRY 150.0
#define  MAX_W_DELAY_CURVE 40000

typedef struct __attribute__((packed, aligned(2))) m {
  int payloadlength;
  int ss_id;
  unsigned long long seq;
  long long w;
  long long seconds;
  long long millis;
} verus_header;

typedef struct __attribute__((packed, aligned(2))) n {
  verus_header header;
  char * data;
} verus_packet;

typedef struct {
  long long w;
  struct timeval time;
} mapEntry;

void* delayProfile_thread (void *arg);
void restartSlowStart(void);
double ewma (double vals, double delay, double alpha);
verus_packet *udp_pdu_init(int seq, unsigned int PACKETSIZE, int w, int ssId);

#endif /* VERUS_H_ */
