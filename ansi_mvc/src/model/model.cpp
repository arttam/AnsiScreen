#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>

#include "model.h"

const char docPath[] = "/home/art/.vimrc";

void Model::markSelected()
{
	// Unmark previous
	std::string _prevVal = contents_[yOffset_ + prevRow_].substr(xOffset_, width_);
	if (static_cast<int>(_prevVal.length()) < width_)
		_prevVal.append(std::string(width_ - static_cast<int>(_prevVal.length()), ' '));

	moveFunc_(fromX_, fromY_ + prevRow_);
	std::cout << "\x1b[37;40m" << _prevVal;

	// Mark current
	std::string _currVal = contents_[yOffset_ + currPos_.second].substr(xOffset_, width_);
	if (static_cast<int>(_currVal.length()) < width_)
		_currVal.append(std::string(width_ - static_cast<int>(_currVal.length()), ' '));

	moveFunc_(fromX_, fromY_ + currPos_.second);
	std::cout << "\x1b[33;44m" << _currVal;
}

void Model::moveUp()
{
	needRefresh_ = false;
	moveCursor_  = true;
	if (currPos_.second > 0) {
		//--currPos_.second;
		prevRow_ = currPos_.second--;
		markSelected();
	}
	else {
		moveCursor_ = false;
		if (yOffset_) {
			--yOffset_;
			needRefresh_ = true;	
		}
	}
}

void Model::moveDown()
{
	needRefresh_ = false;
	moveCursor_  = true;
	if (currPos_.second >= height_ - 1) {
		moveCursor_ = false;
		if (yOffset_ < static_cast<int>(contents_.size()) - height_) {
			++yOffset_;
			needRefresh_ = true;
		}
	}
	else {
		//++currPos_.second;
		prevRow_ = currPos_.second++;
		markSelected();
	}
}

void Model::moveLeft()
{

}

void Model::moveRight()
{

}

void Model::showViewModel()
{
	for(int row = 0, fromy = fromY_; row < height_ && (row + yOffset_) < static_cast<int>(contents_.size()); ++row, ++fromy) {
		const char* color = (row == currPos_.second ? "\x1b[33;44m" : "\x1b[37;40m");
		moveFunc_(fromX_, fromy);
		std::cout << color << wiper_;
		moveFunc_(fromX_, fromy);
		std::cout << contents_[yOffset_ + row].substr(xOffset_, width_);

		/*
		moveFunc_(fromX_, fromy);
		std::cout << color << wiper_;
		moveFunc_(fromX_, fromy);
		std::cout << contents_[yOffset_ + row].substr(xOffset_, width_);
		*/
	}
}

void Model::setViewArea(int width, int height, int fromX, int fromY, std::function<void(int,int)> moveFunc)
{
	width_   = width;
	height_  = height;
	fromX_   = fromX;
	fromY_   = fromY;
	xOffset_ = 0;
	yOffset_ = 0;

	prevRow_ = 0;
	currPos_ = {0,0};
	needRefresh_ = false;
	moveCursor_  = true;

	wiper_ = std::string(width_, ' ');
	moveFunc_ = moveFunc;
}

bool Model::loadContent()
{
	std::ifstream ifs(docPath);
	if (ifs) {
		std::string _line;
		while (!ifs.eof()) {
			std::getline(ifs, _line);
			contents_.push_back(_line);
		}
		ifs.close();
		return true;
	}
	return false;
}
