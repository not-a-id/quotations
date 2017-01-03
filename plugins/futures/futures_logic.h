//  Copyright (c) 2015-2015 The quotation Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#ifndef QUOTATIONS_FUTURES_FUTURES_LOGIC_
#define QUOTATIONS_FUTURES_FUTURES_LOGIC_

#include "basic/basictypes.h"
#include "core/common.h"

namespace futures_logic {

class Futureslogic {
public:
  Futureslogic();
  virtual ~Futureslogic();

private:
  static Futureslogic *instance_;

public:
  static Futureslogic *GetInstance();
  static void FreeInstance();

  bool OnFuturesConnect(struct server *srv, const int socket);

  bool OnFuturesMessage(struct server *srv, const int socket, const void *msg,
                       const int len);

  bool OnFuturesClose(struct server *srv, const int socket);

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
} // namespace futures_logic

#endif
