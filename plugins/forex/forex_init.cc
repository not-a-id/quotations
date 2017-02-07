//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#include "forex/forex_init.h"
#include "core/common.h"
#include "core/plugins.h"
#include "forex/forex_logic.h"

struct forexplugin {
  char *id;
  char *name;
  char *version;
  char *provider;
};

static void *OnForexStart() {
  signal(SIGPIPE, SIG_IGN);
  struct forexplugin *forex =
      (struct forexplugin *)calloc(1, sizeof(struct forexplugin));
  forex->id = "forex";
  forex->name = "forex";
  forex->version = "1.0.0";
  forex->provider = "kerry";
  if (!forex_logic::Forexlogic::GetInstance())
    assert(0);
  return forex;
}

static handler_t OnForexShutdown(struct server *srv, void *pd) {
  forex_logic::Forexlogic::FreeInstance();

  return HANDLER_GO_ON;
}

static handler_t OnForexConnect(struct server *srv, int fd, void *data,
                                     int len) {
  forex_logic::Forexlogic::GetInstance()->OnForexConnect(srv, fd);
  return HANDLER_GO_ON;
}

static handler_t OnForexMessage(struct server *srv, int fd, void *data,
                                     int len) {
  forex_logic::Forexlogic::GetInstance()->OnForexMessage(srv, fd,
                                                                    data, len);
  return HANDLER_GO_ON;
}

static handler_t OnForexClose(struct server *srv, int fd) {
  forex_logic::Forexlogic::GetInstance()->OnForexClose(srv, fd);
  return HANDLER_GO_ON;
}

static handler_t OnUnknow(struct server *srv, int fd, void *data, int len) {
  return HANDLER_GO_ON;
}

static handler_t OnBroadcastConnect(struct server *srv, int fd, void *data,
                                    int len) {
  forex_logic::Forexlogic::GetInstance()->OnBroadcastConnect(
      srv, fd, data, len);
  return HANDLER_GO_ON;
}

static handler_t OnBroadcastClose(struct server *srv, int fd) {
  forex_logic::Forexlogic::GetInstance()->OnBroadcastClose(srv, fd);
  return HANDLER_GO_ON;
}

static handler_t OnBroadcastMessage(struct server *srv, int fd, void *data,
                                    int len) {
  forex_logic::Forexlogic::GetInstance()->OnBroadcastMessage(
      srv, fd, data, len);
  return HANDLER_GO_ON;
}

static handler_t OnIniTimer(struct server *srv) {
  forex_logic::Forexlogic::GetInstance()->OnIniTimer(srv);
  return HANDLER_GO_ON;
}

static handler_t OnTimeOut(struct server *srv, char *id, int opcode, int time) {
  forex_logic::Forexlogic::GetInstance()->OnTimeout(srv, id, opcode,
                                                              time);
  return HANDLER_GO_ON;
}

int forex_plugin_init(struct plugin *pl) {
  pl->init = OnForexStart;
  pl->clean_up = OnForexShutdown;
  pl->connection = OnForexConnect;
  pl->connection_close = OnForexClose;
  pl->connection_close_srv = OnBroadcastClose;
  pl->connection_srv = OnBroadcastConnect;
  pl->handler_init_time = OnIniTimer;
  pl->handler_read = OnForexMessage;
  pl->handler_read_srv = OnBroadcastMessage;
  pl->handler_read_other = OnUnknow;
  pl->time_msg = OnTimeOut;
  pl->data = NULL;
  return 0;
}
