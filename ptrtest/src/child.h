#ifndef __USES_CHILD_H__
#define __USES_CHILD_H__
#include <memory>
#include <string>

class Child
{
	std::string childName_;
public:
	Child(const std::string& src): childName_(src) {}
	Child(const Child& src): childName_(src.childName_) {}
	Child(Child* pSrc): childName_(pSrc->childName_) {}
	~Child() = default;

	void sayMyName();
};

#endif
