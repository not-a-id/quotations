//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月6日 Author: kerry

#ifndef QUOTATIONS_GOODS_JH_PULL_ENGINE_H_
#define QUOTATIONS_GOODS_JH_PULL_ENGINE_H_
#include "goods/pull_engine.h"
#include "logic/quotations_infos.h"
namespace goods_logic {

//http://122.144.213.30:7788/api/prices/realtime/getlist?goodsType=AG

class JHPullEngine : public PullEngine {
 public:
  JHPullEngine();
  virtual ~JHPullEngine();
 public:
  bool ReadData(quotations_logic::Quotations& quotation);  //回调推送接口

  bool RequestData(const std::string& exchange_name, const std::string& symbol,
                   quotations_logic::Quotations* quotation);  //http主动请求
 private:
  bool ParserFXData(const std::string& result,
                    quotations_logic::Quotations* quotation);

  bool GetJHListToDictionary(base_logic::DictionaryValue* dict_value,
                             base_logic::Value** out);
 private:
  std::string url_;
};

}

#endif
