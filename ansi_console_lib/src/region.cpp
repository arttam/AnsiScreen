#include <algorithm>
#include "region.h"

RegionCmd Region::handleKeyboard()
{
	setMode(Mode::Normal);
	bool _leaveHandler{false};

	while(!_leaveHandler) {
		switch(std::getchar()) {
			case 'h':
				moveLeft();
				break;
			case 'j':
				moveDown();
				break;
			case 'k':
				moveUp();
				break;
			case 'l':
				moveRight();
				break;
			case 'i':
				saveCursor();
				setMode(Mode::Insert);
				std::cin.get(_inputBuf, 4095);
				setMode(Mode::Normal);
				restoreCursor();
				break;
			case 'd':
				// Clear to the end of line
				std::cout << CSI << "0K";
				break;
			case 'D':
				// Clear to the beginning of line
				std::cout << CSI << "1K";
				break;
			case 's':
				// Clear to the end of screen
				std::cout << CSI << "0J";
				break;
			case 'S':
				// Clear to the beginning of screen
				std::cout << CSI << "1J";
				break;
			case 'Y':
				// Scroll screen down
				std::cout << CSI << "1T";
				break;
			case 'E':
				// Scroll scree up
				std::cout << CSI << "1S";
				break;
			case 'q':
				_leaveHandler = true;
				break;
			case '\t':
				_leaveHandler = true;
				return RegionCmd::Tab;
				break;
			default:
				break;
		}
	}
	return RegionCmd::Escape;
}

bool Region::loadContent(std::string& source)
{
	std::string _strBuf(source);
	contents_.resize(std::count_if(_strBuf.begin(), _strBuf.end(), [](char ch) { return (ch == '\n'); }));

	size_t rowNr = 0;
	std::string::size_type _sBegin = 0;
	auto _sEnd   = _strBuf.find_first_of('\n');
	while (_sEnd != std::string::npos) {
		contents_[rowNr++] = _strBuf.substr(_sBegin, _sEnd - _sBegin);
		_sBegin = ++_sEnd;
		_sEnd = _strBuf.find_first_of('\n', _sBegin);
	}
	refresh();
	moveCursor(left_, top_);

	return true;
}

void Region::clear()
{
	for(int row=0; row < height_ - 2; ++row) {
		moveCursor(left_, top_ + row);
		std::cout << std::string(width_ - 1, ' ');
	}
}

void Region::refresh()
{
	saveCursor();
	clear();
	for(int row=viewTop_; row < viewTop_ + height_ - 2; ++row) {
		moveCursor(left_, top_ + row - viewTop_);
		std::cout << contents_[viewTop_ + row].substr(viewLeft_, width_);
	}
	restoreCursor();
}

void Region::moveUp()
{
	if (yOffset_) {
		--yOffset_;
		std::cout << CSI << "1A";
		return;
	}

	if (viewTop_) {
		--viewTop_;
		--viewBottom_;
		refresh();
	}
}

void Region::moveDown()
{
	if (yOffset_ < height_ - 2) {
		++yOffset_;
		std::cout << CSI << "1B";
		return ;
	}

	++viewTop_;
	++viewBottom_;
	refresh();
}

void Region::moveLeft()
{
	if (xOffset_) {
		--xOffset_;
		std::cout << CSI << "1D";
		return;
	}

	--viewLeft_;
	refresh();
}

void Region::moveRight()
{
	if (xOffset_ < width_) {
		++xOffset_;
		std::cout << CSI << "1C";
		return;
	}

	++viewLeft_;
	refresh();
}
