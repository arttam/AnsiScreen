#include <iostream>
#include "../../ansi_mvc/src/controller/controller.h"
#include "../../ansi_mvc/src/model/model.h"
#include "../../ansi_mvc/src/view/view.h"
#include "../../ansi_mvc/src/rdb/rdb.h"

int main()
{
	RDBData rdb("/home/art/.rdb/sqlite.rdb");
	if (!rdb.read()) {
		std::cerr << "Unable to open database, leaving" << std::endl;
		return 1;
	}

	View view;

	view.clearScreen();
	view.drawBox();

	int _listPane = view.columns() / 3;
	view.drawHLine(1, 2, -1, {{_listPane, TopCross}});
	view.drawHLine(view.rows() - 10, _listPane, -1, {{_listPane, LeftCross}, {view.columns(), RightCross}});
	view.drawHLine(view.rows() - 2, 1, -1, 
		{
			{1, LeftCross},
			{_listPane, BottomCross},
			{view.columns(), RightCross}
		}
	);

	view.drawVLine(_listPane, 2, view.rows() - 2);

	view.savePoint("ListTop", 2, 2);
	view.savePoint("DetailsTop", _listPane + 1, 2);
	view.savePoint("DescriptionTop", _listPane + 1, view.rows() - 9);
	view.savePoint("CommandLine", 2, view.rows() - 1);

	Model list;
	if (!list.loadContent(rdb.names())) {
		std::cerr << "Failed to read list's contents" << std::endl;
		return 1;
	}
    
	list.setViewArea(_listPane - 2, view.rows() - 3, 2, 2, [&view](int x, int y) { view.moveCursor(x, y); });
	list.showViewModel();
	view.gotoPoint("LeftTop");

    Model entry;
    entry.setViewArea(view.columns() - _listPane - 1, view.rows() - 11, _listPane + 1, 2, [&view](int x, int y) { view.moveCursor(x, y); });
    entry.loadContent(rdb.entry(list.getSelected()));
    entry.showViewModel(false);
    
    Model details;
    details.setViewArea(view.columns() - _listPane - 1, 9, _listPane + 1, view.rows() - 9, [&view](int x, int y) { view.moveCursor(x, y); });
    details.loadContent(rdb.entryDetails(list.getSelected()));
    details.showViewModel(false);

	auto moveDown = [&view, &list, &entry, &rdb, &details]() {
		list.moveDown();
		if (list.moveCursor()) {
			view.moveDown();
		}
		if (list.needRefresh()) {
			view.saveCursor();
			list.showViewModel();
			view.restoreCursor();
		}
        // Update entry panel
        entry.loadContent(rdb.entry(list.getSelected()));
        entry.showViewModel(false);

        // Update details panel
        details.loadContent(rdb.entryDetails(list.getSelected()));
        details.showViewModel(false);
	};

	auto moveUp = [&view, &list, &entry, &rdb, &details]() {
		list.moveUp();
		if (list.moveCursor()) {
			view.moveUp();
		}
		if (list.needRefresh()) {
			view.saveCursor();
			list.showViewModel();
			view.restoreCursor();
		}
        // Update entry panel
        entry.loadContent(rdb.entry(list.getSelected()));
        entry.showViewModel(false);

        // Update details panel
        details.loadContent(rdb.entryDetails(list.getSelected()));
        details.showViewModel(false);
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
