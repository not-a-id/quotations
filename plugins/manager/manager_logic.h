//  Copyright (c) 2017-2018 The KID Authors. All rights reserved.
//  Created on: 2017年1月9日 Author: kerry
#ifndef QUOTATIONS_GOODS_MANAGER_LOGIC_
#define QUOTATIONS_GOODS_MANAGER_LOGIC_

#define DUMP_PACKET 1

#include "core/common.h"
#include "basic/basictypes.h"
#include "net/comm_head.h"
#include "net/packet_processing.h"
#include "schduler/schduler_engine.h"

namespace manager_logic {

class Managerlogic {
 public:
  Managerlogic();
  virtual ~Managerlogic();

 private:
  static Managerlogic *instance_;

 public:
  static Managerlogic *GetInstance();
  static void FreeInstance();
  bool OnManagerConnect(struct server *srv, const int socket);

  bool OnManagerMessage(struct server *srv, const int socket, const void *msg,
                        const int len);

  bool OnManagerClose(struct server *srv, const int socket);

  bool OnBroadcastConnect(struct server *srv, const int socket,
                          const void *data, const int len);

  bool OnBroadcastMessage(struct server *srv, const int socket, const void *msg,
                          const int len);

  bool OnBroadcastClose(struct server *srv, const int socket);

  bool OnIniTimer(struct server *srv);

  bool OnTimeout(struct server *srv, char* id, int opcode, int time);

 private:
  bool OnApplicationReg(struct server* srv, int socket, struct PacketHead *packet);
 private:
  bool Init();
 private:
  quotations_schduler::SchdulerEngine* schduler_engine_;
  //scoped_ptr<manager_logic::ManagerDB>    manager_db_;
  //crawler_schduler::SchdulerEngine*       crawler_schduler_engine_;
  //scoped_ptr<base_logic::DataControllerEngine>          redis_engine_;
};
}  // namespace manager_logic

#endif
