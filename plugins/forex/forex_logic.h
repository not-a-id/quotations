//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#ifndef QUOTATIONS_FOREX_FOREX_LOGIC_
#define QUOTATIONS_FOREX_FOREX_LOGIC_

#include "basic/basictypes.h"
#include "core/common.h"
#include "forex/forex_redis.h"
#include "forex/forex_schduler_engine.h"

namespace forex_logic {

class Forexlogic {
 public:
  Forexlogic();
  virtual ~Forexlogic();

 private:
  static Forexlogic *instance_;

 public:
  static Forexlogic *GetInstance();
  static void FreeInstance();

  bool OnForexConnect(struct server *srv, const int socket);

  bool OnForexMessage(struct server *srv, const int socket, const void *msg,
                      const int len);

  bool OnForexClose(struct server *srv, const int socket);

  bool OnBroadcastConnect(struct server *srv, const int socket,
                          const void *data, const int len);

  bool OnBroadcastMessage(struct server *srv, const int socket, const void *msg,
                          const int len);

  bool OnBroadcastClose(struct server *srv, const int socket);

  bool OnIniTimer(struct server *srv);

  bool OnTimeout(struct server *srv, char *id, int opcode, int time);

 private:
  bool Init();
 private:
  forex_logic::ForexRedis* forex_redis_;
  forex_logic::ForexSchdulerManager* forex_schduler_;
};
}  // namespace goods_logic

#endif
