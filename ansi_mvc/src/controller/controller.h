#ifndef __USES_CONTROLLER_H__
#define __USES_CONTROLLER_H__

#include <map>
#include <functional>
#include <string>
#include "../view/commons.h"

class Controller
{
	bool keepRunning_;
	std::string currentModel_;
	std::map<std::string, std::map<char, std::function<void()>>> actions_;
public:
	Controller() = default;
	~Controller() = default;

	std::string currenModel() { return currentModel_; }
	bool currentModel(const std::string& model);

	bool addAction(std::string model, char ch, std::function<void()> action);
	void stopHandler();
	void startHandler();
};

#endif
