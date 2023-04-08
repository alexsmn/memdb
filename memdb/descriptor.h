#pragma once

#include <cassert>
#include <string_view>

#include "memdb/field.h"

namespace memdb {

class FieldValue;
struct Field;

class Descriptor {
 public:
  Descriptor(const Field* fields,
             size_t field_count,
             size_t record_size,
             unsigned version);

  size_t record_size() const { return record_size_; }
  unsigned version() const { return version_; }

  unsigned field_count() const { return num_fields_; }
  const Field& field(unsigned field) const {
    assert(field < num_fields_);
    return fields_[field];
  }
  FieldId field_id(unsigned field) const {
    assert(field < num_fields_);
    return fields_[field].field_id;
  }
  DBType field_type(unsigned field) const {
    assert(field < num_fields_);
    return fields_[field].type;
  }

  int FindFieldIndex(FieldId field_id) const;

  const Field* FindField(FieldId pid) const;
  const Field* FindPackedField(FieldId pid) const;

  const Field* FindFieldByName(std::string_view name) const;

  DBUInt32 GetUInt32(const void* rec, unsigned field) const;
  const char* GetString(const void* rec, unsigned field) const;

  bool SetNull(void* rec, unsigned field) const;
  bool SetUInt32(void* rec, unsigned field, DBUInt32 value) const;
  bool SetString(void* rec, unsigned field, const char* text) const;
  bool SetValue(void* rec, const FieldValue& value) const;

  // Pack record to buffer.
  size_t PackRecord(const void* rec, void* buffer, size_t size) const;
  // Unpack raw record data.
  // WARNING: |NewRecord()| must be called before unpacking.
  bool UnpackRecord(void* rec, const void* buffer, size_t size) const;

  size_t GetDifferentFieldValues(const void* record1,
                                 const void* record2,
                                 FieldValue values[]) const;
  size_t GetAllFieldValues(const void* record, FieldValue values[]) const;

 protected:
  unsigned num_fields_;
  const Field* fields_;

  size_t record_size_;
  unsigned version_;
};

}  // namespace memdb
