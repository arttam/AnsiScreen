#ifndef __USES_CONTAINER_H__
#define __USES_CONTAINER_H__
#include <string>
#include <memory>
#include <map>

#include "child.h"

class Container
{
	std::map<std::string, std::shared_ptr<Child>> children_;
public:
	Container() = default;

	void introduce(const std::string& who);
	void addChild(const std::string& name, Child&& child);
	void addChild(const std::string& name, const Child& child);
	std::shared_ptr<Child>& findChild(const std::string& name);
};
#endif
