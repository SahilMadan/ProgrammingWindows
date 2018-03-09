// Master include file for Windows applications.
#include <Windows.h>

// WINAPI: Define to use stdcall instead of cdecl.
int WINAPI WinMain(/* instance handle for this program */ HINSTANCE hInstance,
                   /* deprecated */ HINSTANCE hPrevInstance,
                   /* command line used to run program */ PSTR szCmdLine,
                   /* initial display (normal or maximized) */ int iCmdShow) {
  // Display dialog box with message.
  int result =
      MessageBox(/* window handle */ NULL,
                 /* body text */ TEXT("Hello, World!"),
                 /* caption bar text */ TEXT("HelloMsg"),
                 /* display flags */ MB_OKCANCEL | MB_DEFBUTTON1 | MB_ICONHAND);

  // Check result.
  if (result == IDOK) {
    MessageBox(NULL, TEXT("Ok Clicked!"), TEXT("OkMsg"), MB_OK);
  }

  return 0;
}
