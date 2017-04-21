// flags.h
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
// Google-style flag handling declarations and inline definitions.

#pragma once

#include <iostream>
#include <map>
#include <string>

#include "mobvoi/base/log_lite.h"
#include "mobvoi/base/types.h"
#include "mobvoi/base/mutex.h"
#include "mobvoi/base/macros.h"

using std::string;

//
// FLAGS USAGE:
//
// Definition example:
//
//    DEFINE_int32(length, 0, "length");
//
// This defines variable FLAGS_length, initialized to 0.
//
// Declaration example:
//
//    DECLARE_int32(length);
//
// SetFlags() can be used to set flags from the command line
// using, for example, '--length=2'.
//
// ShowUsage() can be used to print out command and flag usage.
//

#define DECLARE_bool(name) extern bool FLAGS_ ## name
#define DECLARE_string(name) extern string FLAGS_ ## name
#define DECLARE_int32(name) extern int32 FLAGS_ ## name
#define DECLARE_int64(name) extern int64 FLAGS_ ## name
#define DECLARE_double(name) extern double FLAGS_ ## name

template <typename T>
struct FlagDescription {
  FlagDescription(T *addr, const char *doc, const char *type, const T val)
      : address(addr), doc_string(doc), type_name(type), default_value(val) {}

  T *address;
  const char *doc_string;
  const char *type_name;
  const T default_value;
};

template <typename T>
class FlagRegister {
 public:
  static FlagRegister<T> *GetRegister() {
    pthread_once(&register_init_, &FlagRegister<T>::Init);
    return register_;
  }

  const FlagDescription<T> &GetFlagDescription(const string &name) const {
    mobvoi::MutexLock l(register_lock_);
    typename std::map< string, FlagDescription<T> >::const_iterator it =
      flag_table_.find(name);
    return it != flag_table_.end() ? it->second : 0;
  }
  void SetDescription(const string &name,
                      const FlagDescription<T> &desc) {
    mobvoi::MutexLock l(register_lock_);
    flag_table_.insert(make_pair(name, desc));
  }

  bool SetFlag(const string &val, bool *address) const {
    if (val == "true" || val == "1" || val.empty()) {
      *address = true;
      return true;
    } else if (val == "false" || val == "0") {
      *address = false;
      return true;
    }
    else {
      return false;
    }
  }
  bool SetFlag(const string &val, string *address) const {
    *address = val;
    return true;
  }
  bool SetFlag(const string &val, int32 *address) const {
    char *p = 0;
    *address = strtol(val.c_str(), &p, 0);
    return !val.empty() && *p == '\0';
  }
  bool SetFlag(const string &val, int64 *address) const {
    char *p = 0;
    *address = strtoll(val.c_str(), &p, 0);
    return !val.empty() && *p == '\0';
  }
  bool SetFlag(const string &val, double *address) const {
    char *p = 0;
    *address = strtod(val.c_str(), &p);
    return !val.empty() && *p == '\0';
  }

  bool SetFlag(const string &arg, const string &val) const {
    for (typename std::map< string,
             FlagDescription<T> >::const_iterator it =
           flag_table_.begin();
         it != flag_table_.end();
         ++it) {
      const string &name = it->first;
      const FlagDescription<T> &desc = it->second;
      if (arg == name)
        return SetFlag(val, desc.address);
    }
    return false;
  }

  const string ShowDefault(bool default_value) const {
    return ", default = " + (default_value ? string("true") : string("false"));
  }
  const string GetDefault(const string &default_value) const {
    return ", default = \"" + default_value + "\"";
  }
  template<typename V>
  const string GetDefault(const V& default_value) const {
    std::ostringstream oss;
    oss << ", default = " << default_value;
    return oss.str();
  }
  void ShowUsage() const {
    for (typename std::map< string,
             FlagDescription<T> >::const_iterator it =
           flag_table_.begin();
         it != flag_table_.end();
         ++it) {
      const string &name = it->first;
      const FlagDescription<T> &desc = it->second;
      std::ostringstream oss;
      oss << "    --" << name << ": type = " << desc.type_name;
      oss << GetDefault(desc.default_value);
      mobvoi::LOG(INFO) << oss.str() << "\n      " << desc.doc_string  << "\n";
    }
  }

 private:
  static void Init() {
    register_lock_ = new mobvoi::Mutex;
    register_ = new FlagRegister<T>;
  }
  static pthread_once_t register_init_;   // ensures only called once
  static mobvoi::Mutex* register_lock_;        // multithreading lock
  static FlagRegister<T> *register_;

  std::map< string, FlagDescription<T> > flag_table_;
};

template <class T>
pthread_once_t FlagRegister<T>::register_init_ = PTHREAD_ONCE_INIT;

template <class T>
mobvoi::Mutex *FlagRegister<T>::register_lock_ = 0;

template <class T>
FlagRegister<T> *FlagRegister<T>::register_ = 0;


template <typename T>
class FlagRegisterer {
 public:
  FlagRegisterer(const string &name, const FlagDescription<T> &desc) {
    FlagRegister<T> *registr = FlagRegister<T>::GetRegister();
    registr->SetDescription(name, desc);
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(FlagRegisterer);
};


#define DEFINE_VAR(type, name, value, doc)                                \
  type FLAGS_ ## name = value;                                            \
  static FlagRegisterer<type>                                             \
  name ## _flags_registerer(#name, FlagDescription<type>(&FLAGS_ ## name, \
                                                         doc,             \
                                                         #type,           \
                                                         value))

#define DEFINE_bool(name, value, doc) DEFINE_VAR(bool, name, value, doc)
#define DEFINE_string(name, value, doc) \
  DEFINE_VAR(string, name, value, doc)
#define DEFINE_int32(name, value, doc) DEFINE_VAR(int32, name, value, doc)
#define DEFINE_int64(name, value, doc) DEFINE_VAR(int64, name, value, doc)
#define DEFINE_double(name, value, doc) DEFINE_VAR(double, name, value, doc)


// Temporary directory
DECLARE_string(tmpdir);

void SetFlags(const char *usage, int *argc, char ***argv, bool remove_flags);

// Deprecated - for backward compatibility
inline void InitFst(const char *usage, int *argc, char ***argv, bool rmflags) {
  return SetFlags(usage, argc, argv, rmflags);
}

void ShowUsage();

void ShowCommand();

