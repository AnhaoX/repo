// Copyright 2014 Mobvoi Inc. All Rights Reserved.
// Author: qli@mobvoi.com (Qian Li)
// Created on: Apr 22, 2014
//
// A pthread mutex wrapper.

#ifndef BASE_MUTEX_LOCK_H_
#define BASE_MUTEX_LOCK_H_

#include <pthread.h>

#include "mobvoi/base/macros.h"

namespace mobvoi {

class Mutex {
 public:
  Mutex() { pthread_mutex_init(&mutex_, 0); }
  ~Mutex() { pthread_mutex_destroy(&mutex_); }

  void Lock() { pthread_mutex_lock(&mutex_); }
  void Unlock() { pthread_mutex_unlock(&mutex_); }
  
 private:
  friend class Condition;

  pthread_mutex_t mutex_;

  DISALLOW_COPY_AND_ASSIGN(Mutex);
};

class MutexLock {
 public:
  explicit MutexLock(Mutex* mutex) : mutex_(mutex) { mutex_->Lock(); }
  ~MutexLock() { mutex_->Unlock(); }

 private:
  Mutex* mutex_;

  DISALLOW_COPY_AND_ASSIGN(MutexLock);
};
  
class Condition {
 public:
  Condition() { pthread_cond_init(&condition_, NULL); }
  ~Condition() { pthread_cond_destroy(&condition_); }
  
  void Broadcast() { pthread_cond_broadcast(&condition_); }
  void Signal() { pthread_cond_signal(&condition_); }
  void Wait(Mutex* mutex) { pthread_cond_wait(&condition_, &(mutex->mutex_)); }
  
 private:
  pthread_cond_t condition_;
  
  DISALLOW_COPY_AND_ASSIGN(Condition);
};

}  // namespace mobvoi
#endif  // BASE_MUTEX_LOCK_H_
