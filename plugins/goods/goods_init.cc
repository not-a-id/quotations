//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#include "goods/goods_init.h"
#include "core/common.h"
#include "core/plugins.h"
#include "goods/goods_logic.h"

struct goodsplugin {
  char *id;
  char *name;
  char *version;
  char *provider;
};

static void *OnGoodsStart() {
  signal(SIGPIPE, SIG_IGN);
  struct goodsplugin *goods =
      (struct goodsplugin *)calloc(1, sizeof(struct goodsplugin));
  goods->id = "goods";
  goods->name = "goods";
  goods->version = "1.0.0";
  goods->provider = "kerry";
  if (!goods_logic::Goodslogic::GetInstance())
    assert(0);
  return goods;
}

static handler_t OnGoodsShutdown(struct server *srv, void *pd) {
  goods_logic::Goodslogic::FreeInstance();

  return HANDLER_GO_ON;
}

static handler_t OnGoodsConnect(struct server *srv, int fd, void *data,
                                     int len) {
  goods_logic::Goodslogic::GetInstance()->OnGoodsConnect(srv, fd);
  return HANDLER_GO_ON;
}

static handler_t OnGoodsMessage(struct server *srv, int fd, void *data,
                                     int len) {
  goods_logic::Goodslogic::GetInstance()->OnGoodsMessage(srv, fd,
                                                                    data, len);
  return HANDLER_GO_ON;
}

static handler_t OnGoodsClose(struct server *srv, int fd) {
  goods_logic::Goodslogic::GetInstance()->OnGoodsClose(srv, fd);
  return HANDLER_GO_ON;
}

static handler_t OnUnknow(struct server *srv, int fd, void *data, int len) {
  return HANDLER_GO_ON;
}

static handler_t OnBroadcastConnect(struct server *srv, int fd, void *data,
                                    int len) {
  goods_logic::Goodslogic::GetInstance()->OnBroadcastConnect(
      srv, fd, data, len);
  return HANDLER_GO_ON;
}

static handler_t OnBroadcastClose(struct server *srv, int fd) {
  goods_logic::Goodslogic::GetInstance()->OnBroadcastClose(srv, fd);
  return HANDLER_GO_ON;
}

static handler_t OnBroadcastMessage(struct server *srv, int fd, void *data,
                                    int len) {
  goods_logic::Goodslogic::GetInstance()->OnBroadcastMessage(
      srv, fd, data, len);
  return HANDLER_GO_ON;
}

static handler_t OnIniTimer(struct server *srv) {
  goods_logic::Goodslogic::GetInstance()->OnIniTimer(srv);
  return HANDLER_GO_ON;
}

static handler_t OnTimeOut(struct server *srv, char *id, int opcode, int time) {
  goods_logic::Goodslogic::GetInstance()->OnTimeout(srv, id, opcode,
                                                              time);
  return HANDLER_GO_ON;
}

int goods_plugin_init(struct plugin *pl) {
  pl->init = OnGoodsStart;
  pl->clean_up = OnGoodsShutdown;
  pl->connection = OnGoodsConnect;
  pl->connection_close = OnGoodsClose;
  pl->connection_close_srv = OnBroadcastClose;
  pl->connection_srv = OnBroadcastConnect;
  pl->handler_init_time = OnIniTimer;
  pl->handler_read = OnGoodsMessage;
  pl->handler_read_srv = OnBroadcastMessage;
  pl->handler_read_other = OnUnknow;
  pl->time_msg = OnTimeOut;
  pl->data = NULL;
  return 0;
}
