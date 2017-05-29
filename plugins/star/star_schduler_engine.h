//  Copyright (c) 2016-2017 The quotations Authors. All rights reserved.
//  Created on: 2017年1月7日 Author: kerry

#ifndef STAR_SCHDULER_ENGINE_H__
#define STAR_SCHDULER_ENGINE_H__

#include "logic/quotations_infos.h"
#include "star/star_redis.h"
#include "schduler/schduler_engine.h"
#include "thread/base_thread_handler.h"
#include "thread/base_thread_lock.h"

#define UPDATE_STAR_DATA  10001

typedef std::list<quotations_logic::PlatformSymbol> PLATFORM_SYMBOL_LIST;

namespace star_logic {

class StarCache {
 public:
  PLATFORM_SYMBOL_LIST symbol_list_; //第一版本暂时不做标的匹配，一切根据kafka传来的信息为准
};

class StarSchdulerManager {
 public:
  StarSchdulerManager();
  virtual ~StarSchdulerManager();

  void InitRedis(star_logic::StarRedis* goods_redis);

  void TimeEvent(int opcode, int time);
 private:
  void  Init();
  void TimeAchieveStar();
  bool AchieveStarUnit(const int32 type,
                        quotations_logic::Quotations* quotations);

  void SendStar(quotations_logic::Quotations* quotations);

  void InitStarSymbol();
 private:
  star_logic::StarRedis *star_redis_;
  quotations_schduler::SchdulerEngine* schduler_engine_;
  StarCache *star_cache_;
  struct threadrw_t *lock_;
};

class StarSchdulerEngine {
 private:
  static StarSchdulerEngine* schduler_engine_;
  static StarSchdulerManager* schduler_mgr_;

  StarSchdulerEngine() {
  }
  virtual ~StarSchdulerEngine() {
  }
 public:
  static StarSchdulerManager* GetSchdulerManager() {
    if (schduler_mgr_ == NULL)
      schduler_mgr_ = new StarSchdulerManager();
    return schduler_mgr_;
  }

  static StarSchdulerEngine* GetStarSchdulerEngine() {
    if (schduler_engine_ == NULL)
      schduler_engine_ = new StarSchdulerEngine();
    return schduler_engine_;
  }
};
}
#endif
