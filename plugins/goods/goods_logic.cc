//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#include "goods/goods_logic.h"
#include "basic/native_library.h"
#include "config/config.h"
#include "core/common.h"
#include "logic/logic_comm.h"
#include "logic/logic_unit.h"
#include "net/errno.h"
#include <string>

#define DEFAULT_CONFIG_PATH "./plugins/goods/goods_config.xml"

namespace goods_logic {

Goodslogic *Goodslogic::instance_ = NULL;

Goodslogic::Goodslogic() {
  if (!Init())
    assert(0);
}

Goodslogic::~Goodslogic() {}

bool Goodslogic::Init() {
  bool r = false;
  std::string path = DEFAULT_CONFIG_PATH;
  config::FileConfig *config = config::FileConfig::GetFileConfig();
  if (config == NULL)
    return false;
  r = config->LoadConfig(path);
  return true;
}

Goodslogic *Goodslogic::GetInstance() {
  if (instance_ == NULL)
    instance_ = new Goodslogic();
  return instance_;
}

void Goodslogic::FreeInstance() {
  delete instance_;
  instance_ = NULL;
}

bool Goodslogic::OnGoodsConnect(struct server *srv, const int socket) {
  return true;
}

bool Goodslogic::OnGoodsMessage(struct server *srv, const int socket,
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

bool Goodslogic::OnGoodsClose(struct server *srv, const int socket) {
  return true;
}

bool Goodslogic::OnBroadcastConnect(struct server *srv, const int socket,
                                     const void *msg, const int len) {
  return true;
}

bool Goodslogic::OnBroadcastMessage(struct server *srv, const int socket,
                                     const void *msg, const int len) {
  return true;
}

bool Goodslogic::OnBroadcastClose(struct server *srv, const int socket) {
  return true;
}

bool Goodslogic::OnIniTimer(struct server *srv) {
  if (srv->add_time_task != NULL) {
  }
  return true;
}

bool Goodslogic::OnTimeout(struct server *srv, char *id, int opcode,
                            int time) {
  switch (opcode) {
  default:
    break;
  }
  return true;
}

} // namespace goods_logic
