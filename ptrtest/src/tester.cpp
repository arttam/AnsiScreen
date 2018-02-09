#include <iostream>
#include <memory>
#include "container.h"

int main()
{
	Container _container;

	Child _rob("Robert");
	_container.addChild("First", Child("Kristina"));
	_container.addChild("Second", _rob);

	try {
		std::shared_ptr<Child> pChild = _container.findChild("First");
		std::shared_ptr<Child> pSecond = _container.findChild("Second");
		pChild->sayMyName();
		pSecond->sayMyName();
	}
	catch(bool notFound) {
		std::cerr << "did not found 'First' child" << std::endl;
	}

	return 0;
}
