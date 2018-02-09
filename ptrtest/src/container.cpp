#include <iostream>
#include "container.h"

void Container::introduce(const std::string& who)
{
	std::cout << "Hello, " << who << " says Hi!" << std::endl;
}

void Container::addChild(const std::string& name, Child&& child)
{
	std::cerr << "rvalue usage for addChild" << std::endl;

	auto _child = std::make_shared<Child>(child);
	_child->setContainerFunc([this](const std::string& s) { return this->introduce(s); });

	children_.insert(std::make_pair(name, _child));
}

void Container::addChild(const std::string& name, const Child& child)
{
	std::cerr << "const Child& usage for addChild" << std::endl;

	auto _child = std::make_shared<Child>(child);
	_child->setContainerFunc([this](const std::string& s) { return this->introduce(s); });
	children_.insert(std::make_pair(name, _child));
}

std::shared_ptr<Child>& Container::findChild(const std::string& name)
{
	auto _childIt = children_.find(name);
	if (_childIt == children_.end())
		throw false;

	return _childIt->second;
}

void Container::countRefs(const std::string& name) const
{
	auto _childIt = children_.find(name);
	if (_childIt != children_.end()) {
		std::cout << "Count of " << name << " is " << _childIt->second.use_count() << std::endl;
	}
	else {
		std::cerr << "Did not found: " << name << std::endl;
	}
}
