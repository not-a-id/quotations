//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#include "goods/jh_pull_engine.h"
#include "logic/base_values.h"
#include "logic/logic_unit.h"
#include "net/http_api.h"
#include <time.h>

namespace goods_logic {

JHPullEngine::JHPullEngine() {
  url_ = "http://122.144.213.30:7788/api/prices/realtime/getlist";
}

JHPullEngine::~JHPullEngine() {
}

bool JHPullEngine::ReadData(quotations_logic::Quotations& quotation) {
  return true;
}

bool JHPullEngine::RequestData(const std::string& exchange_name,
                               const std::string& symbol,
                               quotations_logic::Quotations* quotation) {
//{"PriceList":[{"TypeCode":"AG","CurPrice":3516,"UpDown":1,"Open":3546,"Close":3543,"High":3563,"Low":3484,"PriceDate":"2017-01-06T00:00:00","PriceTime":"2017-01-07T03:59:59","MarketDate":null}]}
  std::string result_str;
  base_logic::DictionaryValue params;
  params.SetString(L"goodsType", symbol);
  quotations_logic::HTTPAPI::RequestGetMethod(url_, &params, result_str);
  quotation->set_symbol(symbol);
  quotation->set_exchange_name(exchange_name);
  return ParserFXData(result_str, quotation);
}

bool JHPullEngine::ParserFXData(const std::string& result,
                                quotations_logic::Quotations* quotation) {
  base_logic::DictionaryValue* value =
      (base_logic::DictionaryValue*) logic::BaseValue::Deserialize(
          (std::string*) &result);
  if (value == NULL)
    return false;

  std::string s;
  std::string price_time;
  int64 unix_time = 0;
  double current_price = 0.0;
  double open_price = 0.0;
  double close_price = 0.0;
  double high_price = 0.0;
  double low_price = 0.0;
  int64 updown_price = 0.0;
  base_logic::DictionaryValue* price_dict = NULL;
  base_logic::Value* temp_price = NULL;
  struct tm time_info = { 0 };
  char* format = "%Y-%m-%dT%H:%M:%S";  //没有秒格式符%S

  bool r = GetJHListToDictionary(value, &temp_price);
  if (!r) {
    if (value) {
      delete value;
      value = NULL;
    }
    return false;
  }

  price_dict = (base_logic::DictionaryValue*) (temp_price);

  r = logic::BaseValue::GetReal(price_dict, L"CurPrice", &current_price);
  if (!r) {
    goto FREE;
  }

  r = logic::BaseValue::GetReal(price_dict, L"Open", &open_price);
  if (!r) {
    goto FREE;
  }

  r = logic::BaseValue::GetReal(price_dict, L"Close", &close_price);
  if (!r) {
    goto FREE;
  }

  r = logic::BaseValue::GetReal(price_dict, L"High", &high_price);
  if (!r) {
    goto FREE;
  }

  r = logic::BaseValue::GetReal(price_dict, L"Low", &low_price);
  if (!r) {
    goto FREE;
  }

  r = logic::BaseValue::GetBigInteger(price_dict, L"UpDown", &updown_price);
  if (!r) {
    goto FREE;
  }

  r = logic::BaseValue::GetString(price_dict, L"PriceTime", &price_time);

  //"2017-01-07 03:59:59";
  strptime(price_time.c_str(), format, &time_info);
  unix_time = mktime(&time_info);

  quotation->set_closed_yesterday_price(close_price);
  quotation->set_current_price(current_price);
  quotation->set_current_unix_time(unix_time);
  quotation->set_high_price(high_price);
  quotation->set_low_price(low_price);
  quotation->set_opening_today_price(open_price);
  quotation->set_change(updown_price);

  FREE:
  if (value) {
    delete value;
    value = NULL;
  }
  return r;
}

bool JHPullEngine::GetJHListToDictionary(
    base_logic::DictionaryValue* dict_value, base_logic::Value** out) {
  base_logic::ListValue* price_list;
  bool r = dict_value->GetList(L"PriceList", &price_list);
  if (!r)
    return false;
  r = price_list->Remove(0, out);
  if (!r) {
    delete price_list;
    price_list = NULL;
  }
  return r;
}

}
