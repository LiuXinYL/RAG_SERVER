/* >>>------------------------------------------------------------
 *
 * Tgt_File: pthread.h
 *
 * <<<------------------------------------------------------------ */


#ifndef PRQA_PTHREAD_H
#define PRQA_PTHREAD_H

// simplified but still realistic implementation of pthread.h

#ifdef __cplusplus
extern "C"
{
#endif

#define __SIZEOF_PTHREAD_MUTEX_T 32
#define __SIZEOF_PTHREAD_ATTR_T 32
#define __SIZEOF_PTHREAD_MUTEX_T 32
#define __SIZEOF_PTHREAD_RWLOCK_T 44
#define __SIZEOF_PTHREAD_BARRIER_T 20

#define __SIZEOF_PTHREAD_MUTEXATTR_T 4
#define __SIZEOF_PTHREAD_COND_T 48
#define __SIZEOF_PTHREAD_CONDATTR_T 4
#define __SIZEOF_PTHREAD_RWLOCKATTR_T 8
#define __SIZEOF_PTHREAD_BARRIERATTR_T 4

#define PTHREAD_MUTEX_INITIALIZER               { 0, 0, 0, 0, }
#define PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP  { 0, 0, 0, PTHREAD_MUTEX_RECURSIVE_NP }
#define PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP { 0, 0, 0, PTHREAD_MUTEX_ERRORCHECK_NP }
#define PTHREAD_ADAPTIVE_MUTEX_INITIALIZER_NP   { 0, 0, 0, PTHREAD_MUTEX_ADAPTIVE_NP }

struct __pthread_mutex_s
{
  int __a;
  int __b;
  int __c;
  int __d;
 };

typedef union
{
  char __size[__SIZEOF_PTHREAD_MUTEXATTR_T];
  int __align;
} pthread_mutexattr_t;

typedef union
{
  char __size[__SIZEOF_PTHREAD_CONDATTR_T];
  int __align;
} pthread_condattr_t;

typedef unsigned int pthread_key_t;

typedef int pthread_once_t;

union pthread_attr_t
{
  char __size[__SIZEOF_PTHREAD_ATTR_T];
  long int __align;
};
typedef union pthread_attr_t pthread_attr_t;

typedef union
{
  struct __pthread_mutex_s __data;
  char __size[__SIZEOF_PTHREAD_MUTEX_T];
  long int __align;
} pthread_mutex_t;

typedef union
{
//  struct __pthread_cond_s __data;
  char __size[__SIZEOF_PTHREAD_COND_T];
  long int __align;
} pthread_cond_t;

typedef union
{
//  struct __pthread_rwlock_arch_t __data;
  char __size[__SIZEOF_PTHREAD_RWLOCK_T];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[__SIZEOF_PTHREAD_RWLOCKATTR_T];
  long int __align;
} pthread_rwlockattr_t;

typedef volatile int pthread_spinlock_t;

typedef union
{
  char __size[__SIZEOF_PTHREAD_BARRIER_T];
  long int __align;
} pthread_barrier_t;

typedef union
{
  char __size[__SIZEOF_PTHREAD_BARRIERATTR_T];
  int __align;
} pthread_barrierattr_t;


typedef unsigned long int pthread_t;


struct timespec;

int pthread_create (pthread_t *, const pthread_attr_t *, void * (*) (void *), void *);
int pthread_join (pthread_t, void **);
int pthread_cancel (pthread_t);

int pthread_mutex_lock (pthread_mutex_t *);
int pthread_mutex_trylock (pthread_mutex_t *);
int pthread_mutex_timedlock (pthread_mutex_t *, const struct timespec *);
int pthread_mutex_unlock (pthread_mutex_t *);

int pthread_mutex_destroy (pthread_mutex_t *);
int pthread_mutex_init (pthread_mutex_t *, const pthread_mutexattr_t *);

int pthread_mutexattr_init (pthread_mutexattr_t *);
int pthread_mutexattr_settype (pthread_mutexattr_t *, int);
int pthread_mutexattr_destroy (pthread_mutexattr_t *);

enum
{
  PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_ADAPTIVE_NP,
  PTHREAD_MUTEX_NORMAL = PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE = PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK = PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_DEFAULT = PTHREAD_MUTEX_NORMAL,
  PTHREAD_MUTEX_FAST_NP = PTHREAD_MUTEX_TIMED_NP
};

int pthread_barrier_init (pthread_barrier_t *, const pthread_barrierattr_t *, unsigned int);
int pthread_barrier_destroy (pthread_barrier_t *);
int pthread_barrier_wait (pthread_barrier_t *);

int pthread_cond_init (pthread_cond_t *, const pthread_condattr_t *);
int pthread_cond_destroy (pthread_cond_t *);
int pthread_cond_signal (pthread_cond_t *);
int pthread_cond_broadcast (pthread_cond_t *);
int pthread_cond_wait (pthread_cond_t *, pthread_mutex_t *);
int pthread_cond_timedwait (pthread_cond_t *, pthread_mutex_t *, const struct timespec *);


int pthread_rwlock_init (pthread_rwlock_t *, const pthread_rwlockattr_t *);
int pthread_rwlock_destroy (pthread_rwlock_t *);
int pthread_rwlock_rdlock (pthread_rwlock_t *);
int pthread_rwlock_tryrdlock (pthread_rwlock_t *);
int pthread_rwlock_wrlock (pthread_rwlock_t *);
int pthread_rwlock_trywrlock (pthread_rwlock_t *);
int pthread_rwlock_unlock (pthread_rwlock_t *);

pthread_t pthread_self(void);
int pthread_equal(pthread_t t1, pthread_t t2);

#ifdef __cplusplus
}
#endif

#ifndef NULL
#define NULL 0
#endif

#endif
