#include <iostream>
#include "child.h"

void Child::sayMyName()
{
	contanerFunc_(childName_);
}

void Child::setContainerFunc(std::function<void(const std::string&)> func)
{
	contanerFunc_ = func;
}

