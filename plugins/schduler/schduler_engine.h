//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月8日 Author: kerry

#ifndef QUOTATIONS_SCHDULER_SCHDULER_ENGINE_H_
#define QUOTATIONS_SCHDULER_SCHDULER_ENGINE_H_

#include "logic/quotations_infos.h"
#include "thread/base_thread_handler.h"
#include "thread/base_thread_lock.h"
#include <map>

namespace quotations_schduler {

typedef std::map<int32, quotations_logic::ConnectionSchduler> SCHDULER_MAP;
typedef std::map<int, quotations_logic::ConnectionSchduler> SOCKET_MAP;

class SchdulerEngine {
 public:
  virtual bool SetConnectionSchduler(
      const int32 id, quotations_logic::ConnectionSchduler* schduler) = 0;

  virtual bool GetConnectionSchduler(
      const int32 id, quotations_logic::ConnectionSchduler* schduler) = 0;

  virtual bool DelConnectionSchduler(const int32 id) = 0;

  virtual bool FindConnectionSchduler(
      const int socket, quotations_logic::ConnectionSchduler* schduler) = 0;

  virtual bool CloseConnectionSchduler(const int socket) = 0;

  virtual bool SetRecvTime(const int socket) = 0;

  virtual bool SetSendTime(const int socket) = 0;

  virtual bool CheckHeartPacket() = 0;

  virtual bool SetSendErrorCount(int socket) = 0;

  virtual bool SetRecvErrorCount(int socket) = 0;

  virtual int32 SendAllQuotations(const void* data, const int32 len) = 0;

  virtual int32 SendAllQuotations(const void* data, const int32 len,
                                  const int32 type) = 0;
};

class SchdulerEngineImpl : public SchdulerEngine {
 public:
  bool SetConnectionSchduler(const int32 id,
                             quotations_logic::ConnectionSchduler* schduler);

  bool GetConnectionSchduler(const int32 id,
                             quotations_logic::ConnectionSchduler* schduler);

  bool DelConnectionSchduler(const int32 id);

  bool FindConnectionSchduler(const int socket,
                              quotations_logic::ConnectionSchduler* schduler);

  bool CloseConnectionSchduler(const int socket);

  bool SetRecvTime(const int socket);

  bool SetSendTime(const int socket);

  bool CheckHeartPacket();

  bool SetSendErrorCount(int socket);

  bool SetRecvErrorCount(int socket);

  int32 SendAllQuotations(const void* data, const int32 len);

  int32 SendAllQuotations(const void* data, const int32 len, const int32 type);
};

class SchdulerCache {
 public:
  SCHDULER_MAP schduler_map_;
  SOCKET_MAP socket_map_;
};

__attribute__((visibility("default")))
   class ConnectionSchdulerManager {
 public:
  ConnectionSchdulerManager();
  virtual ~ConnectionSchdulerManager();
 public:
  bool SetConnectionSchduler(const int32 id,
                             quotations_logic::ConnectionSchduler* schduler);

  bool GetConnectionSchduler(const int32 id,
                             quotations_logic::ConnectionSchduler* schduler);

  bool DelConnectionSchduler(const int32 id);

  bool FindConnectionSchduler(const int socket,
                              quotations_logic::ConnectionSchduler* schduler);

  bool CloseConnectionSchduler(const int socket);

  bool SetRecvTime(const int socket);

  bool SetSendTime(const int socket);

  bool CheckHeartPacket();

  bool SetSendErrorCount(int socket);

  bool SetRecvErrorCount(int socket);

  int32 SendAllQuotations(const void* data, const int32 len);

  int32 SendAllQuotations(const void* data, const int32 len, const int32 type);

 private:
  void Init();

 public:
  SchdulerCache* GetFindCache() {
    return this->schduler_cache_;
  }

 private:
  struct threadrw_t* lock_;
  SchdulerCache* schduler_cache_;
};

class ConnectionSchdulerEngine {
 private:
  static ConnectionSchdulerManager *schduler_mgr_;
  static ConnectionSchdulerEngine *schduler_engine_;

  ConnectionSchdulerEngine() {
  }
  virtual ~ConnectionSchdulerEngine() {
  }
 public:
  __attribute__((visibility("default")))
         static ConnectionSchdulerManager* GetSchdulerManager() {
    if (schduler_mgr_ == NULL)
      schduler_mgr_ = new ConnectionSchdulerManager();
    return schduler_mgr_;
  }

  static ConnectionSchdulerEngine* GetSchdulerEngine() {
    if (schduler_engine_ == NULL)
      schduler_engine_ = new ConnectionSchdulerEngine();

    return schduler_engine_;
  }
};
}

#ifdef __cplusplus
extern "C" {
#endif
quotations_schduler::SchdulerEngine *GetConnectionSchdulerEngine(void);
#ifdef __cplusplus
}
#endif

#endif
