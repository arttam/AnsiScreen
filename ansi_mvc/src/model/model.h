#ifndef __USES_MODEL_H__
#define __USES_MODEL_H__
#include <string>
#include <vector>
#include <functional>
#include <memory>

class Model
{
	int width_;
	int height_;
	int xOffset_;
	int yOffset_;
	int fromX_;
	int fromY_;

	bool needRefresh_;
	bool moveCursor_;
	int prevRow_;
	std::pair<int, int> currPos_;
	std::string wiper_;
	std::vector<std::string> contents_;
	std::function<void(int, int)> moveFunc_;

public:
	Model() = default;
	~Model() = default;

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	bool needRefresh() const { return needRefresh_; }
	bool moveCursor()  const { return moveCursor_; }

	void setViewArea(int width, int height, int fromX, int fromY, std::function<void(int,int)> moveFunc);
	bool loadContent(std::vector<std::string>&& src);
	void showViewModel(bool markSelected = true);

	// For possible control of other regions
	const std::string& getSelected() const;

private:
	void markSelected();
};
#endif
