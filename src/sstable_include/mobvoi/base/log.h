#pragma once

#if defined(__ANDROID__) || defined(IOS)
  #include "mobvoi/base/log_lite.h"
  #include "mobvoi/base/vlog_lite.h"
  using mobvoi::LogMessage;
#else
  #include "mobvoi/base/compat.h"
  #include "thirdparty/glog/logging.h"
#endif
