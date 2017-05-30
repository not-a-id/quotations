//  Copyright (c) 2015-2018 The KID Authors. All rights reserved.
//  Created on: 2017.5.28 Author: kerry

#ifndef STAR_STAR_KAFKA_H_
#define STAR_STAR_KAFKA_H_

#include "logic/quotations_infos.h"
#include "basic/basictypes.h"
#include "basic/scoped_ptr.h"
#include "logic/base_values.h"
#include "queue/kafka_consumer.h"
#include <list>
#include <map>
#include <string>

namespace star_logic {

class StarKafka {
 public:
  StarKafka(config::FileConfig *config);
  StarKafka(const int32 svc_id, base::ConnAddr& addr);
  virtual ~StarKafka();

 public:
  bool FectchBatchTempTask(std::list<quotations_logic::Quotations> *list);


 private:
  kafka_consumer kafka_consumer_;
};
}  // namespace star_logic

#endif /* TASK_DB_H_ */
