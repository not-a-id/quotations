//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月25日 Author: kerry

#include "forex/sina_pull_engine.h"
#include "logic/base_values.h"
#include "net/http_api.h"
#include "logic/logic_comm.h"
#include <time.h>

namespace forex_logic {

SinaPullEngine::SinaPullEngine() {
  url_ = "http://hq.sinajs.cn/";
}

SinaPullEngine::~SinaPullEngine() {

}

bool SinaPullEngine::ReadData(quotations_logic::Quotations& quotation) {
  return true;
}

bool SinaPullEngine::RequestData(const std::string& exchange_name,
                                 const std::string& symbol,
                                 quotations_logic::Quotations* quotation) {
  //var hq_str_fx_seurcny="15:12:00,7.372,7.3766,7.3576,394,7.3579,7.3844,7.345,7.372,欧元兑人民币即期汇率,0.2,0.0144,0.005355,SE Banken. Stockholm,7.6356,7.0589,++--+-+-,2017-01-25";
  /*
   * 0,15:05:30 当前时 1.当前价格 7.3734 2.上一分钟价 7.3781 3.昨收 7.3576 4.波幅 394 --0.0394
   5.今开 7.3579 6.最高 7.3844 7.最低 7.3450
   8.当前价格 7.3734  9.名称 欧元兑人民币即期汇率 10. 涨跌 11.价格变化 0.0158 12.振幅 0.005355
   * */
  std::string result_str;
  base_logic::DictionaryValue params;
  params.SetString(L"list", symbol);
  bool r = quotations_logic::HTTPAPI::RequestGetMethod(url_, &params,
                                                       result_str);
  if (!r) {
    LOG_ERROR("http request error");
    return false;
  }
  quotation->set_symbol(symbol);
  quotation->set_exchange_name(exchange_name);
  r = ParserData(result_str, quotation);
  return r;
}

bool SinaPullEngine::CleanData(const std::string& result, std::string* out) {
  std::string::size_type pos = result.find("\"");
  if (pos == std::string::npos)
    return false;

  std::string sub_str = result.substr(pos + 1, result.length());

  pos = sub_str.find("\"");
  if (pos == std::string::npos)
    return false;
  sub_str = sub_str.substr(0, pos);
  (*out) = sub_str;
  return true;
}

void SinaPullEngine::CleanData(std::string& out,
                               std::vector<std::string>& array) {
  std::string::size_type pos(0);
  std::string::size_type start(0);
  int32 index = 0;
  for (; pos != std::string::npos;) {
    pos = out.find(",", start);
    std::string current_str = out.substr(start, (pos - start));
    start = pos + 1;
    if (index != 9 && index != 16) {
      //LOG_DEBUG2("%s",current_str.c_str());
    }
    array.push_back(current_str);
    index++;
  }
}

bool SinaPullEngine::ParserData(const std::string& result,
                                quotations_logic::Quotations* quotation) {
  //"var hq_str_fx_seurcny=\"17:16:56,7.3858,7.3954,7.3576,428,7.3579,7.3878,7.345,7.3858,ŷ\324\252\266\322\310\313\303\361\261Ҽ\264\306ڻ\343\302\312,0.38,0.0282,0.005817,SE Banken. Stockholm,7.6356,7.0589,-+++-+-+,2017-01-25\";\n"
  std::string clean;
  std::vector < std::string > array;
  struct tm time_info = { 0 };
  char* format = "%Y-%m-%dT%H:%M:%S";
  bool r = CleanData(result, &clean);
  if (!r)
    return false;
  CleanData(clean, array);
  std::string price_time = array[CURRENT_DATE] + "T" + array[CURRENT_TIME];
  strptime(price_time.c_str(), format, &time_info);
  int64 unix_time = mktime(&time_info);
  quotation->set_current_unix_time(unix_time);

  double current_price = atof(array[CURRENT_PRICE].c_str());
  quotation->set_current_price(current_price);

  double yesterday_price = atof(array[YESTERDAY_CLOSE_PRICE].c_str());
  quotation->set_closed_yesterday_price(yesterday_price);

  double today_price = atof(array[TODAY_OPEN_PRICE].c_str());
  quotation->set_opening_today_price(today_price);

  double high_price = atof(array[HIGH_PRICE].c_str());
  quotation->set_high_price(high_price);

  double low_price = atof(array[LOW_PRICE].c_str());
  quotation->set_low_price(low_price);

  double pchg = atof(array[PCHG].c_str());
  quotation->set_pchg(pchg);

  double change_price = atof(array[CHANGE_PRICE].c_str());
  quotation->set_change(change_price);

  return true;
}

}
