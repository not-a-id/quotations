//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#ifndef QUOTATIONS_GOODS_GOODS_LOGIC_
#define QUOTATIONS_GOODS_GOODS_LOGIC_

#include "basic/basictypes.h"
#include "core/common.h"
#include "goods/goods_redis.h"
#include "goods/goods_schduler_engine.h"

namespace goods_logic {

class Goodslogic {
public:
  Goodslogic();
  virtual ~Goodslogic();

private:
  static Goodslogic *instance_;

public:
  static Goodslogic *GetInstance();
  static void FreeInstance();

  bool OnGoodsConnect(struct server *srv, const int socket);

  bool OnGoodsMessage(struct server *srv, const int socket, const void *msg,
                       const int len);

  bool OnGoodsClose(struct server *srv, const int socket);

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
  goods_logic::GoodsRedis*    goods_redis_;
  goods_logic::GoodsSchdulerManager*  goods_schduler_;
};
} // namespace goods_logic

#endif
