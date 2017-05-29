//  Copyright (c) 2016-2017 The quotations Authors. All rights reserved.
//  Created on: 2017年1月7日 Author: kerry

#ifndef STAR_REDIS_H__
#define STAR_REDIS_H__

#include "config/config.h"
#include "storage/data_engine.h"
#include "logic/quotations_infos.h"

namespace star_logic {

class StarRedis {
 public:
  StarRedis(config::FileConfig *config);
  virtual ~StarRedis();
 public:
  bool RealTimeStarData(quotations_logic::Quotations& quotations);
 private:
  base_logic::DataEngine* redis_engine_;
};
}
#endif
