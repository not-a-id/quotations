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

enum QUOTATIONS_TYPE {
  NO_TYPE = -1,
  STOCK_TYPE =1,
  GOOD_TYPE = 2,
  FUTURES_TYPE = 3,
  FOREX_TYPE = 4
};

class ConnectionSchduler {
 public:
  ConnectionSchduler();

  ConnectionSchduler(const ConnectionSchduler& connection_schduler);

  ConnectionSchduler& operator =(const ConnectionSchduler& connection_schduler);

  ~ConnectionSchduler() {
    if (data_ != NULL) {
      data_->Release();
    }
  }

  void set_id(const int32 id){
    data_->id_ = id;
  }

  void set_type(const int32 type){
    data_->type_ = type;
  }

  void set_send_error_count(const int32 send_error_count){
    data_->send_error_count_ = send_error_count;
  }

  void set_recv_error_count(const int32 recv_error_count) {
    data_->recv_error_count_ = recv_error_count;
  }

  void set_socket(const int socket) {
    data_->socket_ = socket;
  }

  void set_is_effective(const bool is_effective) {
    data_->is_effective_ = is_effective;
  }

  void set_send_last_time(const time_t send_last_time){
    data_->send_last_time_ = send_last_time;
  }

  void set_recv_last_time(const time_t recv_last_time) {
    data_->recv_last_time_ = recv_last_time;
  }

  void set_ip(const std::string& ip) {
    data_->ip_ = ip;
  }

  void set_password(const std::string& password) {
    data_->password_ = password;
  }

  void set_mac(const std::string& mac) {
    data_->mac_ = mac;
  }

  void add_send_error_count() {
    __sync_fetch_and_add(&data_->send_error_count_, 1);
  }

  void add_recv_error_count() {
    __sync_fetch_and_add(&data_->recv_error_count_, 1);
  }

  const int32 id() const {
    return data_->id_;
  }

  const int32 type() const {
    return data_->type_;
  }

  const int32 send_error_count() const {
    return data_->send_error_count_;
  }

  const int32 recv_error_count() const {
    return data_->recv_error_count_;
  }

  const int socket() const {
    return data_->socket_;
  }

  const int port() const {
    return data_->port_;
  }

  const bool is_effective() const {
    return data_->is_effective_;
  }

  const time_t send_last_time() const {
    return data_->send_last_time_;
  }

  const time_t recv_last_time() const {
    return data_->recv_last_time_;
  }

  const std::string& ip() const {
    return data_->ip_;
  }

  const std::string& password() const {
    return data_->password_;
  }

  const std::string& mac() const {
    return data_->mac_;
  }
 private:
  class Data {
   public:
    Data()
        : refcount_(1),
          id_(0),
          type_(0),
          send_error_count_(0),
          recv_error_count_(0),
          socket_(-1),
          port_(0),
          send_last_time_(0),
          recv_last_time_(0),
          is_effective_(false) {
    }

    ~Data() {
    }

   public:
    int32 id_;
    int32 type_;
    int32 send_error_count_;
    int32 recv_error_count_;
    int socket_;
    int port_;
    bool is_effective_;
    time_t send_last_time_;
    time_t recv_last_time_;
    std::string ip_;
    std::string password_;
    std::string mac_;
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

class PlatformSymbol {
 public:
  PlatformSymbol();
  PlatformSymbol(const PlatformSymbol& platform_symbol);

  PlatformSymbol& operator =(const PlatformSymbol& platform_symbol);

  ~PlatformSymbol() {
    if (data_ != NULL) {
      data_->Release();
    }
  }

  void set_platform_type(const int32 platform_type) {
    data_->platform_type_ = platform_type;
  }

  void set_platform_name(const std::string& platform_name) {
    data_->platform_name_ = platform_name;
  }

  void set_symbol(const std::string& symbol) {
    data_->symbol_ = symbol;
  }

  void set_exchange_name(const std::string& exchange_name) {
    data_->exchange_name_ = exchange_name;
  }

  void set_show_name(const std::string& show_name) {
    data_->show_name_ = show_name;
  }

  const int32 platform_type() const {
    return data_->platform_type_;
  }
  const std::string& platform_name() const {
    return data_->platform_name_;
  }
  const std::string& symbol() const {
    return data_->symbol_;
  }
  const std::string& exchange_name() const {
    return data_->exchange_name_;
  }
  const std::string& show_name() const {
    return data_->show_name_;
  }

 private:
  class Data {
   public:
    Data()
        : refcount_(1),
          platform_type_(0),
          exchange_name_("DEFAULT") {
    }

    ~Data() {
    }

   public:
    int32 platform_type_;
    std::string platform_name_;
    std::string symbol_;
    std::string exchange_name_;
    std::string show_name_;

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

  void set_platform_name(const std::string& platform) {
    data_->platform_name_ = platform;
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

  const std::string& platform() const {
    return data_->platform_name_;
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

  std::string ValueSerialize();

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
    std::string platform_name_;
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
