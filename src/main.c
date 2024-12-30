#include "../include/threads.h"

#define TEXT "This is the payload"

payload_t payload;

void	*routine(void *args) {
	payload_t *payload = args;
	pthread_t tid = pthread_self();

	pthread_mutex_lock(&payload->mutex);

	printf("HERE in thread 1, id: %ld\n", tid);
	write(0, "++++++++++\n", 11);
	write(0, payload->txt, payload->txtlen);
	write(0, "\n++++++++++\n", 12);

	sleep(2);

	pthread_mutex_unlock(&payload->mutex);

	write(0, "==========\n", 11);

	return (0);
}

void	*tryingToUseMutexLocked(void *args) {
	payload_t *payload = args;
	pthread_t tid = pthread_self();

	printf("HERE in lazy thread, id: %ld\n", tid);
	write(0, "Trying to use locked mutex\n", 28);

	pthread_mutex_lock(&payload->mutex);

	write(0, "----------\n", 11);
	write(0, payload->txt, payload->txtlen);
	write(0, "\n----------\n", 12);

	pthread_mutex_unlock(&payload->mutex);

	return (0);
}

int	main(__attribute__ ((unused)) int ac, char **av) {
	pthread_t tid;
	pthread_t tidLazy;
	char *textFromArgs = av[1];

//	if ((payload = malloc(sizeof(payload_t))) == NULL) {
//		printf("Malloc error");
//	}
	payload.txtlen =  strlen(textFromArgs);
	pthread_mutex_init(&payload.mutex, NULL);

	if ((payload.txt = malloc(sizeof(char) * (payload.txtlen + 1))) == NULL) {
		printf("Malloc error");
	}
	payload.txt = textFromArgs;

	pthread_create(&tid, NULL, routine, &payload);
	pthread_create(&tidLazy, NULL, tryingToUseMutexLocked, &payload);

	printf("HERE in main thread, id: %ld\n", pthread_self());

	sleep(2);

	write(0, "__________\n", 11);

	pthread_join(tid, NULL);
	pthread_mutex_destroy(&payload.mutex);
//	free(payload.txt);
//	free(payload);
	return (0);
}
