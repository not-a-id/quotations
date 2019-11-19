//  Copyright (c) 2016-2017 The quotations Authors. All rights reserved.
//  Created on: 2017年1月7日 Author: kerry

#include "forex/forex_schduler_engine.h"
#include "forex/pull_engine.h"
//#include "forex/forex_proto_buf.h"
#include "net/comm_head.h"
#include "net/packet_processing.h"
#include "net/quotations_proto.h"
#include "logic/logic_unit.h"

namespace forex_logic {

ForexSchdulerManager* ForexSchdulerEngine::schduler_mgr_ = NULL;
ForexSchdulerEngine* ForexSchdulerEngine::schduler_engine_ = NULL;

ForexSchdulerManager::ForexSchdulerManager()
    : forex_redis_(NULL) {
  forex_cache_ = new ForexCache();
  Init();
}

ForexSchdulerManager::~ForexSchdulerManager() {
  DeinitThreadrw(lock_);
  forex_cache_->symbol_list_.clear();
  if (forex_cache_) {
    delete forex_cache_;
    forex_cache_ = NULL;
  }
}

void ForexSchdulerManager::Init() {
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

  InitForexSymbol();
}

void ForexSchdulerManager::InitForexSymbol() {

  quotations_logic::PlatformSymbol sina_eurusd;
  sina_eurusd.set_platform_type(SINA_TYPE);
  sina_eurusd.set_platform_name("SINA");
  sina_eurusd.set_exchange_name("SINA");
  sina_eurusd.set_show_name("EUR-USD");
  sina_eurusd.set_symbol("fx_seurusd");
  forex_cache_->symbol_list_.push_back(sina_eurusd);
}

void ForexSchdulerManager::InitRedis(forex_logic::ForexRedis* forex_redis) {
  forex_redis_ = forex_redis;
}

void ForexSchdulerManager::TimeEvent(int opcode, int time) {
  switch (opcode) {
    case UPDATE_FOREX_DATA: {
      TimeAchieveForex();
      break;
    }
    default:
      break;
  }
}

void ForexSchdulerManager::TimeAchieveForex() {
  bool r = false;
  base_logic::RLockGd lk(lock_);
  PLATFORM_SYMBOL_LIST::iterator it = forex_cache_->symbol_list_.begin();
  for (; it != forex_cache_->symbol_list_.end(); ++it) {
    quotations_logic::Quotations quotations;
    quotations_logic::PlatformSymbol symbol = (*it);
    quotations.set_platform_name(symbol.platform_name());
    quotations.set_symbol(symbol.symbol());
    quotations.set_exchange_name(symbol.exchange_name());
    r = AchieveForexUnit(symbol.platform_type(), &quotations);
  }
}

bool ForexSchdulerManager::AchieveForexUnit(
    const int32 type, quotations_logic::Quotations* quotations) {
  bool r = false;
  forex_logic::PullEngine* engine = forex_logic::PullEngine::Create(type);
  r = engine->RequestData(quotations->exchange_name(), quotations->symbol(),
                          quotations);
  if (!r)
    return false;
  //暂时保留每个时间段的第一秒的数据
  int32 remainder = quotations->current_unix_time() % 60;

  if (remainder <= 10) {
    //写入redis
    r = forex_redis_->RealTimeForexData((*quotations));
    LOG_DEBUG2("symbol %s||current %lld||remainder %d",
               quotations->symbol().c_str(),
               quotations->current_unix_time(),
               remainder);
  }
  SendForex(quotations);
  if (engine) {
    delete engine;
    engine = NULL;
  }
  return r;
}

void ForexSchdulerManager::SendForex(quotations_logic::Quotations* quotations) {
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
