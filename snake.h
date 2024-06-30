#pragma once

#include "resource.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#define LENGTH 16L

typedef BYTE CELL;

#define EMPTY_CELL  0ui8
#define LEFT_CELL   1ui8
#define UP_CELL     2ui8
#define RIGHT_CELL  3ui8
#define DOWN_CELL   4ui8
#define APPLE_CELL  5ui8

typedef struct USERDATA {

  CELL map[LENGTH][LENGTH];
  BOOL ongoing;
  POINT head;
  POINT tail;
  CELL prehead;
  LONG length;

} USERDATA, *LPUSERDATA;

VOID newApple(LPUSERDATA data);

BOOL setDir(LPUSERDATA data, WPARAM key);

BOOL move(LPUSERDATA data, POINT* point);

BOOL shift(LPUSERDATA data, HWND hWnd);

#define IDT_FRAME 1

VOID CALLBACK FrameUpdate(HWND hWnd, UINT uMsg, UINT_PTR wParam, DWORD lParam);

typedef BYTE REGION;

#define BEYOND_REGION   0ui8
#define EMPTY1_REGION   1ui8
#define EMPTY2_REGION   2ui8
#define SNAKE_REGION    3ui8
#define APPLE_REGION    4ui8

#define REGION_COUNT    5ui8

REGION getRegion(LPUSERDATA data, LONG x, LONG y);

#define BEYOND_COLOR  RGB(0, 0, 64)
#define EMPTY1_COLOR  RGB(0, 0, 96)
#define EMPTY2_COLOR  RGB(0, 0, 128)
#define SNAKE_COLOR   RGB(0, 128, 0)
#define APPLE_COLOR   RGB(128, 0, 0)

typedef struct RGNBR {

  HRGN hrgn;
  HBRUSH hbr;

} RGNBR, *LPRGNBR;
