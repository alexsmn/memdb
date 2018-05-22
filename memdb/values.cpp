#include "memdb/values.h"

#include "memdb/descriptor.h"

namespace memdb {

void Values::AddValue(const FieldValue& value) {
  assert(value.field_index >= 0 &&
         value.field_index < descriptor_.field_count());
  assert(descriptor_.field(value.field_index).type == DB_STRING ||
         descriptor_.field(value.field_index).size == value.size);

  const char* buffer = reinterpret_cast<const char*>(value.data);
  datum_.push_back(std::vector<char>(buffer, buffer + value.size));

  const std::vector<char>& data = datum_.back();
  const char* data_ptr = !data.empty() ? &data[0] : NULL;

  values_.push_back(FieldValue(value.field_index, value.size, data_ptr));
}

void Values::SetBuffer(FieldId field_id, const void* data, size_t size) {
  assert(!DoesExist(field_id));

  int field_index = descriptor_.FindFieldIndex(field_id);
  assert(field_index >= 0);

  AddValue(FieldValue(field_index, size, data));
}

bool Values::DoesExist(FieldId field_id) const {
  for (size_t i = 0; i < values_.size(); ++i) {
    unsigned field_index = values_[i].field_index;
    if (field_id == descriptor_.field_id(field_index))
      return true;
  }
  return false;
}

}  // namespace memdb
