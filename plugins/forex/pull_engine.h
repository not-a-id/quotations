//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#ifndef QUOTATIONS_FOREX_PULL_ENGINE_H_
#define QUOTATIONS_FOREX_PULL_ENGINE_H_
#include "basic/basictypes.h"
#include "config/config.h"
#include "logic/quotations_infos.h"
#include <string>

enum FOREXPULLTYPE{
 NO_TYPE = 0,
 SINA_TYPE = 1
};

namespace forex_logic {

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
