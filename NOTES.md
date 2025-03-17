Win32 API Quirks:
Ref: https://learn.microsoft.com/en-us/windows/win32/learnwin32/windows-coding-conventions
- most functions that return a BOOL type can return any non-zero value to indicate Boolean truth
- Don't use pointer types, i.e. `{P|LP}<Object>` Instead, use explicit pointer syntax `<Object>*`
- Use macros abstracting Unicode or ANSI functions (SetWindowTextW) instead of Unicode enabled functions (SetWindowTextW) or ANSI (SetWindowTextA) alone
- ~~If you want to support both ANSI and Unicode, wrap the string in TEXT(<text>), _T(<text>) or as TCHAR.~~ Outdated, all applications should support Unicode.

Win32 API's Hungarian Notation:
P|LP = Pointer, Long Pointer (equivalent to Pointer)
C = Constant
Example: LPCSTR =  Long Pointer Constant STRing
W = Wide
PCWSTR = Pointer Constant Wide STRing

What is a Window?
A. Application window: COmposed of client area and non client area like the frame (title bar, minimize, maximize etc)
B. UI controls are also windows! But they do not exit by themself, instead positioned relative to an application window.
