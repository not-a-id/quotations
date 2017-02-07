//  Copyright (c) 2017-2018 The QUOTATIONS Authors. All rights reserved.
//  Created on: 2017年1月9日 Author: kerry
#include "manager/manager_logic.h"
#include "manager/manager_proto_buf.h"
#include "manager/operator_code.h"
#include "net/comm_head.h"
#include "core/common.h"
#include "logic/logic_comm.h"
#include "logic/logic_unit.h"
#include "config/config.h"
#include <string>

#define DEFAULT_CONFIG_PATH "./plugins/manager/manager_config.xml"

#define TIME_CRALWER_MANAGER_LIVE 10000

namespace manager_logic {

Managerlogic *Managerlogic::instance_ = NULL;

Managerlogic::Managerlogic() {
  if (!Init())
    assert(0);
}

Managerlogic::~Managerlogic() {
}

bool Managerlogic::Init() {
  bool r = false;
  quotations_schduler::SchdulerEngine* (*schduler_engine)(void);
  std::string path = DEFAULT_CONFIG_PATH;
  config::FileConfig *config = config::FileConfig::GetFileConfig();
  if (config == NULL)
    return false;
  r = config->LoadConfig(path);

  std::string schduler_library = "./connection_schduler/connection_schduler.so";
  std::string schduler_func = "GetConnectionSchdulerEngine";
  schduler_engine = (quotations_schduler::SchdulerEngine* (*)(void))
  logic::SomeUtils::GetLibraryFunction(
  schduler_library, schduler_func);schduler_engine_
  = (*schduler_engine)();
  if (schduler_engine_ == NULL)
    assert(0);
  return true;
}

Managerlogic *Managerlogic::GetInstance() {
  if (instance_ == NULL)
    instance_ = new Managerlogic();
  return instance_;
}

void Managerlogic::FreeInstance() {
  delete instance_;
  instance_ = NULL;
}

bool Managerlogic::OnManagerConnect(struct server *srv, const int socket) {
  return true;
}

bool Managerlogic::OnManagerMessage(struct server *srv, const int socket,
                                    const void *msg, const int len) {
  bool r = false;
  struct PacketHead *packet = NULL;
  if (srv == NULL || socket < 0 || msg == NULL || len < PACKET_HEAD_LENGTH)
    return false;

  if (!net::PacketProsess::UnpackStream(msg, len, &packet)) {
    LOG_ERROR2("UnpackStream Error socket %d", socket);
    return false;
  }

  assert(packet);

  switch (packet->operate_code) {
    case USER_APPLICATION_LOGIN: {
      OnApplicationReg(srv, socket, packet);
      break;
    }
    default:
      break;
  }
  return true;
}

bool Managerlogic::OnManagerClose(struct server *srv, const int socket) {
  schduler_engine_->CloseConnectionSchduler(socket);
  return true;
}

bool Managerlogic::OnBroadcastConnect(struct server *srv, const int socket,
                                      const void *msg, const int len) {
  return true;
}

bool Managerlogic::OnBroadcastMessage(struct server *srv, const int socket,
                                      const void *msg, const int len) {
  return true;
}

bool Managerlogic::OnBroadcastClose(struct server *srv, const int socket) {
  return true;
}

bool Managerlogic::OnIniTimer(struct server *srv) {
  if (srv->add_time_task != NULL) {
    srv->add_time_task(srv, "manager", TIME_CRALWER_MANAGER_LIVE, 60, -1);
  }
  return true;
}

bool Managerlogic::OnTimeout(struct server *srv, char *id, int opcode,
                             int time) {
  switch (opcode) {
    case TIME_CRALWER_MANAGER_LIVE:
      //crawler_schduler_engine_->CheckHeartPacket(0);
      break;
    default:
      break;
  }
  return true;
}

bool Managerlogic::OnApplicationReg(struct server* srv, int socket,
                                    struct PacketHead *packet) {
  struct PacketControl* packet_control = (struct PacketControl*) (packet);
  manager_logic::net_request::Login request_login;
  request_login.set_http_packet(packet_control->body_);
  std::string ip;
  int port;
  logic::SomeUtils::GetIPAddress(socket, ip, port);
  quotations_logic::ConnectionSchduler scheduler;
  scheduler.set_id(request_login.aid());
  scheduler.set_ip(ip);
  scheduler.set_is_effective(true);
  scheduler.set_socket(socket);
  scheduler.set_type(request_login.a_type());
  scheduler.set_password(request_login.password());
  schduler_engine_->SetConnectionSchduler(request_login.aid(), &scheduler);
  LOG_DEBUG2("ip:{%s} port:{%d} aid:{%ld} password:{%s}",
      ip.c_str(), port, request_login.aid(), request_login.password().c_str());
  return true;

}

}  // namespace manager_logic
