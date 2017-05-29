//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年5月28日 Author: kerry

#include "star/star_init.h"
#include "core/common.h"
#include "core/plugins.h"
#include "star/star_logic.h"

struct starplugin {
  char *id;
  char *name;
  char *version;
  char *provider;
};

static void *OnStarStart() {
  signal(SIGPIPE, SIG_IGN);
  struct starplugin *star =
      (struct starplugin *)calloc(1, sizeof(struct starplugin));
  star->id = "star";
  star->name = "star";
  star->version = "1.0.0";
  star->provider = "kerry";
  if (!star_logic::Starlogic::GetInstance())
    assert(0);
  return star;
}

static handler_t OnStarShutdown(struct server *srv, void *pd) {
  star_logic::Starlogic::FreeInstance();

  return HANDLER_GO_ON;
}

static handler_t OnStarConnect(struct server *srv, int fd, void *data,
                                     int len) {
  star_logic::Starlogic::GetInstance()->OnStarConnect(srv, fd);
  return HANDLER_GO_ON;
}

static handler_t OnStarMessage(struct server *srv, int fd, void *data,
                                     int len) {
  star_logic::Starlogic::GetInstance()->OnStarMessage(srv, fd,
                                                                    data, len);
  return HANDLER_GO_ON;
}

static handler_t OnStarClose(struct server *srv, int fd) {
  star_logic::Starlogic::GetInstance()->OnStarClose(srv, fd);
  return HANDLER_GO_ON;
}

static handler_t OnUnknow(struct server *srv, int fd, void *data, int len) {
  return HANDLER_GO_ON;
}

static handler_t OnBroadcastConnect(struct server *srv, int fd, void *data,
                                    int len) {
  star_logic::Starlogic::GetInstance()->OnBroadcastConnect(
      srv, fd, data, len);
  return HANDLER_GO_ON;
}

static handler_t OnBroadcastClose(struct server *srv, int fd) {
  star_logic::Starlogic::GetInstance()->OnBroadcastClose(srv, fd);
  return HANDLER_GO_ON;
}

static handler_t OnBroadcastMessage(struct server *srv, int fd, void *data,
                                    int len) {
  star_logic::Starlogic::GetInstance()->OnBroadcastMessage(
      srv, fd, data, len);
  return HANDLER_GO_ON;
}

static handler_t OnIniTimer(struct server *srv) {
  star_logic::Starlogic::GetInstance()->OnIniTimer(srv);
  return HANDLER_GO_ON;
}

static handler_t OnTimeOut(struct server *srv, char *id, int opcode, int time) {
  star_logic::Starlogic::GetInstance()->OnTimeout(srv, id, opcode,
                                                              time);
  return HANDLER_GO_ON;
}

int star_plugin_init(struct plugin *pl) {
  pl->init = OnStarStart;
  pl->clean_up = OnStarShutdown;
  pl->connection = OnStarConnect;
  pl->connection_close = OnStarClose;
  pl->connection_close_srv = OnBroadcastClose;
  pl->connection_srv = OnBroadcastConnect;
  pl->handler_init_time = OnIniTimer;
  pl->handler_read = OnStarMessage;
  pl->handler_read_srv = OnBroadcastMessage;
  pl->handler_read_other = OnUnknow;
  pl->time_msg = OnTimeOut;
  pl->data = NULL;
  return 0;
}
