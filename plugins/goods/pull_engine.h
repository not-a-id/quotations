//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#ifndef QUOTATIONS_GOODS_PULL_ENGINE_H_
#define QUOTATIONS_GOODS_PULL_ENGINE_H_
#include "basic/basictypes.h"
#include "config/config.h"
#include "logic/quotations_infos.h"
#include <string>
enum GOODSPULLTYPE{
 FX_TYPE = 1,
 JH_TYPE = 2
};

namespace goods_logic {

class PullEngine {
public:
  static PullEngine *Create(int32 type);
  virtual ~PullEngine() {}

public:

  virtual bool ReadData(quotations_logic::Quotations& quotation) = 0;

  virtual bool RequestData(const std::string& exchange_name, const std::string& symbol,
                     quotations_logic::Quotations* quotation) = 0;

};
}

#endif
