#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>

#include "model.h"

const char docPath[] = "/usr/share/doc/w3m/README";

void Model::moveUp()
{
	needRefresh_ = false;
	moveCursor_  = true;
	if (currPos_.second) {
		--currPos_.second;
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
	if (currPos_.second >= height_) {
		moveCursor_ = false;
		if (yOffset_ < static_cast<int>(contents_.size()) - height_) {
			++yOffset_;
			needRefresh_ = true;
		}
	}
	else {
		++currPos_.second;
	}
}

void Model::moveLeft()
{

}

void Model::moveRight()
{

}

void Model::showViewModel(int fromx, int fromy, std::function<void(int,int)> moveFunc)
{
	for(int row = 0; row < height_ && (row + yOffset_) < static_cast<int>(contents_.size()); ++row, ++fromy) {
		moveFunc(fromx, fromy);
		std::cout << wiper_;
		moveFunc(fromx, fromy);
		std::cout << contents_[yOffset_ + row].substr(xOffset_, width_);
	}
}

void Model::setViewArea(int width, int height)
{
	width_   = width;
	height_  = height;
	xOffset_ = 0;
	yOffset_ = 0;

	currPos_ = {0,0};
	needRefresh_ = false;
	moveCursor_  = true;

	wiper_ = std::string(width_, ' ');
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
