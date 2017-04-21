// Copyright 2015 Mobvoi Inc. All Rights Reserved.
// Author: huyaguang@mobvoi.com (Yaguang Hu)

#ifndef MOBVOI_BASE_SSTABLE_SINGLETON_H_
#define MOBVOI_BASE_SSTABLE_SINGLETON_H_

#include "mobvoi/base/basictypes.h"
#include "mobvoi/base/compat.h"
#include "mobvoi/base/singleton.h"
#include "mobvoi/util/storage/sstable/sstable.h"

namespace mobvoi {

class SSTableSingleton {
 public:
  ~SSTableSingleton();

  bool GetData(const string& key, std::istringstream* stream);

  static const string kSSTableProtocol;

 private:
  SSTableSingleton();

  friend struct DefaultSingletonTraits<SSTableSingleton>;
  unique_ptr<file::SSTable> sstable_;

  DISALLOW_COPY_AND_ASSIGN(SSTableSingleton);
};
} // namespace mobvoi
#endif  // MOBVOI_BASE_SSTABLE_SINGLETON_H_
