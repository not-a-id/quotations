//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#ifndef QUOTATIONS_PUB_LOGIC_QUOTATIONS_INFOS_H_
#define QUOTATIONS_PUB_LOGIC_QUOTATIONS_INFOS_H_

#include <string>
#include <map>
#include <list>

#include "basic/basictypes.h"
#include "logic/base_values.h"

namespace quotations_logic {

class Quotations {
 public:
  Quotations();

  Quotations(const Quotations& quotations);

  Quotations& operator =(const Quotations& quotations);

  ~Quotations() {
    if (data_ != NULL) {
      data_->Release();
    }
  }

  void set_symbol(const std::string& symbol) {
    data_->symbol_ = symbol;
  }

  void set_exchange_name(const std::string& exchange_name) {
    data_->exchange_name_ = exchange_name;
  }

  void set_current_price(const double current_price) {
    data_->current_price_ = current_price;
  }

  void set_high_price(const double high_price) {
    data_->high_price_ = high_price;
  }

  void set_low_price(const double low_price) {
    data_->low_price_ = low_price;
  }

  void set_opening_today_price(const double opening_today_price) {
    data_->opening_today_price_ = opening_today_price;
  }

  void set_closed_yesterday_price(const double closed_yesterday_price) {
    data_->closed_yesterday_price_ = closed_yesterday_price;
  }

  void set_change(const double change) {
    data_->change_ = change;
  }

  void set_pchg(const double pchg) {
    data_->pchg_ = pchg;
  }

  void set_current_unix_time(const double current_unix_time) {
    data_->current_unix_time_ = current_unix_time;
  }


  const std::string& symbol() const {
    return data_->symbol_;
  }

  const std::string& exchange_name() const {
    return data_->exchange_name_;
  }
  const double current_price() const {
    return data_->current_price_;
  }

  const double high_price() const {
    return data_->high_price_;
  }

  const double low_price() const {
    return data_->low_price_;
  }

  const double opening_today_price() const {
    return data_->opening_today_price_;
  }

  const double closed_yesterday_price() const {
    return data_->closed_yesterday_price_;
  }

  const double change() const {
    return data_->change_;
  }

  const double pchg() const {
    return data_->pchg_;
  }

  const int64 current_unix_time() const {
    return data_->current_unix_time_;
  }
 private:
  class Data {
   public:
    Data()
        : refcount_(1),
          current_price_(0.0),
          high_price_(0.0),
          low_price_(0.0),
          opening_today_price_(0.0),
          closed_yesterday_price_(0.0),
          change_(0.0),
          pchg_(0.0),
          current_unix_time_(0) {
    }

    ~Data() {
    }

   public:
    std::string symbol_;
    std::string exchange_name_;
    double current_price_;
    double high_price_;
    double low_price_;
    double opening_today_price_;
    double closed_yesterday_price_;
    double change_;
    double pchg_;
    int64 current_unix_time_;

    void AddRef() {
      __sync_fetch_and_add(&refcount_, 1);
    }
    void Release() {
      __sync_fetch_and_sub(&refcount_, 1);
      if (!refcount_)
        delete this;
    }

   private:
    int refcount_;
  };
  Data* data_;
};

}  // namespace quotations_logic

#endif /* QUOTATIONS_PUB_LOGIC_QUOTATIONS_INFOS_H_ */
