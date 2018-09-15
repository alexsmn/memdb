#pragma once

#include "memdb/table.h"

namespace memdb {

template<class T>
class TableImpl : public Table {
 public:
  typedef T Record;

  TableImpl(TID tid)
      : Table(Record::GetDescriptor()) {
    this->id = tid;
    CheckFields();
  }

  const Record* FindRecord(RID rid) const {
    return reinterpret_cast<const Record*>(Table::FindRecord(rid));
  }

  // Table
  virtual void NewRecord(void* rec) const {
    assert(rec);
    for (unsigned i = 0; i < descriptor_.field_count(); ++i)
      descriptor_.SetNull(rec, i);
  }

 private:
  void CheckFields() {
#ifdef _DEBUG
    // Check field types and sizes.
    for (size_t i = 0; i < descriptor().field_count(); ++i) {
      DBType type = descriptor().field(i).type;
      size_t size = descriptor().field(i).size;
      switch (type) {
        case DB_BOOL:
        case DB_UINT8:
          assert(size == 1);
          break;
        case DB_UINT16:
          assert(size == 2);
          break;
        case DB_UINT32:
          assert(size == 4);
          break;
        case DB_FLOAT:
          assert(size == 8);
          break;
        case DB_TID:
          assert(size == sizeof(TID));
          break;
        case DB_STRING:
          assert(size >= 2);
          break;
        default:
          assert(false);
          break;
      }
    }

    // Find identical fields.
    if (descriptor().field_count() > 0) {
      for (size_t i = 0; i < descriptor().field_count() - 1; ++i) {
        FieldId field1_id = descriptor().field(i).field_id;
        for (size_t j = i + 1; j < descriptor().field_count(); ++j) {
          FieldId field2_id = descriptor().field(j).field_id;
          assert(field1_id != field2_id);
        }
      }
    }
#endif
  }
};

} // namespace memdb
