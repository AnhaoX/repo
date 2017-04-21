// log.h
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Author: riley@google.com (Michael Riley)
//
// \file
// Google-style logging declarations and inline definitions.

#pragma once

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>

#include "mobvoi/base/types.h"

#if defined(__ANDROID__)
#include <android/log.h>

#define LOG_TAG "System.out.c"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#endif  // defined(__ANDROID__)

namespace mobvoi {

using std::string;

class LogMessage {
 public:
  LogMessage(const string &type) : fatal_(type == "FATAL"), type_(type) {}
  ~LogMessage() {
    std::ostringstream oss;
    PrintDate(oss);
    PrintThreadId(oss);
    PrintType(oss);
    oss << oss_.str();
    Print(oss.str());
    if(fatal_)
      exit(1);
  }
  std::ostream &stream() { return oss_; }

 private:
  void PrintType(std::ostream& oss) {
    oss << type_ << "  ";
  }

  void PrintThreadId(std::ostream& oss) {
    pthread_t tid = pthread_self();
    oss << "[" << tid << "] ";
  }

  void PrintDate(std::ostream& oss) {
    time_t rawtime;
    time(&rawtime);
    struct tm* timeinfo = localtime(&rawtime);
    const int buffer_length = 80;
    char buffer[buffer_length];
    strftime(buffer, buffer_length ,"%Y-%m-%d %H:%M:%S ",timeinfo);
    oss << buffer;
  }

  void Print(const std::string& str) {
 #if defined(__ANDROID__)
    LOGI("%s", str.c_str()); 
#else
    std::cerr << str << std::endl;
#endif  // defined(__ANDROID__)
  }

  bool fatal_;
  const std::string type_;
  std::ostringstream oss_;
};

#define LOG(type) LogMessage(#type).stream()

namespace internal {
template<typename T>
T* CheckNotNull(const char* file, int line, const char* name, T* val) {
  if (val == NULL) {
    LOG(FATAL) << name << ":" << file << ":" << line;
  }
  return val;
}
}  // namespace internal
#define CHECK_NOTNULL(A) \
  internal::CheckNotNull(__FILE__, __LINE__, "'" #A "' must not be NULL", (A))

#define CHECK(x) \
  if (!(x)) LOG(FATAL) << "Check failed at " << __FILE__ << ":" << __LINE__

#define CHECK_EQ(x, y) CHECK((x) == (y))
#define CHECK_LT(x, y) CHECK((x) < (y))
#define CHECK_GT(x, y) CHECK((x) > (y))
#define CHECK_LE(x, y) CHECK((x) <= (y))
#define CHECK_GE(x, y) CHECK((x) >= (y))
#define CHECK_NE(x, y) CHECK((x) != (y))

// Debug checks
#ifdef NDEBUG

#define DCHECK(x) while(false) CHECK(x)
#define DCHECK_EQ(x, y) DCHECK((x) == (y))
#define DCHECK_LT(x, y) DCHECK((x) <  (y))
#define DCHECK_GT(x, y) DCHECK((x) >  (y))
#define DCHECK_LE(x, y) DCHECK((x) <= (y))
#define DCHECK_GE(x, y) DCHECK((x) >= (y))
#define DCHECK_NE(x, y) DCHECK((x) != (y))

#else  // NDEBUG

#define DCHECK    CHECK
#define DCHECK_EQ CHECK_EQ
#define DCHECK_LT CHECK_LT
#define DCHECK_GT CHECK_GT
#define DCHECK_LE CHECK_LE
#define DCHECK_GE CHECK_GE
#define DCHECK_NE CHECK_NE

#endif  // !NDEBUG

// Ports
#define ATTRIBUTE_DEPRECATED __attribute__((deprecated))

}  // namespace mobvoi

