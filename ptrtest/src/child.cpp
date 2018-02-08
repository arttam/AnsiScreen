#include <iostream>
#include "child.h"

void Child::sayMyName()
{
	std::cout << "Local name is: " << childName_ << std::endl;
}
