#ifndef __USES_CONTROLLER_H__
#define __USES_CONTROLLER_H__

#include <map>
#include <functional>
#include "../view/commons.h"

class Controller
{
	bool keepRunning_;
	std::map<char, std::function<void()>> actions_;
public:
	Controller() = default;
	~Controller() = default;

	bool addAction(char ch, std::function<void()> action);
	void stopHandler();
	void startHandler();
};

#endif
