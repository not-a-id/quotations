//  Copyright (c) 2016-2017 The quotations Authors. All rights reserved.
//  Created on: 2017年1月7日 Author: kerry

#ifndef FOREX_REDIS_H__
#define FOREX_REDIS_H__

#include "config/config.h"
#include "storage/data_engine.h"
#include "logic/quotations_infos.h"

namespace forex_logic {

class ForexRedis {
 public:
  ForexRedis(config::FileConfig *config);
  virtual ~ForexRedis();
 public:
  bool RealTimeForexData(quotations_logic::Quotations& quotations);
 private:
  base_logic::DataEngine* redis_engine_;
};
}
#endif
