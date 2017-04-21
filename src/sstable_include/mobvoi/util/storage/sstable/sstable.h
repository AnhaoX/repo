// Copyright 2014 Mobvoi Inc. All Rights Reserved.
// Author: spye@mobvoi.com (Shunping Ye)

#ifndef UTIL_SSTABLE_SSTABLE_H_
#define UTIL_SSTABLE_SSTABLE_H_

#include <string>
#include <vector>
#include <utility>

#include "mobvoi/base/basictypes.h"
#include "mobvoi/base/compat.h"
#include "mobvoi/util/storage/sstable/proto/sstable_service.pb.h"

namespace sofa {
namespace pbrpc {
class RpcClient;
class RpcChannel;
}
}

namespace file {
class SSTableServer_Stub;
class NewIteratorOptions;

class SSTable {
 public:
  //  If true , use snappy for request/response.
  explicit SSTable(bool use_compress = false);
  ~SSTable();

  //  Set RpcController timeout value
  void set_timteout(int timeout_ms) {
    timeout_ = timeout_ms;
  }

  // TODO(shunping) : Change to async mode.
  // get/put
  bool Open(const string& host, int port);
  //  Address with fromat "host:port"
  bool Open(const string& host_port);

  bool Put(const string& key, const string& value);
  //  If failed, resend this request.
  void PutAsync(const string& key, const string& value);
  bool Delete(const string& key);
  bool Get(const string& key, string* value);

  // iterator
  // TODO(shunping) : Write a iterator class for it.
  // Please call NewIterator before iterate, call DeleteIterator
  // after iterate done.
  bool NewIterator(const NewIteratorOptions& options);
  bool SeekToFirst();
  bool SeekKey(const string& key);
  bool Next(string* key, string* value);
  bool NextBatch(int batch_size, vector<std::pair<string, string> >* records);
  bool DeleteIterator();
  inline bool IsOpen() const { return is_open_; };

  file::SSTableServer_Stub* server_stub() {
    return server_stub_.get();
  }
  void IncPutQueue();
  void DecPutQueue();

 private:
  int timeout_;
  string uid_;
  bool use_compress_;
  bool is_open_;
  int put_cache_size_;
  std::unique_ptr<sofa::pbrpc::RpcClient> rpc_client_;
  std::unique_ptr<sofa::pbrpc::RpcChannel> rpc_channel_;
  std::unique_ptr<file::SSTableServer_Stub> server_stub_;

  DISALLOW_COPY_AND_ASSIGN(SSTable);
};
}  // namespace file
#endif  // UTIL_SSTABLE_SSTABLE_H_
