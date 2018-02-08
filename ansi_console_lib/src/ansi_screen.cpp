#include <unistd.h>
#include <termios.h>
#include <iostream>
#include <utility> 

#include "ansi_screen.h"

AnsiScreen::AnsiScreen()
{
	// Switch to altername screen (at least try)
	std::cout << CSI << ToAltScr;
	init();
}

AnsiScreen::~AnsiScreen()
{
	// Switch back to original screen, from altername
	std::cout << CSI << ToOrigScr;
}

void AnsiScreen::setMode(Mode mode)
{
	struct termios tios;
	tcgetattr(STDIN_FILENO, &tios);

	switch(mode) {
		case Mode::Command:
			break;
		case Mode::Insert:
			tios.c_lflag |= ICANON;
			tios.c_lflag |= ECHO;
			break;
		case Mode::Normal:
			tios.c_lflag &= ~ICANON;
			tios.c_lflag &= ~ECHO;
			break;
	}

	tcsetattr(STDIN_FILENO, TCSANOW, &tios);
}

void AnsiScreen::init()
{
	setMode(Mode::Normal);

	std::cout << CSI << "999;999H";
	std::cout << CSI << "6n";
	std::cin.get(_inputBuf, 4095, 'R');
	// Buf now looks like: '?[54;179'
	std::cin.ignore(1);

	std::string _posStr(_inputBuf);
	size_t _bracket = _posStr.find_first_of('[');
	size_t _semicolon = _posStr.find_first_of(';');
	if (_bracket == std::string::npos || _semicolon == std::string::npos) {
		std::cerr << "Failed to process position string: " << _posStr << std::endl;
		return ;
	}
	
	rows_    = std::stoi(_posStr.substr(++_bracket));
	columns_ = std::stoi(_posStr.substr(++_semicolon));

	setMode(Mode::Insert);
}

void AnsiScreen::clearScreen()
{
	// clear screen: move to 1;1, clear till end of screen
	std::cout << CSI << "1;1H" << CSI << "0J";
}

void AnsiScreen::drawBox(int x, int y, int wx, int wy)
{
	wx = (wx == -1) ? columns_ : wx;
	wy = (wy == -1) ? rows_    : wy;

	drawHLine(y, x, wx, { {x, LeftTopCorner}, {wx, RightTopCorner} });

	drawVLine(x, y+1, wy);
	drawVLine(wx, y+1, wy);

	drawHLine(wy, x, wx, { {x, LeftBottomCorner}, {wx, RightBottomCorner} });

}

// Positioning cursor: Y (row) ; X (column) H
void AnsiScreen::drawHLine(int y, int xFrom, int xTo, Separators separators)
{
	xTo = (xTo == -1) ? columns_ : xTo;

	std::cout << CSI << y << ";" << xFrom << "H";
	for (int col = xFrom; col < xTo; ++col)
		std::cout << HorizontalLine;

	if (!separators.empty()) 
		for(auto & separator : separators)
			std::cout << CSI << y << ";" << separator.first << "H" << separator.second;
}

void AnsiScreen::drawVLine(int x, int yFrom, int yTo, Separators separators)
{
	yTo = (yTo == -1) ? rows_ : yTo;

	std::cout << CSI << yFrom << ";" << x << "H";
	for (int row = yFrom; row < yTo; ++row)
		std::cout << CSI << row << ";" << x << "H" << VerticalLine;

	if (!separators.empty()) 
		for (auto & separator : separators)
			std::cout << CSI << separator.first << ";" << x << "H" << separator.second;
}

void AnsiScreen::moveCursor(int x, int y) const
{
	std::cout << CSI << y << ";" << x << "H";
}

void AnsiScreen::saveCursor() const
{
	std::cout << CSI << "s";
}

void AnsiScreen::restoreCursor() const
{
	std::cout << CSI << "u";
}

void AnsiScreen::savePoint(std::string pointName, Point& point)
{
	points_[pointName] = point;
}

void AnsiScreen::savePoint(std::string pointName, Point&& point)
{
	points_[pointName] = point;
}

bool AnsiScreen::gotoPoint(std::string pointName) const 
{
	if (points_.count(pointName)) {
		moveCursor(points_.at(pointName));
		return true;
	}
	return false;
}

RegionPtr AnsiScreen::createRegion(const std::string& regionName, int left, int top, int width, int height)
{
	// Below method would return pair: <newly created element, boolean - true if inserted, false otherwise>
	return regions_.insert(std::make_pair(regionName, RegionPtr(new Region(shared_from_this(), left, top, width, height)))).first->second;
}
