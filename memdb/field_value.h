#pragma once

#include <cstddef>

namespace memdb {

class FieldValue {
 public:
  FieldValue() {}

  FieldValue(unsigned field_index, size_t size, const void* data)
      : field_index(field_index), size(size), data(data) {}

  unsigned field_index;
  size_t size;
  const void* data;
};

}  // namespace memdb
