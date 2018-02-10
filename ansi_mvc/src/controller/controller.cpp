#include <iostream>
#include <cstdio> // std::getchar

#include "controller.h"

// Adds action, if action was actually inserted - returns true, otherwise false
// std::map insert returns pair of Iterator and bool, later says if insertion
// take place
bool Controller::addAction(char ch, std::function<void()> action)
{
	return (actions_.emplace(ch, action)).second;
}

void Controller::startHandler()
{
	keepRunning_ = true;
	while(keepRunning_) {
		auto _cmd = actions_.find(std::getchar());
		if (_cmd != actions_.end()) {
			_cmd->second();
		}
	}
}

void Controller::stopHandler()
{
	keepRunning_ = false;
}

