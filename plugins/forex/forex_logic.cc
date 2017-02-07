//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#include "forex/forex_logic.h"
#include "basic/native_library.h"
#include "config/config.h"
#include "core/common.h"
#include "logic/logic_comm.h"
#include "logic/logic_unit.h"
#include "net/errno.h"
#include <string>

#define DEFAULT_CONFIG_PATH "./plugins/forex/forex_config.xml"

#define TIME_UPDATE_DATA 10001

namespace forex_logic {

Forexlogic *Forexlogic::instance_ = NULL;

Forexlogic::Forexlogic() {
  if (!Init())
    assert(0);
}

Forexlogic::~Forexlogic() {
  if (forex_redis_) {
    delete forex_redis_;
    forex_redis_ = NULL;
  }
  if (forex_schduler_) {
    delete forex_schduler_;
    forex_schduler_ = NULL;
  }
}

bool Forexlogic::Init() {
  bool r = false;
  std::string path = DEFAULT_CONFIG_PATH;
  config::FileConfig *config = config::FileConfig::GetFileConfig();
  if (config == NULL)
    return false;
  r = config->LoadConfig(path);
  if (config == NULL)
    return false;
  forex_redis_ = new forex_logic::ForexRedis(config);
  forex_schduler_ = forex_logic::ForexSchdulerEngine::GetSchdulerManager();
  forex_schduler_->InitRedis(forex_redis_);

  return true;
}

Forexlogic *Forexlogic::GetInstance() {
  if (instance_ == NULL)
    instance_ = new Forexlogic();
  return instance_;
}

void Forexlogic::FreeInstance() {
  delete instance_;
  instance_ = NULL;
}

bool Forexlogic::OnForexConnect(struct server *srv, const int socket) {
  return true;
}

bool Forexlogic::OnForexMessage(struct server *srv, const int socket,
                                const void *msg, const int len) {
  bool r = false;
  struct PacketHead *packet = NULL;
  if (srv == NULL || socket < 0 || msg == NULL || len < PACKET_HEAD_LENGTH)
    return false;

  switch (packet->operate_code) {
    default:
      break;
  }
  return true;
}

bool Forexlogic::OnForexClose(struct server *srv, const int socket) {
  return true;
}

bool Forexlogic::OnBroadcastConnect(struct server *srv, const int socket,
                                    const void *msg, const int len) {
  return true;
}

bool Forexlogic::OnBroadcastMessage(struct server *srv, const int socket,
                                    const void *msg, const int len) {
  return true;
}

bool Forexlogic::OnBroadcastClose(struct server *srv, const int socket) {
  return true;
}

bool Forexlogic::OnIniTimer(struct server *srv) {
  if (srv->add_time_task != NULL) {
    srv->add_time_task(srv, "forex", UPDATE_FOREX_DATA, 3, -1);
  }
  return true;
}

bool Forexlogic::OnTimeout(struct server *srv, char *id, int opcode, int time) {
  forex_schduler_->TimeEvent(opcode, time);
  return true;
}

}  // namespace forex_logic
