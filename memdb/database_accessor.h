#pragma once

#include <filesystem>

namespace base {
class FilePath;
}

namespace memdb {

class MemoryDB;

class DatabaseAccessor {
 public:
  explicit DatabaseAccessor(MemoryDB& database)
      : database_(database), just_created_(false) {}
  virtual ~DatabaseAccessor() {}

  DatabaseAccessor(const DatabaseAccessor&) = delete;
  DatabaseAccessor& operator=(const DatabaseAccessor&) = delete;

  bool just_created() const { return just_created_; }

  virtual void Open(const std::filesystem::path& database_dir) = 0;

 protected:
  MemoryDB& database() const { return database_; }

  void set_just_created() { just_created_ = true; }

 private:
  MemoryDB& database_;
  bool just_created_;
};

}  // namespace memdb
