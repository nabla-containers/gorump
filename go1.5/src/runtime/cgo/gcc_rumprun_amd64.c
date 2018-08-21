// Copyright 2009 The Go Authors.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <sys/types.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include "libcgo.h"

static void* threadentry(void*);
static void (*setg_gcc)(void*);
int x_cgo_set_tls(unsigned long addr);

void
x_cgo_init(G *g, void (*setg)(void*))
{
	pthread_attr_t attr;
	size_t size;

	setg_gcc = setg;
	pthread_attr_init(&attr);
	pthread_attr_getstacksize(&attr, &size);
	g->stacklo = (uintptr)&attr - size + 4096;
	pthread_attr_destroy(&attr);
}


void
_cgo_sys_thread_start(ThreadStart *ts)
{
	pthread_attr_t attr;
	sigset_t ign, oset;
	pthread_t p;
	size_t size;
	int err;

	sigfillset(&ign);
	pthread_sigmask(SIG_SETMASK, &ign, &oset);

	pthread_attr_init(&attr);
	pthread_attr_getstacksize(&attr, &size);

	// Leave stacklo=0 and set stackhi=size; mstack will do the rest.
	ts->g->stackhi = size;
	err = pthread_create(&p, &attr, threadentry, ts);

	pthread_sigmask(SIG_SETMASK, &oset, nil);

	if (err != 0) {
		fprintf(stderr, "runtime/cgo: pthread_create failed: %s\n", strerror(err));
		abort();
	}
}

static void*
threadentry(void *v)
{
	ThreadStart ts;

	ts = *(ThreadStart*)v;
	free(v);

	/*
	 * Set specific keys.
	 */
	x_cgo_set_tls((unsigned long)(ts.tls));
	setg_gcc((void*)ts.g);

	crosscall_amd64(ts.fn);
	return nil;
}

pthread_key_t tls_key;
pthread_once_t key_once = PTHREAD_ONCE_INIT;

void _key_init()
{
    pthread_key_create(&tls_key, NULL);
}

void key_init()
{
    pthread_once(&key_once, _key_init);
}

int x_cgo_set_tls(unsigned long addr)
{
    key_init();
    unsigned long* _addr = malloc(sizeof(unsigned long));
    *_addr = addr;
    pthread_setspecific(tls_key, _addr);
    return 0;
}

unsigned long x_cgo_get_tls()
{
    unsigned long *_addr = pthread_getspecific(tls_key);
    if(_addr == 0)
        return 0;
    return *_addr;
}
