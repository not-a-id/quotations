//  Copyright (c) 2017-2018 The quoations Authors. All rights reserved.
//  Created on: 2017年1月9日 Author: kerry

#ifndef QUOTATIONS_MANAGER_MANAGER_LOGIC_
#define QUOTATIONS_MANAGER_MANAGER_LOGIC_

#include "basic/basictypes.h"
#include "logic/base_values.h"
#include <list>
#include <string>

namespace manager_logic {
namespace net_request {
class Login {
 public:
  Login()
   :aid_(NULL)
   ,password_(NULL){
  }

  ~Login() {
    if (aid_) {delete aid_; aid_ = NULL;}
    if (password_) {delete password_; password_ = NULL;}
  }

  void set_http_packet(base_logic::DictionaryValue* value);


  void set_aid(const int64 aid) { aid_ =
    new base_logic::FundamentalValue(aid);}

  void set_password(const std::string& password) { password_ =
    new base_logic::StringValue(password);}


  const int64 aid() const {
    int64 aid = 0;
    aid_->GetAsBigInteger(&aid);
    return aid;
  }

  const std::string password() const {
    std::string password;
    password_->GetAsString(&password);
    return password;
  }


 public:
  base_logic::FundamentalValue*     aid_;
  base_logic::StringValue*          password_;
};
}

namespace net_reply {

}
}
#endif
