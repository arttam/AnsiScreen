#include <iostream>
#include "../../ansi_mvc/src/controller/controller.h"
#include "../../ansi_mvc/src/model/model.h"
#include "../../ansi_mvc/src/view/view.h"

int main()
{
	View view;

	view.clearScreen();
	view.drawBox();

	Separators _hlSeparators{ 
		{1, LeftCross}, 
		{view.columns() / 2, MiddleCross}, 
		{view.columns(), RightCross}
	};
	view.drawHLine(view.rows() / 2, 1, view.columns(), _hlSeparators);

	Separators _vlSeparators {
		{1, TopCross },
		{view.rows() / 2, MiddleCross},
		{view.rows(), BottomCross}
	};
	view.drawVLine(view.columns() / 2, 1, view.rows(), _vlSeparators);

	view.savePoint("LeftTop", 2, 2);
	view.savePoint("RightTop", view.columns() / 2 + 1, 2);
	view.savePoint("LeftBottom", 2, view.rows() / 2 + 1);
	view.savePoint("RightBottom", view.columns() / 2 + 1, view.rows() / 2 + 1);

	view.gotoPoint("LeftTop");

	/*
	Controller controller;
	controller.addAction('k', [&view]() { view.moveUp(); });
	controller.addAction('j', [&view]() { view.moveDown(); });
	controller.addAction('h', [&view]() { view.moveLeft(); });
	controller.addAction('l', [&view]() { view.moveRight(); });
	controller.addAction('q', [&controller]() { controller.stopHandler(); });

	view.setMode(Mode::Normal);
	controller.startHandler();
	*/

	Model model;
	if (!model.loadContent()) {
		std::cerr << "Failed to read model's contents" << std::endl;
		return 1;
	}

	model.setViewArea(view.columns() / 2 - 2, view.rows() / 2 - 2, 2, 2, [&view](int x, int y) { view.moveCursor(x, y); });
	model.showViewModel();
	view.gotoPoint("LeftTop");

	auto moveDown = [&view, &model]() {
		model.moveDown();
		if (model.moveCursor()) {
			view.moveDown();
		}
		if (model.needRefresh()) {
			view.saveCursor();
			model.showViewModel();
			view.restoreCursor();
		}
	};

	auto moveUp = [&view, &model]() {
		model.moveUp();
		if (model.moveCursor()) {
			view.moveUp();
		}
		if (model.needRefresh()) {
			view.saveCursor();
			model.showViewModel();
			view.restoreCursor();
		}
	};

	Controller controller;
	controller.addAction('q', [&controller]() { controller.stopHandler(); });
	controller.addAction('j', moveDown);
	controller.addAction('k', moveUp);

	view.setMode(Mode::Normal);
	controller.startHandler();

	std::cin.get();

	return 0;
}
