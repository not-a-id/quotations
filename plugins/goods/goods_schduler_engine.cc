//  Copyright (c) 2016-2017 The quotations Authors. All rights reserved.
//  Created on: 2017年1月7日 Author: kerry

#include "goods/goods_schduler_engine.h"
#include "goods/pull_engine.h"

namespace goods_logic {

GoodsSchdulerManager* GoodsSchdulerEngine::schduler_mgr_ = NULL;
GoodsSchdulerEngine* GoodsSchdulerEngine::schduler_engine_ = NULL;

GoodsSchdulerManager::GoodsSchdulerManager()
    : goods_redis_(NULL) {
  goods_cache_ = new GoodsCache();
  Init();
}

GoodsSchdulerManager::~GoodsSchdulerManager() {
  DeinitThreadrw(lock_);
  goods_cache_->symbol_list_.clear();
  if (goods_cache_) {delete goods_cache_; goods_cache_ = NULL;}

}

void GoodsSchdulerManager::Init() {
  InitThreadrw(&lock_);
  quotations_logic::PlatformSymbol jh_ag_symbol;
  jh_ag_symbol.set_platform_type(JH_TYPE);
  jh_ag_symbol.set_platform_name("JH");
  jh_ag_symbol.set_show_name("吉银");
  jh_ag_symbol.set_symbol("AG");
  goods_cache_->symbol_list_.push_back(jh_ag_symbol);

  quotations_logic::PlatformSymbol jh_co_symbol;
  jh_co_symbol.set_platform_type(JH_TYPE);
  jh_co_symbol.set_platform_name("JH");
  jh_co_symbol.set_show_name("吉油");
  jh_co_symbol.set_symbol("CO");
  goods_cache_->symbol_list_.push_back(jh_co_symbol);

  quotations_logic::PlatformSymbol fx_ag15_symbol;
  fx_ag15_symbol.set_exchange_name("PMEC");
  fx_ag15_symbol.set_platform_name("fx");
  fx_ag15_symbol.set_platform_type(FX_TYPE);
  fx_ag15_symbol.set_show_name("现货白银9995");
  fx_ag15_symbol.set_symbol("AG15");
  goods_cache_->symbol_list_.push_back(fx_ag15_symbol);


  quotations_logic::PlatformSymbol fx_ag1_symbol;
  fx_ag1_symbol.set_exchange_name("PMEC");
  fx_ag1_symbol.set_platform_name("fx");
  fx_ag1_symbol.set_platform_type(FX_TYPE);
  fx_ag1_symbol.set_show_name("现货白银9999");
  fx_ag1_symbol.set_symbol("AG1");
  goods_cache_->symbol_list_.push_back(fx_ag1_symbol);


  quotations_logic::PlatformSymbol fx_ag30_symbol;
  fx_ag30_symbol.set_exchange_name("TJPME");
  fx_ag30_symbol.set_platform_name("fx");
  fx_ag30_symbol.set_platform_type(FX_TYPE);
  fx_ag30_symbol.set_show_name("现货白银");
  fx_ag30_symbol.set_symbol("AG30KG");
  goods_cache_->symbol_list_.push_back(fx_ag30_symbol);

  quotations_logic::PlatformSymbol fx_xagusd_symbol;
  fx_xagusd_symbol.set_exchange_name("TJPME");
  fx_xagusd_symbol.set_platform_name("fx");
  fx_xagusd_symbol.set_platform_type(FX_TYPE);
  fx_xagusd_symbol.set_show_name("现货白银");
  fx_xagusd_symbol.set_symbol("XAGUSD");
  goods_cache_->symbol_list_.push_back(fx_xagusd_symbol);

}

void GoodsSchdulerManager::InitRedis(goods_logic::GoodsRedis* goods_redis) {
  goods_redis_ = goods_redis;
}

void GoodsSchdulerManager::TimeEvent(int opcode, int time) {
  switch (opcode) {
    case UPDATE_GOODS_DATA: {
      TimeAchieveGoods();
      break;
    }
    default:
      break;
  }
}

void GoodsSchdulerManager::TimeAchieveGoods() {
  bool r = false;
  PLATFORM_SYMBOL_LIST::iterator it = goods_cache_->symbol_list_.begin();
  for (; it != goods_cache_->symbol_list_.end(); ++it) {
    quotations_logic::Quotations quotations;
    quotations_logic::PlatformSymbol symbol = (*it);
    quotations.set_platform_name(symbol.platform_name());
    quotations.set_symbol(symbol.symbol());
    quotations.set_exchange_name(symbol.exchange_name());
    r = AchieveGoodsUnit(symbol.platform_type(), &quotations);
  }
}

bool GoodsSchdulerManager::AchieveGoodsUnit(
    const int32 type, quotations_logic::Quotations* quotations) {
  bool r = false;
  goods_logic::PullEngine* engine = goods_logic::PullEngine::Create(type);
  r =  engine->RequestData(quotations->exchange_name(), quotations->symbol(),
                             quotations);
  if (!r)
    return false;
  //写入redis
  r = goods_redis_->RealTimeGoodsData((*quotations));
  return r;
}

}
