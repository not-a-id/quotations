//  Copyright (c) 2017-2018 The quoations Authors. All rights reserved.
//  Created on: 2017年1月9日 Author: kerry

#include "manager_proto_buf.h"
#include "basic/basic_util.h"

namespace manager_logic {

namespace net_request {

bool Login::set_http_packet(base_logic::DictionaryValue* value) {
  bool r = false;
  int64 aid = 0;
  int32 atype = 0;
  int64 big_atype = 0;
  std::string password;

  if (value == NULL)
    return false;

  r = value->GetBigInteger(L"aid", &aid);
  if (r)
    set_aid(aid);
  else
    return false;

  r = value->GetString(L"password", &password);
  if (r)
    set_password(password);
  else
    return false;

  r = value->GetBigInteger(L"atype", &big_atype);
  if(r){
    atype = big_atype;
    set_atype(atype);
  }else{
    set_atype(0);
  }
}

}


}
