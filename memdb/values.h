#pragma once

#include "memdb/field_value.h"
#include "memdb/types.h"

#include <vector>

namespace memdb {

class Descriptor;

class Values {
 public:
  explicit Values(const Descriptor& descriptor) : descriptor_{descriptor} {}

  Values(const Values&) = delete;
  Values& operator=(const Values&) = delete;

  const std::vector<FieldValue>& values() const { return values_; }

  void AddValue(const FieldValue& value);

  void SetBuffer(FieldId field_id, const void* data, size_t size);
  bool DoesExist(FieldId field_id) const;

  template <typename T>
  void Set(FieldId field_id, const T& val) {
    SetBuffer(field_id, &val, sizeof(T));
  }

 private:
  const Descriptor& descriptor_;

  std::vector<FieldValue> values_;
  std::vector<std::vector<char> > datum_;
};

}  // namespace memdb
