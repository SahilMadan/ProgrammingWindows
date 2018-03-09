#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

// Use cdecl instead of stdcall.
int CDECL MessageBoxPrintf(const TCHAR* szCaption, const TCHAR* szFormat, ...) {
  // TCHAR points to WCHAR if unicode is defined; else CHAR.
  TCHAR szBuffer[1024];

  va_list pArgList;

  // The va_start macro (defined in STDARG.H) is usually equivalent to:
  // pArgList = (char *)&szFormat + sizeof(szFormat);
  // i.e. points to argument just above szFormat on the stack.
  va_start(pArgList, szFormat);

  // Generic macro (defined to normal or wide functions) to write formatted
  // output using a pointer to a list of arguments.
  _vsntprintf_s(szBuffer, sizeof(szBuffer) / sizeof(TCHAR), szFormat, pArgList);

  // Macro just zeroes out pArgList.
  va_end(pArgList);

  // Generic definition adds L## in front of wide strings.
  TEXT("Hello");

  // Generic definition points to MessageBoxA for ASCII and MessageBoxW for
  // Wide.
  return MessageBox(NULL, szBuffer, szCaption, MB_OK);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine,
                   int iCmdShow) {
  int cxScreen;
  int cyScreen;

  // Function retrieves the specified system metric or configuration setting (in
  // pixels).
  cxScreen = GetSystemMetrics(SM_CXSCREEN);
  cyScreen = GetSystemMetrics(SM_CYSCREEN);

  // Note that TEXT macro is a generic definition adds L## in front of wide
  // strings.
  MessageBoxPrintf(TEXT("ScreenSize"),
                   TEXT("The screen size is %i pixels wide by %i pixels high."),
                   cxScreen, cyScreen);
  return 0;
}
