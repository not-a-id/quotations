//  Copyright (c) 2016-2017 The quotations Authors. All rights reserved.
//  Created on: 2017年1月7日 Author: kerry

#include "star/star_schduler_engine.h"
#include "star/pull_engine.h"
#include "net/comm_head.h"
#include "net/packet_processing.h"
#include "net/quotations_proto.h"
#include "logic/logic_unit.h"

namespace star_logic {

StarSchdulerManager* StarSchdulerEngine::schduler_mgr_ = NULL;
StarSchdulerEngine* StarSchdulerEngine::schduler_engine_ = NULL;

StarSchdulerManager::StarSchdulerManager()
    : star_redis_(NULL) {
  star_cache_ = new StarCache();
  Init();
}

StarSchdulerManager::~StarSchdulerManager() {
  DeinitThreadrw(lock_);
  star_cache_->symbol_list_.clear();
  if (star_cache_) {
    delete star_cache_;
    star_cache_ = NULL;
  }
}

void StarSchdulerManager::Init() {
  InitThreadrw(&lock_);

  bool r = false;
  quotations_schduler::SchdulerEngine* (*schduler_engine)(void);

  std::string schduler_library = "./connection_schduler/connection_schduler.so";
  std::string schduler_func = "GetConnectionSchdulerEngine";
  schduler_engine = (quotations_schduler::SchdulerEngine* (*)(void))
  logic::SomeUtils::GetLibraryFunction(
  schduler_library, schduler_func);schduler_engine_
  = (*schduler_engine)();
  if (schduler_engine_ == NULL)
    assert(0);

  InitStarSymbol();
}

void StarSchdulerManager::InitStarSymbol() {
//读取有效的明星标的
}

void StarSchdulerManager::InitRedis(star_logic::StarRedis* star_redis) {
  star_redis_ = star_redis;
}

void StarSchdulerManager::TimeEvent(int opcode, int time) {
  switch (opcode) {
    case UPDATE_FOREX_DATA: {
      TimeAchieveStar();
      break;
    }
    default:
      break;
  }
}

void StarSchdulerManager::TimeAchieveStar() {
  /*bool r = false;
  base_logic::RLockGd lk(lock_);
  PLATFORM_SYMBOL_LIST::iterator it = star_cache_->symbol_list_.begin();
  for (; it != star_cache_->symbol_list_.end(); ++it) {
    quotations_logic::Quotations quotations;
    quotations_logic::PlatformSymbol symbol = (*it);
    quotations.set_platform_name(symbol.platform_name());
    quotations.set_symbol(symbol.symbol());
    quotations.set_exchange_name(symbol.exchange_name());
    r = AchieveStarUnit(symbol.platform_type(), &quotations);
  }*/
}

bool StarSchdulerManager::AchieveStarUnit(
    const int32 type, quotations_logic::Quotations* quotations) {
 /* bool r = false;
  star_logic::PullEngine* engine = star_logic::PullEngine::Create(type);
  r = engine->RequestData(quotations->exchange_name(), quotations->symbol(),
                          quotations);
  if (!r)
    return false;
  //暂时保留每个时间段的第一秒的数据
  int32 remainder = quotations->current_unix_time() % 60;

  if (remainder <= 10) {
    //写入redis
    r = star_redis_->RealTimeStarData((*quotations));
    LOG_DEBUG2("symbol %s||current %lld||remainder %d",
               quotations->symbol().c_str(),
               quotations->current_unix_time(),
               remainder);
  }
  SendStar(quotations);
  if (engine) {
    delete engine;
    engine = NULL;
  }
  return r;
  */
}

void StarSchdulerManager::SendStar(quotations_logic::Quotations* quotations) {
  struct PacketControl packet_control;
  MAKE_HEAD(packet_control, 1001, 1, 0, 0, 0);
  quotations_logic::net_reply::RealTime real_time;
  real_time.set_change(quotations->change());
  real_time.set_pchg(quotations->pchg());
  real_time.set_opening_today_price(quotations->opening_today_price());
  real_time.set_closed_yesterday_price(quotations->closed_yesterday_price());
  real_time.set_current_price(quotations->current_price());
  real_time.set_current_unix_time(quotations->current_unix_time());
  real_time.set_high_price(quotations->high_price());
  real_time.set_low_price(quotations->low_price());
  real_time.set_type(quotations_logic::FOREX_TYPE);
  real_time.set_exchange_name(quotations->exchange_name());
  real_time.set_platform_name(quotations->platform());
  real_time.set_symbol(quotations->symbol());
  packet_control.body_ = real_time.get();
  schduler_engine_->SendAllQuotations(&packet_control, 0, quotations_logic::FOREX_TYPE);
}

}
