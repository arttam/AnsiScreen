#include <iostream>
#include <cstdio> // std::getchar

#include "controller.h"

bool Controller::currentModel(const std::string& model)
{
	if (!actions_.count(model))
		return false;

	currentModel_ = model;
	return true;
}

// Adds action, if action was actually inserted - returns true, otherwise false
// std::map insert returns pair of Iterator and bool, later says if insertion
// take place
bool Controller::addAction(std::string model, char ch, std::function<void()> action)
{
	if (!actions_.count(model)) {
		actions_[model] = std::map<char, std::function<void()>>();
	}
	return actions_[model].emplace(ch, action).second;
	
	//return (actions_.emplace(ch, action)).second;
}

void Controller::startHandler()
{
	keepRunning_ = true;
	while(keepRunning_) {
		auto _cmd = actions_[currentModel_].find(std::getchar());
		if (_cmd != actions_[currentModel_].end()) {
			_cmd->second();
		}
	}
}

void Controller::stopHandler()
{
	keepRunning_ = false;
}

