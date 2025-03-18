#include <windows.h>
#include <sstream>
#include "windowsx.h"  // for GET_X_LPARAM and GET_Y_LPARAM

#include <dwmapi.h> // Required for rounded corners
#pragma comment(lib, "Dwmapi.lib") // Link the library

// TODO (1): Create and Show a Window(Essential for TSF)
// TODO (2): Explore the Windows Message System
// TODO (3): Handling Basic Events(Key & Mouse Input)
// TODO (4): Understanding Window Procedures(WndProc)
// TODO (5): Working with System Hooks(More Advanced)


const DWORD ANIMATION_TYPE = AW_BLEND;  // Ref: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-animatewindow
const int ANIMATION_DURATION_IN_MS = 300;

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
            CLEARTYPE_QUALITY, FF_SWISS, L"Consolas");  // CLEARTYPE_QUALITY (as oppose to DEFAULT_QUALITY) supports advanced text rendering techniques
        
        // Enable rounded corners (Windows 11+)
        DWM_WINDOW_CORNER_PREFERENCE preference = DWMWCP_ROUNDSMALL;  // Control window rounding style
        DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &preference, sizeof(preference));

        AnimateWindow(hwnd, ANIMATION_DURATION_IN_MS, AW_BLEND);
        Sleep(ANIMATION_DURATION_IN_MS);
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    }
    case WM_NCHITTEST: {  // Ref: https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-nchittest#return-value
        LRESULT hit = DefWindowProc(hwnd, uMsg, wParam, lParam);
        // Get the cursor position relative to the window
        POINT cursor;
        cursor.x = GET_X_LPARAM(lParam);
        cursor.y = GET_Y_LPARAM(lParam);

        swprintf_s(lastMousePositionReport, L"Mouse moved to (%ld, %ld)", cursor.x, cursor.y);
        InvalidateRect(hwnd, NULL, TRUE);

        RECT windowRect;
        GetWindowRect(hwnd, &windowRect);

        const int borderThreshold = 10; // Thickness of the resize area

        bool left = cursor.x >= windowRect.left && cursor.x < windowRect.left + borderThreshold;
        bool right = cursor.x <= windowRect.right && cursor.x > windowRect.right - borderThreshold;
        bool top = cursor.y >= windowRect.top && cursor.y < windowRect.top + borderThreshold;
        bool bottom = cursor.y <= windowRect.bottom && cursor.y > windowRect.bottom - borderThreshold;

        if (top && left)    return HTTOPLEFT;
        if (top && right)   return HTTOPRIGHT;
        if (bottom && left) return HTBOTTOMLEFT;
        if (bottom && right) return HTBOTTOMRIGHT;
        if (left)   return HTLEFT;
        if (right)  return HTRIGHT;
        if (top)    return HTTOP;
        if (bottom) return HTBOTTOM;

        return HTCAPTION; // Allow dragging anywhere else
        }
    
    case WM_SIZE:
        InvalidateRect(hwnd, NULL, TRUE); // Request a redraw to keep text centered when resizing
        return 0;
    // NOTE: Borderless means I'm managing closing the window using the keyboard
    // case WM_CLOSE:  // when closed
    //     AnimateWindow(hwnd, 300, AW_BLEND | AW_HIDE); // Slide out to the left
    //     PostQuitMessage(0);
    //     return 0;


    // Keyboard Events
    case WM_KEYDOWN: { // Capture key presses
        char keyPressed = (char)wParam;
        // Press esc to quit
        if (keyPressed==VK_ESCAPE) {  // Ref: https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
            AnimateWindow(hwnd, ANIMATION_DURATION_IN_MS, AW_BLEND | AW_HIDE);
            Sleep(ANIMATION_DURATION_IN_MS);
            PostQuitMessage(0);
            return 0;
        }
        swprintf_s(lastEventReport, L"Key pressed: %c", keyPressed);
        InvalidateRect(hwnd, NULL, TRUE); // Request window redraw
        return 0;
    }
    

    // Mouse Events
    case WM_NCLBUTTONDOWN: {  // Mouse event in non client area (everything is a caption)
        POINT cursor;
        cursor.x = GET_X_LPARAM(lParam);
        cursor.y = GET_Y_LPARAM(lParam);
        swprintf_s(lastEventReport, L"Mouse clicked at (%ld, %ld)", cursor.x, cursor.y);
        InvalidateRect(hwnd, NULL, TRUE);
        return DefWindowProc(hwnd, uMsg, wParam, lParam);  // Retain default behavior
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
        HDC hdc = BeginPaint(hwnd, &ps);  // hdc = Handle to Display device Context
        
        // Text Appearance
        SelectObject(hdc, hFont); // Apply custom font
        SetTextColor(hdc, RGB(255, 255, 255)); // White text color
        SetBkMode(hdc, TRANSPARENT); // Transparent background for text

        // Center Text
        RECT rect;
        GetClientRect(hwnd, &rect); // Get window size
        // upper-left point is (0,0)
        int centerX = rect.right / 2;
        int centerY = rect.bottom / 2;
        
        SetTextAlign(hdc, TA_CENTER);

        // Text Content
        TextOut(hdc, centerX, centerY-20, lastEventReport, wcslen(lastEventReport));
        TextOut(hdc, centerX, centerY+0, lastMousePositionReport, wcslen(lastMousePositionReport));
        
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
        0, CLASS_NAME, L"My First Window", WS_POPUP, // WS_POPUP is no border, as oppose to normal WS_OVERLAPPEDWINDOW
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
