#include <windows.h>
#include <sstream>

// TODO (1): Create and Show a Window(Essential for TSF)
// TODO (2): Explore the Windows Message System
// TODO (3): Handling Basic Events(Key & Mouse Input)
// TODO (4): Understanding Window Procedures(WndProc)
// TODO (5): Working with System Hooks(More Advanced)

std::wstring logString;
// Window Procedure: Handles messages sent to the window
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CLOSE:
        PostQuitMessage(0); // Signal to close the app
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_KEYDOWN:
    {
        char key = (char)wParam; // Get the key that was pressed
        logString = (L"Key Pressed: " + (wchar_t)key);
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    }
    case WM_SIZE:
        logString = L"Window resized";
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    case WM_LBUTTONDOWN:
        logString = L"Mouse clicked";
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    case WM_PAINT: { // Redraw the window and display text
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        TextOut(hdc, 20, 50, logString.c_str(), (int)logString.length());
        EndPaint(hwnd, &ps);
        return 0;
    }

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);  // Handle signals using default Windows behavior
    }
}

// Entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"SampleWindowClass";

    // Define the window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;  // Event handler function
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, L"My First Window", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 300,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) return 0;

    ShowWindow(hwnd, nCmdShow);

    // Message Loop - Keeps the app running
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
