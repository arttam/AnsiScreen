#include <iostream>
#include <fstream>
#include <iterator>

#include "../../ansi_console_lib/src/ansi_screen.h"
#include "../../ansi_console_lib/src/region.h"

int main(int argc, char** argv)
{
	if (argc < 1) {
		std::cerr << "Need file path" << std::endl;
		return 1;
	}

	AnsiScreen scr;
	scr.clearScreen();
	scr.drawBox();

	Separators _hlSeparators{ 
		{1, LeftCross}, 
		{scr.columns() / 2, MiddleCross}, 
		{scr.columns(), RightCross}
	};
	scr.drawHLine(scr.rows() / 2, 1, scr.columns(), _hlSeparators);

	Separators _vlSeparators {
		{1, TopCross },
		{scr.rows() / 2, MiddleCross},
		{scr.rows(), BottomCross}
	};
	scr.drawVLine(scr.columns() / 2, 1, scr.rows(), _vlSeparators);

	scr.savePoint("LeftTop", 2, 2);
	scr.savePoint("RightTop", scr.columns() / 2 + 1, 2);
	scr.savePoint("LeftBottom", 2, scr.rows() / 2 + 1);
	scr.savePoint("RightBottom", scr.columns() / 2 + 1, scr.rows() / 2 + 1);

	scr.gotoPoint("LeftTop");

	// Prepare some data to be shown
	std::ifstream _if(argv[1]);
	if (!_if.is_open()) {
		std::cerr << "Cannot open source file for reading" << std::endl;
		return 1;
	}
	std::istreambuf_iterator<char> _fileIt(_if);
	std::string _content(_fileIt, (std::istreambuf_iterator<char>()));
	_if.close();


	RegionPtr _region = scr.createRegion("LTRegion", 2, 2, scr.columns() / 2 - 1, scr.rows() / 2 - 1);
	_region->loadContent(_content);

	switch(_region->handleKeyboard()) {
		case RegionCmd::Command:
			std::cout << "Process region command";
			break;
		case RegionCmd::Escape:
			std::cout << "Process region escape";
			break;
		case RegionCmd::Tab:
			std::cout << "Switch focus to next one";
			break;
	}
	std::cin.get();

	return 0;
}
