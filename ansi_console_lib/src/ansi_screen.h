#ifndef __UsesAnsiScreen__
#define __UsesAnsiScreen__

#include <vector>
#include <map>
#include <memory>

#include "commons.h"
#include "region.h"

using Separator = std::pair<int, const char*>;
using Separators = std::vector<Separator>;
using Point = std::pair<int, int>;
using Points = std::map<std::string, Point>;
using RegionPtr = std::shared_ptr<Region>;
using Regions = std::map<std::string, RegionPtr>;
using CreateRes = std::pair<Regions::iterator, bool>;

class AnsiScreen: std::enable_shared_from_this<AnsiScreen>
{
	int rows_;
	int columns_;
    
	Points points_;
	Regions regions_;
public:

	AnsiScreen();
	~AnsiScreen();

	int rows() const { return rows_; }
	int columns() const { return columns_; }

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

    void savePoint(std::string pointName, Point&& point);
    void savePoint(std::string pointName, int x, int y) { savePoint(pointName, Point(x, y)); }
    void savePoint(std::string pointName, Point& point);
    bool gotoPoint(std::string pointName) const;

	// Region operaitons
	CreateRes createRegion(const std::string& regionName, int left, int top, int width, int height);

private:
	void init();
};

#endif
