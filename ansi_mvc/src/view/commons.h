#ifndef __USES_COMMONS_H__
#define __USES_COMMONS_H__

enum class Mode { Command, Insert, Normal };
enum class RegionCmd { Tab, Command, Escape };

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

// Colors
static const char SelectedColor[] = "\x1b[30;47m";
static const char DefaultColor[]  = "\x1b[47;30m";

#endif
