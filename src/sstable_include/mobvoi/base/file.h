// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
// http://code.google.com/p/protobuf/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Author: kenton@google.com (Kenton Varda)
// emulates google3/file/base/file.h

#ifndef MOBVOI_BASE_FILE_FILE_H_
#define MOBVOI_BASE_FILE_FILE_H_

#include <string>
#include <vector>

#include "mobvoi/base/compat.h"
#include "mobvoi/base/macros.h"

namespace mobvoi {

const int DEFAULT_FILE_MODE = 0777;

// Protocol buffer code only uses a couple static methods of File, and only
// in tests.
class File {
 public:
  // Check if the file exists.
  static bool Exists(const string& name);

  static bool Delete(const string& file_path);

  // Read an entire file to a string.  Return true if successful, false
  // otherwise.
  static bool ReadFileToString(const string& name, string* output);

  static bool ReadFileToLines(const string& filename, vector<string>* vec);

  // Same as above, but crash on failure.
  static void ReadFileToStringOrDie(const string& name, string* output);

  // Create a file and write a string to it.
  static bool WriteStringToFile(const string& contents, const string& name);

  // Same as above, but crash on failure.
  static void WriteStringToFileOrDie(const string& contents,
                                     const string& name);

  // Create a directory.
  static bool CreateDir(const string& name, int mode);

  // Create a directory and all parent directories if necessary.
  static bool RecursivelyCreateDir(const string& path, int mode);

  // If "name" is a file, we delete it.  If it is a directory, we
  // call DeleteRecursively() for each file or directory (other than
  // dot and double-dot) within it, and then delete the directory itself.
  // The "dummy" parameters have a meaning in the original version of this
  // method but they are not used anywhere in protocol buffers.
  static void DeleteRecursively(const string& name,
                                void* dummy1 = NULL, void* dummy2 = NULL);

  //  a The first fragment may or may not have a trailing '/'.
  //  b The second fragment may or may not have a leading '/'.
  //  The path "a/b" containing exactly one '/' between fragments a and b.
  static string JoinPath(const string& a, const string& b);

  static bool FileSize(const string& file, size_t* size);

  static bool IsDir(const std::string& dir);

  static bool GetFilesInDir(const string& dir, vector<string>* out);

  // Get subdir names, except "." and ".."
  static bool GetDirsInDir(const string& dir, vector<string>* out);

  static bool Rename(const std::string& from, const std::string& to);

  static std::string BaseName(const std::string& path);

  static std::string PrefixName(const std::string& file_path);

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(File);
};
}  // namespace mobvoi

#endif  // MOBVOI_BASE_FILE_FILE_H_
