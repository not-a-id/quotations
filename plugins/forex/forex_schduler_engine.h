//  Copyright (c) 2016-2017 The quotations Authors. All rights reserved.
//  Created on: 2017年1月7日 Author: kerry

#ifndef FOREX_SCHDULER_ENGINE_H__
#define FOREX_SCHDULER_ENGINE_H__

#include "logic/quotations_infos.h"
#include "forex/forex_redis.h"
#include "schduler/schduler_engine.h"
#include "thread/base_thread_handler.h"
#include "thread/base_thread_lock.h"

#define UPDATE_FOREX_DATA  10001

typedef std::list<quotations_logic::PlatformSymbol> PLATFORM_SYMBOL_LIST;

namespace forex_logic {

class ForexCache {
 public:
  PLATFORM_SYMBOL_LIST symbol_list_;
};

class ForexSchdulerManager {
 public:
  ForexSchdulerManager();
  virtual ~ForexSchdulerManager();

  void InitRedis(forex_logic::ForexRedis* goods_redis);

  void TimeEvent(int opcode, int time);
 private:
  void  Init();
  void TimeAchieveForex();
  bool AchieveForexUnit(const int32 type,
                        quotations_logic::Quotations* quotations);

  void SendForex(quotations_logic::Quotations* quotations);

  void InitForexSymbol();
 private:
  forex_logic::ForexRedis *forex_redis_;
  quotations_schduler::SchdulerEngine* schduler_engine_;
  ForexCache *forex_cache_;
  struct threadrw_t *lock_;
};

class ForexSchdulerEngine {
 private:
  static ForexSchdulerEngine* schduler_engine_;
  static ForexSchdulerManager* schduler_mgr_;

  ForexSchdulerEngine() {
  }
  virtual ~ForexSchdulerEngine() {
  }
 public:
  static ForexSchdulerManager* GetSchdulerManager() {
    if (schduler_mgr_ == NULL)
      schduler_mgr_ = new ForexSchdulerManager();
    return schduler_mgr_;
  }

  static ForexSchdulerEngine* GetForexSchdulerEngine() {
    if (schduler_engine_ == NULL)
      schduler_engine_ = new ForexSchdulerEngine();
    return schduler_engine_;
  }
};
}
#endif
