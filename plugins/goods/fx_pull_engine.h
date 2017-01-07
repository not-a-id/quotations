//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#ifndef QUOTATIONS_GOODS_FX_PULL_ENGINE_H_
#define QUOTATIONS_GOODS_FX_PULL_ENGINE_H_
#include "goods/pull_engine.h"
#include "logic/quotations_infos.h"
namespace goods_logic {

//http://quote.fx678.com/symbo?exchName=PMEC&symbol=AG15 API
//http://quote.fx678.com/symbol/AG15 WEB

class FXPullEngine : public PullEngine {
 public:
  FXPullEngine();
  virtual ~FXPullEngine();
 public:
  bool ReadData(quotations_logic::Quotations& quotation);  //回调推送接口

  bool RequestData(const std::string& exchange_name, const std::string& symbol,
                   quotations_logic::Quotations* quotation);  //http主动请求

 private:
  bool ParserFXData(const std::string& result,
                    quotations_logic::Quotations* quotation);

  bool GetFXListToBigInteger(base_logic::DictionaryValue* dict_value,
                             const std::wstring& path, int64* out);

  bool GetFXListToReal(base_logic::DictionaryValue* dict_value,
                       const std::wstring& path, double* out);
 private:
  std::string url_;
};

}

#endif
