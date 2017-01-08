//  Copyright (c) 2016-2017 The quotations Authors. All rights reserved.
//  Created on: 2017年1月7日 Author: kerry

#ifndef GOODS_REDIS_H__
#define GOODS_REDIS_H__

#include "config/config.h"
#include "storage/data_engine.h"
#include "logic/quotations_infos.h"

namespace goods_logic {

class GoodsRedis {
 public:
  GoodsRedis(config::FileConfig *config);
  virtual ~GoodsRedis();
 public:
  bool RealTimeGoodsData(quotations_logic::Quotations& quotations);
 private:
  base_logic::DataEngine* redis_engine_;
};
}
#endif
