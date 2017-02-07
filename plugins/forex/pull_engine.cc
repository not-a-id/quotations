//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#include "forex/pull_engine.h"
#include "forex/sina_pull_engine.h"

namespace forex_logic {

PullEngine *PullEngine::Create(int32 type) {
  PullEngine *engine = NULL;
  switch (type) {
    case SINA_TYPE:{
      engine = new SinaPullEngine();
      break;
    }
    default:
      break;
  }
  return engine;
}

}
