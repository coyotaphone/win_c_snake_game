#include "snake.h"

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, INT nCmdShow) {

  srand(GetTickCount());

  BOOL info = FALSE;
  SetUserObjectInformation(GetCurrentProcess(), UOI_TIMERPROC_EXCEPTION_SUPPRESSION, &info, sizeof(info));

  WNDCLASS wndClass = {
    CS_VREDRAW | CS_HREDRAW, WindowProc, 0, 0, hInstance, LoadIcon(NULL, IDI_APPLICATION),
    LoadCursor(NULL, IDC_ARROW), NULL, NULL, L"SnakeWindow"
  };
  LPCWSTR lpClassName = (LPCWSTR)RegisterClass(&wndClass);

  LONG side = (1L + LENGTH + 1L) * 35L;
  RECT rect = { 0L, 0L, side, side };
  AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
  int nWidth = rect.right - rect.left;
  int nHeight = rect.bottom - rect.top;
  SystemParametersInfo(SPI_GETWORKAREA, 0U, &rect, 0U);

  USERDATA data = {
    {
      RIGHT_CELL, RIGHT_CELL, RIGHT_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
      EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
      EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
      EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
      EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
      EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
      EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
      EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
      EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
      EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
      EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
      EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
      EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
      EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
      EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
      EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL
    }, FALSE, { 2L, 0L }, { 0L, 0L }, RIGHT_CELL, 3L
  };
  ShowWindow(CreateWindow(
    lpClassName, TEXT(NAME_STR), WS_OVERLAPPEDWINDOW,
    (rect.left + rect.right - nWidth) >> 1, (rect.top + rect.bottom - nHeight) >> 1,
    nWidth, nHeight, NULL, NULL, hInstance, &data
  ), nCmdShow);

  MSG msg;
  while (GetMessage(&msg, NULL, 0U, 0U))
    DispatchMessage(&msg);

  UnregisterClass(lpClassName, hInstance);

  return 0;

}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

  switch (uMsg) {

  case WM_CREATE: {
    LPUSERDATA data = (LPUSERDATA)((LPCREATESTRUCT)lParam)->lpCreateParams;
    newApple(data);
    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)data);
  } return 0LL;

  case WM_DESTROY:
    PostQuitMessage(0);
    return 0LL;

  case WM_PAINT: {
    PAINTSTRUCT paint;
    BeginPaint(hWnd, &paint);

    RECT rect;
    GetClientRect(hWnd, &rect);
    LONG tile = min(rect.right, rect.bottom) / (1L + LENGTH + 1L);
    LONG side = tile * LENGTH;
    POINT offset = { (rect.right - side) >> 1, (rect.bottom - side) >> 1 };

    RGNBR rgnbr[REGION_COUNT] = {

      CreateRectRgnIndirect(&rect),  CreateSolidBrush(BEYOND_COLOR),
      CreateRectRgn(0, 0, 0, 0),     CreateSolidBrush(EMPTY1_COLOR),
      CreateRectRgn(0, 0, 0, 0),     CreateSolidBrush(EMPTY2_COLOR),
      CreateRectRgn(0, 0, 0, 0),     CreateSolidBrush(SNAKE_COLOR),
      CreateRectRgn(0, 0, 0, 0),     CreateSolidBrush(APPLE_COLOR),

    };

    LPUSERDATA data = (LPUSERDATA)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    HRGN mapRgn = CreateRectRgn(offset.x, offset.y, offset.x + side, offset.y + side);
    CombineRgn(rgnbr->hrgn, rgnbr->hrgn, mapRgn, RGN_DIFF);
    DeleteObject(mapRgn);

    int y1 = offset.y;
    int y2 = y1 + tile;
    for (LONG y = 0L; y < LENGTH; ++y) {
      int x1 = offset.x;
      int x2 = x1 + tile;
      for (LONG x = 0L; x < LENGTH; ++x) {
        HRGN cellRgn = CreateRectRgn(x1, y1, x2, y2);
        HRGN dstRgn = rgnbr[getRegion(data, x, y)].hrgn;
        CombineRgn(dstRgn, dstRgn, cellRgn, RGN_OR);
        DeleteObject(cellRgn);
        x1 += tile;
        x2 += tile;
      }
      y1 += tile;
      y2 += tile;
    }
    
    HRGN clipRgn = CreateRectRgnIndirect(&paint.rcPaint);
    RGNBR* end = rgnbr + REGION_COUNT;
    for (RGNBR* obj = rgnbr; obj < end; obj++) {
      CombineRgn(obj->hrgn, obj->hrgn, clipRgn, RGN_AND);
      FillRgn(paint.hdc, obj->hrgn, obj->hbr);
      DeleteObject(obj->hrgn);
      DeleteObject(obj->hbr);
    }
    DeleteObject(clipRgn);

    EndPaint(hWnd, &paint);
    return 0LL;
  }

  case WM_ERASEBKGND:
    return 0LL;

  case WM_KEYDOWN: {
    LPUSERDATA data = (LPUSERDATA)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    if (setDir(data, wParam) && !data->ongoing) {
      data->ongoing = TRUE;
      SetTimer(hWnd, IDT_FRAME, 100U, FrameUpdate);
    }
    return 0LL;
  }

  default:
    return DefWindowProc(hWnd, uMsg, wParam, lParam);

  }

}

VOID newApple(LPUSERDATA data) {
  LONG count = rand() % (LENGTH * LENGTH - data->length);
  for (LONG x = 0L; x < LENGTH; ++x)
    for (LONG y = 0L; y < LENGTH; ++y)
      if (data->map[y][x] == EMPTY_CELL && !count--) {
        data->map[y][x] = APPLE_CELL;
        return;
      }
}

BOOL setDir(LPUSERDATA data, WPARAM key) {
  BOOL result;
  switch (key) {
  case VK_LEFT:
    if (result = data->prehead != RIGHT_CELL)
      data->map[data->head.y][data->head.x] = LEFT_CELL;
    break;
  case VK_UP:
    if (result = data->prehead != DOWN_CELL)
      data->map[data->head.y][data->head.x] = UP_CELL;
    break;
  case VK_RIGHT:
    if (result = data->prehead != LEFT_CELL)
      data->map[data->head.y][data->head.x] = RIGHT_CELL;
    break;
  case VK_DOWN:
    if (result = data->prehead != UP_CELL)
      data->map[data->head.y][data->head.x] = DOWN_CELL;
    break;
  default:
    result = FALSE;
    break;
  }
  return result;
}

BOOL move(LPUSERDATA data, POINT* point) {
  BOOL result;
  switch (data->map[point->y][point->x]) {
  case LEFT_CELL:
    result = point->x > 0L && getRegion(data, --point->x, point->y) != SNAKE_REGION;
    break;
  case UP_CELL:
    result = point->y > 0L && getRegion(data, point->x, --point->y) != SNAKE_REGION;
    break;
  case RIGHT_CELL:
    result = point->x < LENGTH - 1L && getRegion(data, ++point->x, point->y) != SNAKE_REGION;
    break;
  case DOWN_CELL:
    result = point->y < LENGTH - 1L && getRegion(data, point->x, ++point->y) != SNAKE_REGION;
    break;
  default:
    result = FALSE;
    break;
  }
  return result;
}

BOOL shift(LPUSERDATA data, HWND hWnd) {
  BOOL result;
  data->prehead = data->map[data->head.y][data->head.x];
  if (result = move(data, &data->head)) {
    CELL* newhead = &data->map[data->head.y][data->head.x];
    BOOL check = *newhead == APPLE_CELL;
    *newhead = data->prehead;
    if (check)
      if (++data->length < 256L)
        newApple(data);
      else
        KillTimer(hWnd, IDT_FRAME);
    else {
      CELL* tailcell = &data->map[data->tail.y][data->tail.x];
      move(data, &data->tail);
      *tailcell = EMPTY_CELL;
    }
  }
  return result;
}

VOID CALLBACK FrameUpdate(HWND hWnd, UINT uMsg, UINT_PTR wParam, DWORD lParam) {

  if (shift((LPUSERDATA)GetWindowLongPtr(hWnd, GWLP_USERDATA), hWnd)) {
    InvalidateRect(hWnd, NULL, FALSE);
    UpdateWindow(hWnd);
  }
  else
    KillTimer(hWnd, IDT_FRAME);

}

REGION getRegion(LPUSERDATA data, LONG x, LONG y) {
  switch (data->map[y][x]) {
  case EMPTY_CELL:
    if ((x + y) % 2L)
      return EMPTY1_REGION;
    else
      return EMPTY2_REGION;
  case LEFT_CELL:
  case UP_CELL:
  case RIGHT_CELL:
  case DOWN_CELL:
    return SNAKE_REGION;
  case APPLE_CELL:
    return APPLE_REGION;
  default:
    return BEYOND_REGION;
  }
}
