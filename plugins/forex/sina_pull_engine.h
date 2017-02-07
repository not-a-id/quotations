//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月25日 Author: kerry

#ifndef QUOTATIONS_FOREX_SINA_PULL_ENGINE_H_
#define QUOTATIONS_FOREX_SINA_PULL_ENGINE_H_

#include "forex/pull_engine.h"
#include "logic/quotations_infos.h"
#include <vector>

namespace forex_logic {
//http://hq.sinajs.cn/list=fx_seurcny

enum ELETYPE{
  CURRENT_TIME = 0,
  CURRENT_PRICE = 1,
  ELEL_UNKONW_ONE = 2,
  YESTERDAY_CLOSE_PRICE = 3,
  VOLATILITY = 4,
  TODAY_OPEN_PRICE = 5,
  HIGH_PRICE = 6,
  LOW_PRICE = 7,
  ELEL_UNKOWN_TOW = 8,
  NAME = 9,
  PCHG = 10,
  CHANGE_PRICE = 12,
  SWING = 13 ,
  ADDRESS = 14,
  CURRENT_DATE = 17
};

class SinaPullEngine : public PullEngine {
 public:
  SinaPullEngine();
  virtual ~SinaPullEngine();
 public:
  bool ReadData(quotations_logic::Quotations& quotation);

  bool RequestData(const std::string& exchange_name, const std::string& symbol,
                   quotations_logic::Quotations* quotation);  //http主动请求
 private:
  bool ParserData(const std::string& result,
                  quotations_logic::Quotations* quotation);

  bool CleanData(const std::string& result, std::string* out);

  void CleanData(std::string& out, std::vector<std::string>& array);
 private:
  std::string url_;
};

}
#endif
