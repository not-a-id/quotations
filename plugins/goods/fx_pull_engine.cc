//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#include "goods/fx_pull_engine.h"
#include "logic/base_values.h"
#include "logic/logic_unit.h"
#include "net/http_api.h"

namespace goods_logic {

FXPullEngine::FXPullEngine(){
  url_ = "http://quote.fx678.com/symbo";
}

FXPullEngine::~FXPullEngine() {
}

bool FXPullEngine::ReadData(quotations_logic::Quotations& quotation) {
  return true;
}

bool FXPullEngine::RequestData(const std::string& exchange_name,
                               const std::string& symbol,
                               quotations_logic::Quotations* quotation) {
  //std::string result_str =
  //  "{\"s\":\"ok\",\"t\":[\"1483596327\"],\"c\":[\"3706.00\"],\"o\":[\"3672.00\"],\"h\":[\"3724.00\"],\"l\":[\"3670.00\"],\"p\":[\"3669.00\"],\"v\":[\"0.00\"],\"b\":[\"3712.00\"],\"se\":[\"3706.00\"]}";
  std::string result_str;
  base_logic::DictionaryValue params;
  params.SetString(L"exchName", exchange_name);
  params.SetString(L"symbol", symbol);
  quotations_logic::HTTPAPI::RequestGetMethod(url_, &params, result_str);
  quotation->set_symbol(symbol);
  quotation->set_exchange_name(exchange_name);
  return ParserFXData(result_str, quotation);
}

bool FXPullEngine::ParserFXData(const std::string& result,
                                quotations_logic::Quotations* quotation) {
  base_logic::DictionaryValue* value =
      (base_logic::DictionaryValue*) logic::BaseValue::Deserialize(
          (std::string*) &result);
  if (value == NULL)
    return false;

  std::string s;
  int64 unix_time = 0;
  double current_price = 0.0;
  double open_price = 0.0;
  double close_price = 0.0;
  double high_price = 0.0;
  double low_price = 0.0;
  bool r = logic::BaseValue::GetString(value, L"s", &s);
  if (!r)
    return false;

  r = GetFXListToBigInteger(value, L"t", &unix_time);
  if (!r)
    return r;

  r = GetFXListToReal(value, L"c", &current_price);
  if (!r)
    return r;

  r = GetFXListToReal(value, L"o", &open_price);
  if (!r)
    return r;

  r = GetFXListToReal(value, L"p", &close_price);
  if (!r)
    return r;

  r = GetFXListToReal(value, L"h", &high_price);
  if (!r)
    return r;

  r = GetFXListToReal(value, L"l", &low_price);
  if (!r)
    return r;

  quotation->set_closed_yesterday_price(close_price);
  quotation->set_current_price(current_price);
  quotation->set_current_unix_time(unix_time);
  quotation->set_high_price(high_price);
  quotation->set_low_price(low_price);
  quotation->set_opening_today_price(open_price);

  return true;
}
bool FXPullEngine::GetFXListToBigInteger(
    base_logic::DictionaryValue* dict_value, const std::wstring& path,
    int64* out) {
  bool r = false;
  base_logic::Value* t = NULL;
  base_logic::ListValue* list_value = new base_logic::ListValue;
  r = dict_value->GetList(path, &list_value);
  if (!r)
    goto FREE;

  r = list_value->Remove(0, &t);
  if (!r)
    goto FREE;
  r = logic::BaseValue::GetBigInteger(t, out);
  if (!r)
    goto FREE;

  FREE: if (list_value) {
    delete list_value;
    list_value = NULL;
  }
  return r;
}

bool FXPullEngine::GetFXListToReal(base_logic::DictionaryValue* dict_value,
                                   const std::wstring& path, double* out) {
  bool r = false;
  base_logic::Value* t = NULL;
  base_logic::ListValue* list_value = new base_logic::ListValue;
  r = dict_value->GetList(path, &list_value);
  if (!r)
    goto FREE;

  r = list_value->Remove(0, &t);
  if (!r)
    goto FREE;
  r = logic::BaseValue::GetReal(t, out);
  if (!r)
    goto FREE;

  FREE: if (list_value) {
    delete list_value;
    list_value = NULL;
  }
  return r;
}

}
