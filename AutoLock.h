#ifndef __AUTOLOCK_H_
#define __AUTOLOCK_H_

#include <pthread.h>

/*
 * RAII class for handling pthread mutex
 *
 * It uses RAII mechanism to lock mutex automatically on an object creation,
 * and automatically unlocks the mutex when the object goes out of scope.
 * This class is mainly written for thread-safety of data when a user runs
 * the quadris program in tetris mode which uses multiple pthreads. (concurrency)
 */
class AutoLock
{
public:
    AutoLock(pthread_mutex_t * lock)
    : lock(lock)
    {
        pthread_mutex_lock(lock);
    }

    ~AutoLock()
    {
        pthread_mutex_unlock(lock);
    }

private:
    pthread_mutex_t * lock;
};

#endif //__AUTOLOCK_H_
