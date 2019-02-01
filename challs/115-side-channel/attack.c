// TODO
#define _POSIX_C_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>

#define MAX_PATH 1024

#define BUFSIZE 256

#define ITERATIONS 1
#define K 256
#define DATA 256

#define FORK_FAILED_THRESHOLD 100
#define PIPE_FAILED_THRESHOLD 100

struct thread_iterate_args {
	unsigned char index, data;
	unsigned long *avg;
};

struct thread_index_args {
	unsigned char index;
	unsigned long *avg;
};

void spawn_process(int p[2]) {
	int r;
	struct timeval start;
	char *argv[] = {"./dumbsmartcard"}, *environ[] = {NULL};
	
	r = dup2(p[0], STDIN_FILENO);
	if(r < 0) {
		perror("dup2");
		exit(EXIT_FAILURE);
	}

	gettimeofday(&start, NULL);

	r = write(p[1], &start, sizeof(start));
	if(r < 0) {
		perror("Child: write");
	}

	close(p[1]);

	r = execve(argv[0], argv, environ);
	if(r < 0) {
		perror("Child: execve");
	}
}

void *thread_iterate(void *raw_args) {
	struct thread_iterate_args *args = raw_args;
	char buf[BUFSIZE] = {0};
	int r, f, p[2];
	unsigned int i, fork_failed, pipe_failed;
	struct timeval start, stop;
	unsigned long time;

	buf[args->index] = args->data;
	*args->avg = 0;

	for(i = 0; i < ITERATIONS; i++) {
		while((r = pipe(p)) < 0) {
			pipe_failed++;
			if(pipe_failed > PIPE_FAILED_THRESHOLD) {
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			usleep(PIPE_SLEEP);
		}

		fork_failed = 0;
		while((f = fork()) < 0) {
			fork_failed++;
			if(fork_failed > FORK_FAILED_THRESHOLD) {
				perror("fork");
				exit(EXIT_FAILURE);				
			}
			usleep(1000);
		}

		if(f < 0) {
			exit(EXIT_FAILURE);
		} else if(!f) {
			spawn_process(p);
			// Never called
			exit(EXIT_SUCCESS);
		}

		// Get clock start
		r = read(p[0], &start, sizeof(start));
		close(p[0]);
		if(r < 0) {
			perror("Parent: read");
			exit(EXIT_FAILURE);
		}

		// Send buffer to child
		r = write(p[1], buf, sizeof(buf));
		close(p[1]);
		if(r < 0) {
			perror("Parent: write");
			exit(EXIT_FAILURE);
		}

		waitpid(f, NULL, 0);

		gettimeofday(&stop, NULL);

		time = (unsigned long)stop.tv_sec * 1000000 + (unsigned long)stop.tv_usec
			- (unsigned long)start.tv_sec * 1000000 - (unsigned long)start.tv_usec;

		*args->avg += time;
	}

	*args->avg /= ITERATIONS;

	return NULL;
}

void *thread_index(void *raw_args) {
	struct thread_index_args *args = raw_args;
	unsigned char data;
	pthread_t threads[DATA];
	int r;
	struct thread_iterate_args targs[DATA];

	for(data = 0; data < DATA; data++) {
		targs[data].index = args->index;
		targs[data].data = data;
		targs[data].avg = &args->avg[data];
		r = pthread_create(&threads[data], NULL, thread_iterate, &targs[data]);
		if(r) {
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
	}

	for(data = 0; data < DATA; data++) {
		// fprintf(stderr, "INNER: Waiting for %ld\n", threads[data]);
		r = pthread_join(threads[data], NULL);
		// fprintf(stderr, "INNER: %ld: ok\n", threads[data]);
		if(r) {
			perror("pthread_join");
			exit(EXIT_FAILURE);
		}
	}

	return NULL;
}

int main(int argc, char *argv[]) {
	pthread_t threads[K];
	int r;
	unsigned int k, data, l;
	struct thread_index_args targs[K];
	unsigned long avg[K][DATA];
	FILE *f;
	char fpath[MAX_PATH];

	if(argc != 2) {
		fprintf(stderr, "Usage: %s <out directory>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	l = strlen(argv[1]);

	for(k = 0; k < K; k++) {
		targs[k].index = k;
		targs[k].avg = avg[k];
		r = pthread_create(&threads[k], NULL, thread_index, &targs[k]);
		if(r) {
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
	}

	for(k = 0; k < K; k++) {
		// fprintf(stderr, "OUTER: Waiting for %ld\n", threads[k]);
		r = pthread_join(threads[k], NULL);
		// fprintf(stderr, "OUTER: %ld: ok\n", threads[k]);
		if(r) {
			perror("pthread_join");
			exit(EXIT_FAILURE);
		}
	}



	for(k = 0; k < K; k++) {
		strncpy(fpath, argv[1], MAX_PATH);
		snprintf(fpath + l, MAX_PATH - l - 7, "/%03d.dat", k);
		f = fopen(fpath, "w");
		if(!f) {
			perror("fopen");
			continue;
		}

		for(data = 0; data < DATA; data++) {
			fprintf(f, "%d %ld\n", k, avg[k][data]);
		}

		fclose(f);
	}

	return EXIT_SUCCESS;
}