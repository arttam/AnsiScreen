#include <iostream>
#include "container.h"

void Container::introduce(const std::string& who)
{
	std::cout << "Hello, " << who << " says Hi!" << std::endl;
}

void Container::addChild(const std::string& name, Child&& child)
{
	children_.insert(std::make_pair(name, std::make_shared<Child>(child)));
}

void Container::addChild(const std::string& name, const Child& child)
{
	children_.insert(std::make_pair(name, std::make_shared<Child>(child)));
}

std::shared_ptr<Child>& Container::findChild(const std::string& name)
{
	auto _childIt = children_.find(name);
	if (_childIt == children_.end())
		throw false;

	return _childIt->second;
}
