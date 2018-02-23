#include <algorithm>
#include "rdb.h"

const char *RDBData::getAll = "select rowid,* from reminders;";

RDBData::RDBData(const char *dbPath):db_(dbPath)
{ }

bool RDBData::read()
{
	try {
		db_ << getAll >> [this](int id, std::string name, std::string type, std::string login, std::string md5, std::string hint, std::string details) {
			entries_.push_back({id, name, type, login, md5, hint, details});
		};
		return true;
	}
	catch(std::exception& ex) {
		std::cerr << "Failed to read data: " << ex.what() << std::endl;
		return false;
	}
}

void RDBData::debug() const
{
	for(auto &e: entries_) {
		std::cout << e.id << ": " << e.name << std::endl;
	}
}

std::vector<std::string> RDBData::names() const
{
	std::vector<std::string> _response;
	std::transform(entries_.begin(), entries_.end(), std::back_inserter(_response), 
		[](const DBEntry entry) { return entry.name; });

	return _response;
}

std::vector<std::string> RDBData::entry(const std::string& name) const
{
	std::vector<std::string> _response;
	auto entryIt = std::find_if(entries_.begin(), entries_.end(), 
		[&name](const DBEntry& entry) { return entry.name == name; } );

	if (entryIt == entries_.end())
		return _response;

	_response.push_back(std::string("Name  : ").append(entryIt->name));
	_response.push_back(std::string("Type  : ").append(entryIt->type));
	_response.push_back(std::string("Login : ").append(entryIt->login));
	_response.push_back(std::string("MD5   : ").append(entryIt->md5));
	_response.push_back(std::string("hint  : ").append(entryIt->hint));

	return _response;
}

std::vector<std::string> RDBData::entryDetails(const std::string& name) const
{
	std::vector<std::string> _response;
	auto entryIt = std::find_if(entries_.begin(), entries_.end(), 
		[&name](const DBEntry& entry) { return entry.name == name; } );

	if (entryIt == entries_.end())
		return _response;

	_response.push_back( entryIt->details );
	return _response;
}
