//  Copyright (c) 2016-2017 The quotations Authors. All rights reserved.
//  Created on: 2017年5月28日 Author: kerry

#include "star/star_redis.h"
#include "storage/data_engine.h"
#include "basic/basic_util.h"
#include "logic/logic_comm.h"

namespace star_logic {

StarRedis::StarRedis(config::FileConfig* config) {
  redis_engine_ = base_logic::DataEngine::Create(REIDS_TYPE);
  redis_engine_->InitParam(config->redis_list_);
}

StarRedis::~StarRedis() {
  if (redis_engine_) {
    delete redis_engine_;
    redis_engine_ = NULL;
  }
}

bool StarRedis::RealTimeStarData(quotations_logic::Quotations& quotations) {
    return true;
}
}
