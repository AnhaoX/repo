// Copyright 2015 Mobvoi Inc. All Rights Reserved.
// Author: huyaguang@mobvoi.com (Yaguang Hu)

#ifndef MOBVOI_BASE_HBASE_SINGLETON_H_
#define MOBVOI_BASE_HBASE_SINGLETON_H_

#include "mobvoi/base/basictypes.h"
#include "mobvoi/base/compat.h"
#if !defined(__ANDROID__) && !defined(IOS)
#include "mobvoi/base/Hbase.h"
#endif
#include "mobvoi/base/singleton.h"

namespace apache {
namespace thrift {
namespace transport {
  class TSocket;
  class TTransport;
} // namespace transport

namespace protocol {
  class TProtocol;
} // namespace protocol
} // namespace thrift

namespace hadoop {
namespace hbase {
namespace thrift {
  class HbaseClient;
} // namespace thrift
} // namepsace hbase
} // namespace hadoop
} // namespace apache

namespace mobvoi {

class HbaseSingleton {
 public:
  ~HbaseSingleton();

  bool GetData(string uri, std::istringstream* stream);

  static const string kHBaseProtocol;

 private:
  HbaseSingleton();

  bool ParseUri(const string& uri, string* host, string* port,
                string* table, string* row,
                string* column);

  friend struct DefaultSingletonTraits<HbaseSingleton>;

  boost::shared_ptr<apache::thrift::transport::TSocket> socket_;
  boost::shared_ptr<apache::thrift::transport::TTransport> transport_;
  boost::shared_ptr<apache::thrift::protocol::TProtocol> protocol_;
  unique_ptr<apache::hadoop::hbase::thrift::HbaseClient> client_;

  DISALLOW_COPY_AND_ASSIGN(HbaseSingleton);
};

} // namepsace mobvoi

#endif // MOBVOI_BASE_HBASE_SINGLETON_H_
