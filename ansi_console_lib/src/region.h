#ifndef __USES_REGION_H__
#define __USES_REGION_H__
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <memory>

class AnsiScreen;
enum class RegionCmd;


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

	std::shared_ptr<AnsiScreen> parent_;
	std::vector<std::string> contents_;

public:
    Region(std::shared_ptr<AnsiScreen> screen, int left, int top, int width, int height)
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
		, parent_(screen)
    {}

	bool loadContent(std::string& source);
    RegionCmd handleKeyboard();

private:
	void clear();
	void refresh();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

};

#endif
