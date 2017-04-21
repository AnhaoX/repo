// Copyright 2014 Mobvoi Inc. All Rights Reserved.
// Author: mikelei@mobvoi.com (Mike Lei)
//
// Common string utilities.

#ifndef MOBVOI_BASE_STRING_UTIL_H_
#define MOBVOI_BASE_STRING_UTIL_H_

#include <stdlib.h>
#include <string.h>

#include <vector>

#include "mobvoi/base/compat.h"

#include "mobvoi/base/types.h"

namespace mobvoi {

inline int StrCaseCmp(const char* string1, const char* string2) {
  return strcasecmp(string1, string2);
}
// Splits string using any of the single character delimiters.
// If omit_empty_strings == true, the output will contain any
// nonempty strings after splitting on any of the
// characters in the delimiter.  If omit_empty_strings == false,
// the output will contain n+1 strings if there are n characters
// in the set "delim" within the input string.  In this case
// the empty string is split to a single empty string.
void SplitStringToVector(const std::string& full, const char* delimiters,
                         bool omit_empty_strings,
                         std::vector<std::string>* out);

std::string JoinVectorToString(const std::vector<std::string>& v,
                               const std::string& separator);

// Split utf8 string into characters.
bool SplitUTF8String(const std::string& str,
                     std::vector<std::string>* characters);

std::string UTF8CodeToUTF8String(int32_t code);

// Returns true if str starts with search, or false otherwise.
bool StartsWithASCII(const std::string& str,
                     const std::string& search,
                     bool case_sensitive);

template<typename T>
T StringToNumber(const string& number_string) {
  T number;
  std::istringstream iss(number_string);
  iss >> number;
  if (iss.fail()) {
    std::cout << "Failed to convert " << number_string << " to " << number << std::endl;
    exit(EXIT_FAILURE);
  }
  return number;
}

bool EndWith(const string& str, const string& suffix);

// Trims any whitespace from either end of the input string.  Returns where
// whitespace was found.
// The non-wide version has two functions:
// * TrimWhitespaceASCII()
//   This function is for ASCII strings and only looks for ASCII whitespace;
// Please choose the best one according to your usage.
// NOTE: Safe to use the same variable for both input and output.
enum TrimPositions {
  TRIM_NONE     = 0,
  TRIM_LEADING  = 1 << 0,
  TRIM_TRAILING = 1 << 1,
  TRIM_ALL      = TRIM_LEADING | TRIM_TRAILING,
};

bool TrimString(const string& input,
                const char trim_chars[],
                string* output);
TrimPositions TrimWhitespaceASCII(const string& input,
                                  TrimPositions positions,
                                  string* output);

// Starting at |start_offset| (usually 0), replace the first instance of
// |find_this| with |replace_with|.
void ReplaceFirstSubstringAfterOffset(string* str,
                                      string::size_type start_offset,
                                      const string& find_this,
                                      const string& replace_with);
void ReplaceAllAfterOffset(string* str,
                           string::size_type start_offset,
                           const string& find_this,
                           const string& replace_with);
}  // namespace mobvoi

std::string StringPrintf(const char* fmt, ...);
void SplitString(const string& str,
                 char s,
                 std::vector<string>* r);
double StringToDouble(const string& str);
float StringToFloat(const string& str);
string JoinVector(std::vector<string> values, char ch);
string IntToString(int d);
string UintToString(uint32 d);
string Int64ToString(int64 d);
string Uint64ToString(uint64 d);
string DoubleToString(long double d);

int StringToInt(const string& str);
int64 StringToInt64(const string& str);
uint64 StringToUint64(const string& str);

string string2hex(const string& str);

#endif  // MOBVOI_BASE_STRING_UTIL_H_
