//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#include "stock/stock_init.h"
#include "core/common.h"
#include "core/plugins.h"
#include "stock/stock_logic.h"

struct stockplugin {
  char *id;
  char *name;
  char *version;
  char *provider;
};

static void *OnStockStart() {
  signal(SIGPIPE, SIG_IGN);
  struct stockplugin *stock =
      (struct stockplugin *)calloc(1, sizeof(struct stockplugin));
  stock->id = "stock";
  stock->name = "stock";
  stock->version = "1.0.0";
  stock->provider = "kerry";
  if (!stock_logic::Stocklogic::GetInstance())
    assert(0);
  return stock;
}

static handler_t OnStockShutdown(struct server *srv, void *pd) {
  stock_logic::Stocklogic::FreeInstance();

  return HANDLER_GO_ON;
}

static handler_t OnStockConnect(struct server *srv, int fd, void *data,
                                     int len) {
  stock_logic::Stocklogic::GetInstance()->OnStockConnect(srv, fd);
  return HANDLER_GO_ON;
}

static handler_t OnStockMessage(struct server *srv, int fd, void *data,
                                     int len) {
  stock_logic::Stocklogic::GetInstance()->OnStockMessage(srv, fd,
                                                                    data, len);
  return HANDLER_GO_ON;
}

static handler_t OnStockClose(struct server *srv, int fd) {
  stock_logic::Stocklogic::GetInstance()->OnStockClose(srv, fd);
  return HANDLER_GO_ON;
}

static handler_t OnUnknow(struct server *srv, int fd, void *data, int len) {
  return HANDLER_GO_ON;
}

static handler_t OnBroadcastConnect(struct server *srv, int fd, void *data,
                                    int len) {
  stock_logic::Stocklogic::GetInstance()->OnBroadcastConnect(
      srv, fd, data, len);
  return HANDLER_GO_ON;
}

static handler_t OnBroadcastClose(struct server *srv, int fd) {
  stock_logic::Stocklogic::GetInstance()->OnBroadcastClose(srv, fd);
  return HANDLER_GO_ON;
}

static handler_t OnBroadcastMessage(struct server *srv, int fd, void *data,
                                    int len) {
  stock_logic::Stocklogic::GetInstance()->OnBroadcastMessage(
      srv, fd, data, len);
  return HANDLER_GO_ON;
}

static handler_t OnIniTimer(struct server *srv) {
  stock_logic::Stocklogic::GetInstance()->OnIniTimer(srv);
  return HANDLER_GO_ON;
}

static handler_t OnTimeOut(struct server *srv, char *id, int opcode, int time) {
  stock_logic::Stocklogic::GetInstance()->OnTimeout(srv, id, opcode,
                                                              time);
  return HANDLER_GO_ON;
}

int stock_plugin_init(struct plugin *pl) {
  pl->init = OnStockStart;
  pl->clean_up = OnStockShutdown;
  pl->connection = OnStockConnect;
  pl->connection_close = OnStockClose;
  pl->connection_close_srv = OnBroadcastClose;
  pl->connection_srv = OnBroadcastConnect;
  pl->handler_init_time = OnIniTimer;
  pl->handler_read = OnStockMessage;
  pl->handler_read_srv = OnBroadcastMessage;
  pl->handler_read_other = OnUnknow;
  pl->time_msg = OnTimeOut;
  pl->data = NULL;
  return 0;
}
