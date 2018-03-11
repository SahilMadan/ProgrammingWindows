#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine,
                   int iCmdShow) {
  static TCHAR szAppName[] = TEXT("HelloWindow");
  static TCHAR szWinClassName[] = TEXT("HelloWindowClass");

  // Before you create an application window, you must register a window class.
  // The window class defines the window procedure (WinProc) and some other
  // characteristics of the windows that are created based on that class.
  WNDCLASS wndclass;

  // Completely repaint when we resize horizontally or vertically.
  wndclass.style = CS_HREDRAW | CS_VREDRAW;

  // Identify the window procedure.
  wndclass.lpfnWndProc = WndProc;

  // Reserve some extra space in the class structure and window structure.
  wndclass.cbClsExtra = 0;
  wndclass.cbWndExtra = 0;

  // Instance handle of the program.
  wndclass.hInstance = hInstance;

  // Load a (currently predefined) icon/cursor for use by the program.
  // Specify hInstance containing the resource and the resource identifier.
  wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);

  // Specify a background color by giving a handle to a brush.
  // GetStockObject obtains a graphic object (pens, brushes, fonts, palettes).
  wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

  // Specify a menu name (we don't have one).
  wndclass.lpszMenuName = NULL;

  // The class must be given an identifiable name.
  wndclass.lpszClassName = szWinClassName;

  if (!RegisterClass(&wndclass)) {
    // Compiled with UNICODE defined, but running on Win98 where RegisterClassW
    // is not defined. Note that MessageBoxW is one of the few defined on Win98.
    MessageBox(NULL, TEXT("This program requires a newer version of Windows."),
               szAppName, MB_ICONERROR);
  }

  // Create and get a handle to the window.
  HWND hwnd = CreateWindow(szWinClassName,                // Window class name
                           TEXT("Hello Window Program"),  // Window caption
                           WS_OVERLAPPEDWINDOW,           // Window style
                           CW_USEDEFAULT,                 // Initial x POSITION
                           CW_USEDEFAULT,                 // Initial y POSITION
                           CW_USEDEFAULT,                 // Initial x SIZE
                           CW_USEDEFAULT,                 // Initial y SIZE
                           NULL,       // Parent window handle (this is parent)
                           NULL,       // Window menu handle (we have no menu)
                           hInstance,  // Program instance handle
                           NULL);      // Optional creation params

  // Show the window.
  // Specify the window handle and the how it should be shown.
  // In this case, we pass along the argument (SW_SHOWNORMAL).
  ShowWindow(hwnd, iCmdShow);

  // Force client window to be painted.
  UpdateWindow(hwnd);

  // Get mouse/keyboard (non-queued) messages from this program's message queue
  // and store in msg. Processed in orderly and synchronized manner.
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    // Pass message back to Windows to translate from virtual keys to character
    // keys.
    TranslateMessage(&msg);

    // Sends a message to the appropriate window procedure. Does not return
    // until the WinProc has returned control back to Windows (ensures
    // synchronization). Note that the WinProc may call a function that returns
    // control mid-way i.e. WM_PAINT calls UpdateWindow.
    DispatchMessage(&msg);
  }
  // The last message was a WM_QUIT message.
  return msg.wParam;
}

// Processes queued and non-queued messages. I.e. those placed on queue by
// Windows and direct calls to this function by Windows.
LRESULT CALLBACK
WndProc(HWND hwnd,        // The handle to the window receiving the message
        UINT message,     // Received message identifier
        WPARAM wParam,    // Word Params (historically 16-bit, now 32)
        LPARAM lParam) {  // Long Params (32-bit always)

  HDC hdc;
  PAINTSTRUCT ps;
  RECT rect;

  switch (message) {
    case WM_CREATE:
      // Plays a sound file. Ensure you link winmm.lib.
      // We specify the name of the file, the hInstance of the module containing
      // the sound file, and some flags. In this case, SND_FILENAME specifies
      // that the first argument is a filename, and SND_ASYNC specifies that it
      // should be played asynchronously.
      PlaySound(TEXT("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC);
      return 0;
    case WM_PAINT:
      // Initiate the beginning of a window paint. Erases background using
      // hbrBackground brush. Returns a handle to the device context.
      hdc = BeginPaint(hwnd, &ps);

      // Obtain the dimensions of the client area (i.e. where we can draw).
      GetClientRect(hwnd, &rect);

      // Displays a text string. We specify the device context, the string, the
      // count of chars (in this case, zero terminated), the rectangle area, and
      // some drawing flags. In this case, draw in a single line in the center
      // of the client area.
      DrawText(hdc, TEXT("Hello, World!"), -1, &rect,
               DT_SINGLELINE | DT_CENTER | DT_VCENTER);
      // Ends window painting.
      EndPaint(hwnd, &ps);
      return 0;
    case WM_DESTROY:
      // Inserts a quit message into the message queue.
      PostQuitMessage(0);
      return 0;
  }
  // Performs default processing of messages.
  return DefWindowProc(hwnd, message, wParam, lParam);
}
