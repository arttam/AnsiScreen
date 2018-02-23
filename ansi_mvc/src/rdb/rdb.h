#ifndef __USES_RDB_H__
#define __USES_RDB_H__
#include <string>
#include <vector>
#include <sqlite_modern_cpp.h>

struct DBEntry
{
	int id;
	std::string name; 
	std::string type; 
	std::string login; 
	std::string md5; 
	std::string hint; 
	std::string details;
};

class RDBData
{
	static const char *getAll;

	std::vector<DBEntry> entries_;
	sqlite::database db_;

public:
	RDBData(const char *dbPath);
	~RDBData() = default;

	bool read();
	void debug() const;
	const std::vector<DBEntry>& entries() const { return entries_; }
	std::vector<std::string> names() const;
	std::vector<std::string> entry(const std::string& name) const;
	std::vector<std::string> entryDetails(const std::string& name) const;
};

#endif
