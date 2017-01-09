//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#include "logic/quotations_infos.h"
#include "basic/template.h"
#include "logic/logic_comm.h"

namespace quotations_logic {

ConnectionSchduler::ConnectionSchduler() {
  data_ = new Data();
}

ConnectionSchduler::ConnectionSchduler(const ConnectionSchduler& connection_schduler)
    : data_(connection_schduler.data_) {
  if (data_ != NULL) {
    data_->AddRef();
  }
}

ConnectionSchduler& ConnectionSchduler::operator =(const ConnectionSchduler& connection_schduler) {
  if (connection_schduler.data_ != NULL) {
    connection_schduler.data_->AddRef();
  }

  if (data_ != NULL) {
    data_->Release();
  }

  data_ = connection_schduler.data_;
  return (*this);
}



PlatformSymbol::PlatformSymbol() {
  data_ = new Data();
}

PlatformSymbol::PlatformSymbol(const PlatformSymbol& platform_symbol)
    : data_(platform_symbol.data_) {
  if (data_ != NULL) {
    data_->AddRef();
  }
}

PlatformSymbol& PlatformSymbol::operator =(const PlatformSymbol& platform_symbol) {
  if (platform_symbol.data_ != NULL) {
    platform_symbol.data_->AddRef();
  }

  if (data_ != NULL) {
    data_->Release();
  }

  data_ = platform_symbol.data_;
  return (*this);
}



Quotations::Quotations() {
  data_ = new Data();
}

Quotations::Quotations(const Quotations& quotations)
    : data_(quotations.data_) {
  if (data_ != NULL) {
    data_->AddRef();
  }
}

Quotations& Quotations::operator =(const Quotations& quotations) {
  if (quotations.data_ != NULL) {
    quotations.data_->AddRef();
  }

  if (data_ != NULL) {
    data_->Release();
  }

  data_ = quotations.data_;
  return (*this);
}

std::string Quotations::ValueSerialize() {
  std::string json_content;
  base_logic::DictionaryValue dict;
  dict.SetReal(L"current_price", data_->current_price_);
  dict.SetReal(L"high_price", data_->high_price_);
  dict.SetReal(L"low_price", data_->low_price_);
  dict.SetReal(L"opening_today_price", data_->opening_today_price_);
  dict.SetReal(L"closed_yesterday_price", data_->closed_yesterday_price_);
  dict.SetReal(L"change", data_->change_);
  dict.SetReal(L"pchg", data_->pchg_);
  dict.SetBigInteger(L"current_unix_time", data_->current_unix_time_);
  if (!data_->platform_name_.empty())
    dict.SetString(L"platform_name", data_->platform_name_);
  if (!data_->symbol_.empty())
    dict.SetString(L"symbol", data_->symbol_);
  if (!data_->exchange_name_.empty())
    dict.SetString(L"exchange_name", data_->exchange_name_);

  base_logic::ValueSerializer* engine = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON);
  if (engine == NULL) {
    LOG_ERROR("engine create null");
  }
  bool r = engine->Serialize(dict, &json_content);
  return json_content;
}

}  // namespace quotations_logic
