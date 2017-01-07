//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#include "goods/pull_engine.h"
#include "goods/fx_pull_engine.h"
#include "goods/jh_pull_engine.h"

namespace goods_logic {

PullEngine *PullEngine::Create(int32 type) {
  PullEngine *engine = NULL;
  switch (type) {
  case FX_TYPE: {
    engine = new FXPullEngine();
    break;
  }
  case JH_TYPE: {
    engine = new JHPullEngine();
    break;
  }
  default:
    break;
  }
  return engine;
}
}
