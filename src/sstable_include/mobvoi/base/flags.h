#pragma once

#if defined(__ANDROID__) || defined(IOS)
  #include "mobvoi/base/flags_lite.h"
#else
  #include "thirdparty/gflags/gflags.h"
#endif

#include <string>
#include "mobvoi/base/log.h"

namespace mobvoi {

inline void ParseCommandLineFlags(int* argc, char*** argv,
                                  bool remove_flags,
                                  const std::string& usage) {
#if defined(__ANDROID__) || defined(IOS)
  SetFlags(usage.c_str(), argc, argv, remove_flags);
#else
  google::SetUsageMessage(usage);
  google::ParseCommandLineFlags(argc, argv, remove_flags);
#endif
}

inline void ShowUsage(const char *argv0) {
#if defined(__ANDROID__) || defined(IOS)
    ::ShowUsage();
#else
    google::ShowUsageWithFlags(argv0);
#endif
}

inline void ShowCommand() {
#if defined(__ANDROID__) || defined(IOS)
  LOG(WARNING) << "ShowCommand() on android is not implemented.";
#else
  LOG(INFO) << google::GetArgv();
#endif
}

}  // namespace mobvoi
