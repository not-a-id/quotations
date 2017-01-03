//  Copyright (c) 2015-2015 The quotation Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#include "futures/futures_logic.h"
#include "basic/native_library.h"
#include "config/config.h"
#include "core/common.h"
#include "logic/logic_comm.h"
#include "logic/logic_unit.h"
#include "net/errno.h"
#include <string>

#define DEFAULT_CONFIG_PATH "./plugins/futures/futures_config.xml"

namespace futures_logic {

Futureslogic *Futureslogic::instance_ = NULL;

Futureslogic::Futureslogic() {
  if (!Init())
    assert(0);
}

Futureslogic::~Futureslogic() {}

bool Futureslogic::Init() {
  bool r = false;
  std::string path = DEFAULT_CONFIG_PATH;
  config::FileConfig *config = config::FileConfig::GetFileConfig();
  if (config == NULL)
    return false;
  r = config->LoadConfig(path);
  return true;
}

Futureslogic *Futureslogic::GetInstance() {
  if (instance_ == NULL)
    instance_ = new Futureslogic();
  return instance_;
}

void Futureslogic::FreeInstance() {
  delete instance_;
  instance_ = NULL;
}

bool Futureslogic::OnFuturesConnect(struct server *srv, const int socket) {
  return true;
}

bool Futureslogic::OnFuturesMessage(struct server *srv, const int socket,
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

bool Futureslogic::OnFuturesClose(struct server *srv, const int socket) {
  return true;
}

bool Futureslogic::OnBroadcastConnect(struct server *srv, const int socket,
                                     const void *msg, const int len) {
  return true;
}

bool Futureslogic::OnBroadcastMessage(struct server *srv, const int socket,
                                     const void *msg, const int len) {
  return true;
}

bool Futureslogic::OnBroadcastClose(struct server *srv, const int socket) {
  return true;
}

bool Futureslogic::OnIniTimer(struct server *srv) {
  if (srv->add_time_task != NULL) {
  }
  return true;
}

bool Futureslogic::OnTimeout(struct server *srv, char *id, int opcode,
                            int time) {
  switch (opcode) {
  default:
    break;
  }
  return true;
}

} // namespace futures_logic
