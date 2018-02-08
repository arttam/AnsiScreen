#include <iostream>
#include <memory>
#include "container.h"

int main()
{
	Container _container;

	_container.addChild("First", Child("Kristina"));

	try {
		std::shared_ptr<Child> pChild = _container.findChild("First");
		pChild->sayMyName();
		std::cout << "References count now: " << pChild.use_count() << std::endl;
	}
	catch(bool notFound) {
		std::cerr << "did not found 'First' child" << std::endl;
	}
	
	return 0;
}
