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
   ,password_(NULL)
   ,a_type_(NULL){
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

  void set_atype(const int32 type) {
    a_type_ = new base_logic::FundamentalValue(type);
  }


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

  const int32 a_type() const {
    int32 a_type;
    a_type_->GetAsInteger(&a_type);
    return a_type;
  }


 public:
  base_logic::FundamentalValue*     aid_;
  base_logic::StringValue*          password_;
  base_logic::FundamentalValue*     a_type_;
};
}

namespace net_reply {

}
}
#endif
