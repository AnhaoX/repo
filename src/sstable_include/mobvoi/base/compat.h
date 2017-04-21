// Copyright 2012 Mobvoi Inc. All Rights Reserved.
// Author: mikelei@mobvoi.com (Mike Lei)
//
// Google compatibility declarations and inline definitions.
// These are assembled from OpenFst and Thrax code.

#ifndef MOBVOI_BASE_COMPAT_H__
#define MOBVOI_BASE_COMPAT_H__

#include <deque>
#include <iostream>
#include <istream>
#include <map>
#include <memory>
#include <ostream>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using std::cerr;
using std::cin;
using std::cout;
using std::deque;
using std::endl;
using std::istream;
using std::map;
using std::ostream;
using std::set;
using std::stack;
using std::string;
using std::shared_ptr;
using std::unique_ptr;
using std::vector;

namespace mobvoi {
using std::unordered_map;
using std::unordered_set;
}  // namespace mobvoi

#endif  // MOBVOI_BASE_COMPAT_H__
