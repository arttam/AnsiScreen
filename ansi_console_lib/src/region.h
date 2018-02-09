#ifndef __USES_REGION_H__
#define __USES_REGION_H__
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <memory>
#include <functional>

#include "commons.h"

class Region
{
	int top_;
	int left_;
    int width_;
    int height_;
	int xOffset_;
	int yOffset_;
	int viewTop_;
	int viewBottom_;
	int viewLeft_;
//	int viewRight_;

	std::vector<std::string> contents_;

	// Screen methods used by region
	std::function<void()> saveCursor;
	std::function<void()> restoreCursor;
	std::function<void(Mode)> setMode;
	std::function<void(int, int)> moveCursor;

public:
    Region(int left, int top, int width, int height)
        : top_(top)
		, left_(left)
		, width_(width)
        , height_(height)
		, xOffset_(0)
		, yOffset_(0)
		, viewTop_(0)
		, viewBottom_(height - 2)
	  	, viewLeft_(0)
//	 	, viewRight_(width - 2)
    {}

	bool loadContent(std::string& source);
    RegionCmd handleKeyboard();

	// Screen method setters
	void setSaveCursor(std::function<void()> pSaveCursor) { saveCursor = pSaveCursor; }
	void setRestoreCursor(std::function<void()> pRestoreCursor) { restoreCursor = pRestoreCursor; }
	void setSetMode(std::function<void(Mode)> pSetMode) { setMode = pSetMode; }
	void setMoveCursor(std::function<void(int, int)> pMoveCursor) { moveCursor = pMoveCursor; }

private:
	void clear();
	void refresh();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

};

#endif
