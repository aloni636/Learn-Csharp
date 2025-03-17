// Make sure the linker is linking against windows subsystem: Projec -> Properties -> Linker -> System -> SubSystem -> Change to "Windows (/SUBSYSTEM:WINDOWS)".
// NOTE: Process name is WinApiMinimal.exe

#include <windows.h>

// TODO (1): Create and Show a Window(Essential for TSF)
// TODO (2): Explore the Windows Message System
// TODO (3): Handling Basic Events(Key & Mouse Input)
// TODO (4): Understanding Window Procedures(WndProc)
// TODO (5): Working with System Hooks(More Advanced)

// Entry point for Windows applications
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
