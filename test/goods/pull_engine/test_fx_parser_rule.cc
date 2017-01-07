//  Copyright (c) 2015-2016 The kid Authors. All rights reserved.
//   Created on: 2016.12.23 Author: kerry

#include "gtest/gtest.h"
#include "log/mig_log.h"
#include "logic/quotations_infos.h"
#include "goods/pull_engine.h"
#include <string>

class PaserFXTest: public testing::Test {
};


B
TEST(PaserFXTest, Basic){
  /*char* format="%Y-%m-%dT%H:%M:%S";//没有秒格式符%S
  //char* timeStr="1970-1-1 0:1";//1970年1月1日0时1分，没有秒数
  std::string timeStr = "2017-01-07T03:59:12";
  struct tm time_info={0};
  if(NULL == strptime(timeStr.c_str(), format, &time_info)) {
    fprintf(stderr, "error\n");
  }else{
    time_t secondsFrom1970 = timegm(&time_info);//这个值期望是60
    time_t tunixt = mktime(&time_info);
    fprintf(stdout, "time =[%s], time in seconds from 1970 is [%d]\n", timeStr, secondsFrom1970);
  }*/
  //goods_logic::PullEngine* engine =  goods_logic::PullEngine::Create(FX_TYPE);
  goods_logic::PullEngine* engine = goods_logic::PullEngine::Create(JH_TYPE);
  std::string exchange_name = "PMEC";
  std::string symbol = "AG";
  quotations_logic::Quotations quotations;
  engine->RequestData(exchange_name, symbol, &quotations);
}
