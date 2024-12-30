#ifndef __THREADS_H__
#define __THREADS_H__

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct payload_s {
	pthread_mutex_t mutex;
	char *txt;
	int txtlen;
} payload_t;

#endif
