#include <windows.h>
#include <sstream>
#include "windowsx.h"  // for GET_X_LPARAM and GET_Y_LPARAM
// TODO (1): Create and Show a Window(Essential for TSF)
// TODO (2): Explore the Windows Message System
// TODO (3): Handling Basic Events(Key & Mouse Input)
// TODO (4): Understanding Window Procedures(WndProc)
// TODO (5): Working with System Hooks(More Advanced)


HFONT hFont;

wchar_t lastEventReport[50] = L"Waiting for events...";  // Store the last non realtime event
wchar_t lastMousePositionReport[50] = L"[...]";  // 

// Window Procedure: Handles messages sent to the window
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    // Window Lifetime Events
    case WM_CREATE: {  // when created
        hFont = CreateFont(18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY, FF_SWISS, L"Consolas");
        return 0;
    }
    case WM_CLOSE:  // when closed
        PostQuitMessage(0);
        return 0;

    // Keyboard Events
    case WM_KEYDOWN: { // Capture key presses
        swprintf_s(lastEventReport, L"Key pressed: %c", (char)wParam);
        InvalidateRect(hwnd, NULL, TRUE); // Request window redraw
        return 0;
    }
    
    // Mouse Events
    case WM_LBUTTONDOWN: {
        POINT pt;
        pt.x = GET_X_LPARAM(lParam);
        pt.y = GET_Y_LPARAM(lParam);
        swprintf_s(lastEventReport, L"Mouse clicked at (%ld, %ld)", pt.x, pt.y);
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    };  
    case WM_MOUSEMOVE: {
        POINT pt;
        pt.x = GET_X_LPARAM(lParam);
        pt.y = GET_Y_LPARAM(lParam);
        swprintf_s(lastMousePositionReport, L"Mouse moved to (%ld, %ld)", pt.x, pt.y);
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    }

    // Painting Events
    case WM_PAINT: { // Redraw the window and display text
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        
        // Text Appearance
        SelectObject(hdc, hFont); // Apply custom font
        SetTextColor(hdc, RGB(255, 255, 255)); // White text color
        SetBkMode(hdc, TRANSPARENT); // Transparent background for text

        // Text Content
        TextOut(hdc, 20, 20, lastEventReport, wcslen(lastEventReport));
        TextOut(hdc, 20, 40, lastMousePositionReport, wcslen(lastMousePositionReport));
        
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_ERASEBKGND: { // Custom background color
        HDC hdc = (HDC)wParam;
        RECT rect;
        GetClientRect(hwnd, &rect);
        HBRUSH brush = CreateSolidBrush(RGB(50, 50, 50)); // Dark gray background
        FillRect(hdc, &rect, brush);
        DeleteObject(brush);
        return 1; // Prevent default background erasing
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
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
