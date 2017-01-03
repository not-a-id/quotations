//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#include "stock/stock_logic.h"
#include "basic/native_library.h"
#include "config/config.h"
#include "core/common.h"
#include "logic/logic_comm.h"
#include "logic/logic_unit.h"
#include "net/errno.h"
#include <string>

#define DEFAULT_CONFIG_PATH "./plugins/stock/stock_config.xml"

namespace stock_logic {

Stocklogic *Stocklogic::instance_ = NULL;

Stocklogic::Stocklogic() {
  if (!Init())
    assert(0);
}

Stocklogic::~Stocklogic() {}

bool Stocklogic::Init() {
  bool r = false;
  std::string path = DEFAULT_CONFIG_PATH;
  config::FileConfig *config = config::FileConfig::GetFileConfig();
  if (config == NULL)
    return false;
  r = config->LoadConfig(path);
  return true;
}

Stocklogic *Stocklogic::GetInstance() {
  if (instance_ == NULL)
    instance_ = new Stocklogic();
  return instance_;
}

void Stocklogic::FreeInstance() {
  delete instance_;
  instance_ = NULL;
}

bool Stocklogic::OnStockConnect(struct server *srv, const int socket) {
  return true;
}

bool Stocklogic::OnStockMessage(struct server *srv, const int socket,
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

bool Stocklogic::OnStockClose(struct server *srv, const int socket) {
  return true;
}

bool Stocklogic::OnBroadcastConnect(struct server *srv, const int socket,
                                     const void *msg, const int len) {
  return true;
}

bool Stocklogic::OnBroadcastMessage(struct server *srv, const int socket,
                                     const void *msg, const int len) {
  return true;
}

bool Stocklogic::OnBroadcastClose(struct server *srv, const int socket) {
  return true;
}

bool Stocklogic::OnIniTimer(struct server *srv) {
  if (srv->add_time_task != NULL) {
  }
  return true;
}

bool Stocklogic::OnTimeout(struct server *srv, char *id, int opcode,
                            int time) {
  switch (opcode) {
  default:
    break;
  }
  return true;
}

} // namespace stock_logic
