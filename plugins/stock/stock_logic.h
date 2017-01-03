//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry
//  
#ifndef QUOTATIONS_STOCK_STOCK_LOGIC_
#define QUOTATIONS_STOCK_STOCK_LOGIC_

#include "basic/basictypes.h"
#include "core/common.h"
//#include "net/comm_head.h"
//#include "net/packet_processing.h"

namespace stock_logic {

class Stocklogic {
public:
  Stocklogic();
  virtual ~Stocklogic();

private:
  static Stocklogic *instance_;

public:
  static Stocklogic *GetInstance();
  static void FreeInstance();

  bool OnStockConnect(struct server *srv, const int socket);

  bool OnStockMessage(struct server *srv, const int socket, const void *msg,
                       const int len);

  bool OnStockClose(struct server *srv, const int socket);

  bool OnBroadcastConnect(struct server *srv, const int socket,
                          const void *data, const int len);

  bool OnBroadcastMessage(struct server *srv, const int socket, const void *msg,
                          const int len);

  bool OnBroadcastClose(struct server *srv, const int socket);

  bool OnIniTimer(struct server *srv);

  bool OnTimeout(struct server *srv, char *id, int opcode, int time);

private:
  bool Init();
};
} // namespace quatations_logic

#endif
