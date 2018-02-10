#include <iostream>
#include <unistd.h>
#include <termios.h>
#include "view.h"

View::View(bool useAltScreen):usesAltScreen_(useAltScreen)
{
	if (usesAltScreen_) {
		std::cout << CSI << ToAltScr;
		init();
	}
}
View::~View() {
	if (usesAltScreen_) {
		std::cout << CSI << ToOrigScr;
	}
}

void View::setMode(Mode mode)
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

void View::init()
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

void View::setDimensions(int rows, int columns)
{
	rows_ = rows;
	columns_ = columns;
}

void View::clearScreen()
{
	// clear screen: move to 1;1, clear till end of screen
	std::cout << CSI << "1;1H" << CSI << "0J";
}

void View::drawBox(int x, int y, int wx, int wy)
{
	wx = (wx == -1) ? columns_ : wx;
	wy = (wy == -1) ? rows_    : wy;

	drawHLine(y, x, wx, { {x, LeftTopCorner}, {wx, RightTopCorner} });

	drawVLine(x, y+1, wy);
	drawVLine(wx, y+1, wy);

	drawHLine(wy, x, wx, { {x, LeftBottomCorner}, {wx, RightBottomCorner} });

}

// Positioning cursor: Y (row) ; X (column) H
void View::drawHLine(int y, int xFrom, int xTo, Separators separators)
{
	xTo = (xTo == -1) ? columns_ : xTo;

	std::cout << CSI << y << ";" << xFrom << "H";
	for (int col = xFrom; col < xTo; ++col)
		std::cout << HorizontalLine;

	if (!separators.empty())
		for(auto & separator : separators)
			std::cout << CSI << y << ";" << separator.first << "H" << separator.second;
}

void View::drawVLine(int x, int yFrom, int yTo, Separators separators)
{
	yTo = (yTo == -1) ? rows_ : yTo;

	std::cout << CSI << yFrom << ";" << x << "H";
	for (int row = yFrom; row < yTo; ++row)
		std::cout << CSI << row << ";" << x << "H" << VerticalLine;

	if (!separators.empty())
		for (auto & separator : separators)
			std::cout << CSI << separator.first << ";" << x << "H" << separator.second;
}

void View::moveCursor(int x, int y) const
{
	std::cout << CSI << y << ";" << x << "H";
}

void View::moveUp() const
{
	std::cout << CSI << "1A";
}

void View::moveDown() const
{
	std::cout << CSI << "1B";
}

void View::moveLeft() const
{
	std::cout << CSI << "1D";
}

void View::moveRight() const
{
	std::cout << CSI << "1C";
}

void View::saveCursor() const
{
	std::cout << CSI << "s";
}

void View::restoreCursor() const
{
	std::cout << CSI << "u";
}

void View::savePoint(std::string pointName, Point& point)
{
	points_[pointName] = point;
}

void View::savePoint(std::string pointName, Point&& point)
{
	points_[pointName] = point;
}

bool View::gotoPoint(std::string pointName) const
{
	if (points_.count(pointName)) {
		moveCursor(points_.at(pointName));
		return true;
	}
	return false;
}

