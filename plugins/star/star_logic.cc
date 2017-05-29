//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年5月28日 Author: kerry

#include "star/star_logic.h"
#include "basic/native_library.h"
#include "config/config.h"
#include "core/common.h"
#include "logic/logic_comm.h"
#include "logic/logic_unit.h"
#include "net/errno.h"
#include <string>

#define DEFAULT_CONFIG_PATH "./plugins/star/star_config.xml"

#define TIME_UPDATE_DATA 10001

namespace star_logic {

Starlogic *Starlogic::instance_ = NULL;

Starlogic::Starlogic() {
  if (!Init())
    assert(0);
}

Starlogic::~Starlogic() {
  if (star_redis_) {
    delete star_redis_;
    star_redis_ = NULL;
  }
  if (star_schduler_) {
    delete star_schduler_;
    star_schduler_ = NULL;
  }
}

bool Starlogic::Init() {
  bool r = false;
  std::string path = DEFAULT_CONFIG_PATH;
  config::FileConfig *config = config::FileConfig::GetFileConfig();
  if (config == NULL)
    return false;
  r = config->LoadConfig(path);
  if (config == NULL)
    return false;
  star_redis_ = new star_logic::StarRedis(config);
  star_schduler_ = star_logic::StarSchdulerEngine::GetSchdulerManager();
  star_schduler_->InitRedis(star_redis_);

  return true;
}

Starlogic *Starlogic::GetInstance() {
  if (instance_ == NULL)
    instance_ = new Starlogic();
  return instance_;
}

void Starlogic::FreeInstance() {
  delete instance_;
  instance_ = NULL;
}

bool Starlogic::OnStarConnect(struct server *srv, const int socket) {
  return true;
}

bool Starlogic::OnStarMessage(struct server *srv, const int socket,
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

bool Starlogic::OnStarClose(struct server *srv, const int socket) {
  return true;
}

bool Starlogic::OnBroadcastConnect(struct server *srv, const int socket,
                                    const void *msg, const int len) {
  return true;
}

bool Starlogic::OnBroadcastMessage(struct server *srv, const int socket,
                                    const void *msg, const int len) {
  return true;
}

bool Starlogic::OnBroadcastClose(struct server *srv, const int socket) {
  return true;
}

bool Starlogic::OnIniTimer(struct server *srv) {
  if (srv->add_time_task != NULL) {
    srv->add_time_task(srv, "star", UPDATE_STAR_DATA, 3, -1);
  }
  return true;
}

bool Starlogic::OnTimeout(struct server *srv, char *id, int opcode, int time) {
  star_schduler_->TimeEvent(opcode, time);
  return true;
}

}  // namespace star_logic
