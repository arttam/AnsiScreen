#ifndef __USES_VIEW_H__
#define __USES_VIEW_H__
#include <vector>
#include <map>

#include "commons.h"

using Separator = std::pair<int, const char*>;
using Separators = std::vector<Separator>;
using Point = std::pair<int, int>;
using Points = std::map<std::string, Point>;

class View
{
	bool usesAltScreen_;
	int rows_;
	int columns_;
    
	Points points_;
public:
	View(bool useAltScreen = true);
	~View();

	int rows() const { return rows_; }
	int columns() const { return columns_; }
	void setDimensions(int rows, int columns);

    // Screen mode
	void setMode(Mode mode);
	void clearScreen();

    // Drawing
	void drawHLine(int y, int xFrom = 1, int xTo = -1, Separators separators = {});
	void drawVLine(int x, int yFrom = 1, int yTo = -1, Separators separators = {});
	void drawBox(int x = 1, int y = 1, int wx = -1, int wy = -1);

    // Cursor
    void moveCursor(int x, int y) const;
    void moveCursor(const Point& point) const { moveCursor(point.first, point.second); }
    void saveCursor() const;
    void restoreCursor() const;
	void moveUp() const;
	void moveDown() const;
	void moveLeft() const;
	void moveRight() const;

    void savePoint(std::string pointName, Point&& point);
    void savePoint(std::string pointName, int x, int y) { savePoint(pointName, Point(x, y)); }
    void savePoint(std::string pointName, Point& point);
    bool gotoPoint(std::string pointName) const;

private:
	void init();
};

#endif
