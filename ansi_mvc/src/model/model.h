#ifndef __USES_MODEL_H__
#define __USES_MODEL_H__
#include <string>
#include <vector>
#include <functional>

class Model
{
	int width_;
	int height_;
	int xOffset_;
	int yOffset_;

	bool needRefresh_;
	bool moveCursor_;
	std::pair<int, int> currPos_;
	std::string wiper_;
	std::vector<std::string> contents_;

public:
	Model() = default;
	~Model() = default;

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	bool needRefresh() const { return needRefresh_; }
	bool moveCursor()  const { return moveCursor_; }

	void setViewArea(int width, int height);
	bool loadContent();
	void showViewModel(int fromx, int fromy, std::function<void(int,int)> moveFunc);
};
#endif
