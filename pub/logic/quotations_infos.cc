//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#include "logic/quotations_infos.h"
#include "basic/template.h"

namespace quotations_logic {

Quotations::Quotations() {
  data_ = new Data();
}

Quotations::Quotations(const Quotations& quotations)
    : data_(quotations.data_) {
  if (data_ != NULL) {
    data_->AddRef();
  }
}

Quotations& Quotations::operator =(
    const Quotations& quotations) {
  if (quotations.data_ != NULL) {
    quotations.data_->AddRef();
  }

  if (data_ != NULL) {
    data_->Release();
  }

  data_ = quotations.data_;
  return (*this);
}


}  // namespace quotations_logic
