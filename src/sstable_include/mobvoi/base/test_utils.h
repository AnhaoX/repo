// Copyright 2014 Mobvoi Inc. All Rights Reserved.
// Author: qli@mobvoi.com (Qian Li)
//
// Common utils for test.

#ifndef MOBVOI_BASE_TEST_UTILS_H__
#define MOBVOI_BASE_TEST_UTILS_H__

namespace mobvoi {

std::string get_speech_root_dir() {
  const std::string SPEECH_ROOT_DIR = "SPEECH_ROOT_DIR";
  const char* speech_root_dir = getenv(SPEECH_ROOT_DIR.c_str());
  if (speech_root_dir == NULL) {
    return "./";
  } else {
    return speech_root_dir;
  }
}

}  // namespace mobvoi

#endif  // MOBVOI_BASE_TEST_UTILS_H__
