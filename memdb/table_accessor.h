#pragma once

#include "memdb/types.h"

namespace memdb {

class TableAccessor {
 public:
  virtual ~TableAccessor() { }

  virtual bool Open() = 0;
  virtual std::pair<bool, RecordUID> Insert(const void* data) = 0;
  virtual bool Update(RecordUID uid, const void* data) = 0;
  virtual bool Delete(RecordUID uid) = 0;
};

} // namespace memdb
