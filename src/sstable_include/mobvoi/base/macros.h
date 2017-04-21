// Copyright 2014 Mobvoi Inc. All Rights Reserved.
// Author: qli@mobvoi.com (Qian Li)
// Created on: May 12, 2014
//
// This file contains common macros.

#ifndef MOBVOI_BASE_MACROS_H_
#define MOBVOI_BASE_MACROS_H_

// A macro to disallow the copy constructor and operator= functions.
// This should be used in the private: declarations for a class.
#define DISALLOW_COPY_AND_ASSIGN(type)    \
  type(const type&);                      \
  void operator=(const type&)

// A macro to disallow all the implicit constructors, namely the
// default constructor, copy constructor and operator= functions.
//
// This should be used in the private: declarations for a class
// that wants to prevent anyone from instantiating it. This is
// especially useful for classes containing only static methods.
#define DISALLOW_IMPLICIT_CONSTRUCTORS(type)    \
  type();                                       \
  DISALLOW_COPY_AND_ASSIGN(type)

#endif  // MOBVOI_BASE_MACROS_H_
