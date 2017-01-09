//  Copyright (c) 2017-2018 The quoations Authors. All rights reserved.
//  Created on: 2017年1月9日 Author: kerry

#include "manager_proto_buf.h"
#include "basic/basic_util.h"

namespace manager_logic {

namespace net_request {

void Login::set_http_packet(base_logic::DictionaryValue* value) {
  bool r = false;
  int64 aid = 0;
  std::string password;

  r = value->GetBigInteger(L"aid", &aid);
  if (r)
    set_aid(aid);

  r = value->GetString(L"password", &password);
  if (r)
    set_password(password);
}

}


}
