//  Copyright (c) 2015-2015 The SWP Authors. All rights reserved.
//  Created on: 2016年12月30日 Author: kerry

#include "futures/futures_init.h"
#include "core/common.h"
#include "core/plugins.h"
#include "futures/futures_logic.h"

struct futuresplugin {
  char *id;
  char *name;
  char *version;
  char *provider;
};

static void *OnFuturesStart() {
  signal(SIGPIPE, SIG_IGN);
  struct futuresplugin *futures =
      (struct futuresplugin *)calloc(1, sizeof(struct futuresplugin));
  futures->id = "futures";
  futures->name = "futures";
  futures->version = "1.0.0";
  futures->provider = "kerry";
  if (!futures_logic::Futureslogic::GetInstance())
    assert(0);
  return futures;
}

static handler_t OnFuturesShutdown(struct server *srv, void *pd) {
  futures_logic::Futureslogic::FreeInstance();

  return HANDLER_GO_ON;
}

static handler_t OnFuturesConnect(struct server *srv, int fd, void *data,
                                     int len) {
  futures_logic::Futureslogic::GetInstance()->OnFuturesConnect(srv, fd);
  return HANDLER_GO_ON;
}

static handler_t OnFuturesMessage(struct server *srv, int fd, void *data,
                                     int len) {
  futures_logic::Futureslogic::GetInstance()->OnFuturesMessage(srv, fd,
                                                                    data, len);
  return HANDLER_GO_ON;
}

static handler_t OnFuturesClose(struct server *srv, int fd) {
  futures_logic::Futureslogic::GetInstance()->OnFuturesClose(srv, fd);
  return HANDLER_GO_ON;
}

static handler_t OnUnknow(struct server *srv, int fd, void *data, int len) {
  return HANDLER_GO_ON;
}

static handler_t OnBroadcastConnect(struct server *srv, int fd, void *data,
                                    int len) {
  futures_logic::Futureslogic::GetInstance()->OnBroadcastConnect(
      srv, fd, data, len);
  return HANDLER_GO_ON;
}

static handler_t OnBroadcastClose(struct server *srv, int fd) {
  futures_logic::Futureslogic::GetInstance()->OnBroadcastClose(srv, fd);
  return HANDLER_GO_ON;
}

static handler_t OnBroadcastMessage(struct server *srv, int fd, void *data,
                                    int len) {
  futures_logic::Futureslogic::GetInstance()->OnBroadcastMessage(
      srv, fd, data, len);
  return HANDLER_GO_ON;
}

static handler_t OnIniTimer(struct server *srv) {
  futures_logic::Futureslogic::GetInstance()->OnIniTimer(srv);
  return HANDLER_GO_ON;
}

static handler_t OnTimeOut(struct server *srv, char *id, int opcode, int time) {
  futures_logic::Futureslogic::GetInstance()->OnTimeout(srv, id, opcode,
                                                              time);
  return HANDLER_GO_ON;
}

int futures_plugin_init(struct plugin *pl) {
  pl->init = OnFuturesStart;
  pl->clean_up = OnFuturesShutdown;
  pl->connection = OnFuturesConnect;
  pl->connection_close = OnFuturesClose;
  pl->connection_close_srv = OnBroadcastClose;
  pl->connection_srv = OnBroadcastConnect;
  pl->handler_init_time = OnIniTimer;
  pl->handler_read = OnFuturesMessage;
  pl->handler_read_srv = OnBroadcastMessage;
  pl->handler_read_other = OnUnknow;
  pl->time_msg = OnTimeOut;
  pl->data = NULL;
  return 0;
}
