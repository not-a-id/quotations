//  Copyright (c) 2016-2017 The quotations Authors. All rights reserved.
//  Created on: 2017年1月7日 Author: kerry

#include "forex/forex_redis.h"
#include "storage/data_engine.h"
#include "basic/basic_util.h"
#include "logic/logic_comm.h"

namespace forex_logic {

ForexRedis::ForexRedis(config::FileConfig* config) {
  redis_engine_ = base_logic::DataEngine::Create(REIDS_TYPE);
  redis_engine_->InitParam(config->redis_list_);
}

ForexRedis::~ForexRedis() {
  if (redis_engine_) {
    delete redis_engine_;
    redis_engine_ = NULL;
  }
}

bool ForexRedis::RealTimeForexData(quotations_logic::Quotations& quotations) {

  //[hash name] rule : platform:exchangename:type: FX:PMEC:AG
  // [key name] rule : unix - minute
  base_logic::DictionaryValue value;
  std::string hash_name;
  std::string key_name;
  std::string value_name;

  hash_name = quotations.platform() + ":" + quotations.exchange_name() + ":"
      + quotations.symbol();
  LOG_MSG2("%s", hash_name.c_str());
  int64 key_temp = quotations.current_unix_time() / 60 * 60;
  key_name = base::BasicUtil::StringUtil::Int64ToString(key_temp);
  value.SetString(L"name", hash_name);
  value.SetString(L"key", key_name);
  value.SetString(L"value", quotations.ValueSerialize());

  return redis_engine_->WriteData(HASH_VALUE, &value);

}
}
