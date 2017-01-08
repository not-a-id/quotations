//  Copyright (c) 2016-2017 The quotations Authors. All rights reserved.
//  Created on: 2017年1月7日 Author: kerry

#ifndef GOODS_SCHDULER_ENGINE_H__
#define GOODS_SCHDULER_ENGINE_H__

#include "logic/quotations_infos.h"
#include "goods/goods_redis.h"
#include "thread/base_thread_handler.h"
#include "thread/base_thread_lock.h"

#define UPDATE_GOODS_DATA  10001

typedef std::list<quotations_logic::PlatformSymbol> PLATFORM_SYMBOL_LIST;
namespace goods_logic {

class GoodsCache {
 public:
  PLATFORM_SYMBOL_LIST symbol_list_;
};

class GoodsSchdulerManager {
 public:
  GoodsSchdulerManager();
  virtual ~GoodsSchdulerManager();

  void InitRedis(goods_logic::GoodsRedis* goods_redis);

  void TimeEvent(int opcode, int time);
 private:
  void  Init();
  void TimeAchieveGoods();
  bool AchieveGoodsUnit(const int32 type,
                        quotations_logic::Quotations* quotations);
 private:
  goods_logic::GoodsRedis *goods_redis_;
  GoodsCache *goods_cache_;
  struct threadrw_t *lock_;
};

class GoodsSchdulerEngine {
 private:
  static GoodsSchdulerEngine* schduler_engine_;
  static GoodsSchdulerManager* schduler_mgr_;

  GoodsSchdulerEngine() {
  }
  virtual ~GoodsSchdulerEngine() {
  }
 public:
  static GoodsSchdulerManager* GetSchdulerManager() {
    if (schduler_mgr_ == NULL)
      schduler_mgr_ = new GoodsSchdulerManager();
    return schduler_mgr_;
  }

  static GoodsSchdulerEngine* GetGoodsSchdulerEngine() {
    if (schduler_engine_ == NULL)
      schduler_engine_ = new GoodsSchdulerEngine();
    return schduler_engine_;
  }
};
}
#endif
