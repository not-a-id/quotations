//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年5月28日 Author: kerry

#ifndef QUOTATIONS_STAR_STAR_LOGIC_
#define QUOTATIONS_STAR_STAR_LOGIC_

#include "basic/basictypes.h"
#include "core/common.h"
#include "star/star_redis.h"
#include "star/star_schduler_engine.h"

namespace star_logic {

class Starlogic {
 public:
  Starlogic();
  virtual ~Starlogic();

 private:
  static Starlogic *instance_;

 public:
  static Starlogic *GetInstance();
  static void FreeInstance();

  bool OnStarConnect(struct server *srv, const int socket);

  bool OnStarMessage(struct server *srv, const int socket, const void *msg,
                      const int len);

  bool OnStarClose(struct server *srv, const int socket);

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
  star_logic::StarRedis* star_redis_;
  star_logic::StarSchdulerManager* star_schduler_;
};
}  // namespace goods_logic

#endif
