#ifndef __UsesAnsiScreen__
#define __UsesAnsiScreen__

#include <vector>
#include <map>
#include <memory>

#include "region.h"

static const char *CSI = "\x1b[";
static char _inputBuf[4096];

static const char RightBottomCorner[] =  "\e(0\x6a\e(B"; // 188 Right Bottom corner
static const char RightTopCorner[] 	  =  "\e(0\x6b\e(B"; // 187 Right Top corner
static const char LeftTopCorner[]     =  "\e(0\x6c\e(B"; // 201 Left Top cornet
static const char LeftBottomCorner[]  =  "\e(0\x6d\e(B"; // 200 Left Bottom corner
static const char MiddleCross[]       =  "\e(0\x6e\e(B"; // 206 Midle Cross
static const char HorizontalLine[]    =  "\e(0\x71\e(B"; // 205 Horizontal Line
static const char LeftCross[]         =  "\e(0\x74\e(B"; // 204 Left Cross
static const char RightCross[]        =  "\e(0\x75\e(B"; // 185 Right Cross
static const char BottomCross[]       =  "\e(0\x76\e(B"; // 202 Bottom Cross
static const char TopCross[]          =  "\e(0\x77\e(B"; // 203 Top Cross
static const char VerticalLine[]      =  "\e(0\x78\e(B"; // 186 Vertical Line
// Extras
static const char ToAltScr[]          = "?47h";
static const char ToOrigScr[]         = "?47l";

enum class Mode { Command, Insert, Normal };
enum class RegionCmd { Tab, Command, Escape };

using Separator = std::pair<int, const char*>;
using Separators = std::vector<Separator>;
using Point = std::pair<int, int>;
using Points = std::map<std::string, Point>;
using RegionPtr = std::shared_ptr<Region>;
using Regions = std::map<std::string, RegionPtr>;

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
	RegionPtr createRegion(const std::string& regionName, int left, int top, int width, int height);

private:
	void init();
};

#endif
