//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#include "http/http_method.h"
#include "logic/base_values.h"
#include "net/http_api.h"

namespace quotations_logic {

bool HTTPAPI::RequestGetMethod(const std::string& url,
                               base_logic::DictionaryValue* info,
                               std::string& result) {

  bool r = false;
  std::string params;
  int32 count = 0;
  base_logic::ValueSerializer *engine =
      base_logic::ValueSerializer::Create(base_logic::IMPL_HTTP, &params);
  base_logic::Value* value = (base_logic::Value*) info;
  r = engine->Serialize(*value);
  if (!r) {
    if (engine) {delete engine; engine = NULL;}
    return r;
  }
  std::string query = url + std::string("?") + params;
  //std::string query = "http://idcardreturnphoto.haoservice.com/idcard/VerifyIdcardReturnPhoto?cardNo=13032119880401018&realName=%E5%BC%A0%E5%BC%BA";
  //std::string authorization = "Authorization:APPCODE 900036feeee64ae089177dd06b25faa9";
  http::HttpMethodGet http(query);
  //http.SetHeaders(authorization);
  int32 i = 0;
  do {
    r = http.Get();
    if (r)
      break;
    i++;
    if (i >= count)
      break;

  } while (true);

  if (!r){
    if (engine) {delete engine; engine = NULL;}
    return r;
  }
  r = http.GetContent(result);
  return r;
}

}
