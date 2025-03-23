# Win32 API Quirks
[Ref](https://learn.microsoft.com/en-us/windows/win32/learnwin32/windows-coding-conventions)
- most functions that return a BOOL type can return any non-zero value to indicate Boolean truth
- Don't use pointer types, i.e. `{P|LP}<Object>` Instead, use explicit pointer syntax `<Object>*`
- Use macros abstracting Unicode or ANSI functions (SetWindowTextW) instead of Unicode enabled functions (SetWindowTextW) or ANSI (SetWindowTextA) alone
- ~~If you want to support both ANSI and Unicode, wrap the string in TEXT(<text>), _T(<text>) or as TCHAR.~~ Outdated, all applications should support Unicode.

# Win32 API's Hungarian Notation
- P|LP = Pointer, Long Pointer (equivalent to Pointer)
- C = Constant
- Example: LPCSTR =  Long Pointer Constant STRing
- W = Wide
- PCWSTR = Pointer Constant Wide STRing

***What is a Window?***
A. Application window: COmposed of client area and non client area like the frame (title bar, minimize, maximize etc)
B. UI controls are also windows! But they do not exit by themself, instead positioned relative to an application window.

# COM Quirks
- Releasing a COM object is always done **after we made sure** the COM object was created succesfully. Not doing so would lead to destructing an invalid object. ([Ref](https://learn.microsoft.com/en-us/windows/win32/learnwin32/managing-the-lifetime-of-an-object))
- ***Call conventions for COM methods***:
    - A function can only return **one value**, and in COM is reserved for success/failure codes. Therefore, to return a new instantiated COM object, we need to pass a reference to an object **which would be be populated** with the pointer to the new COM object. This results in double pointer to interface semantics ([Ref](https://learn.microsoft.com/en-us/windows/win32/learnwin32/creating-an-object-in-com)).
    - How double pointer to void (`void **`) comes into play (for example, in `QueryInterface()`)? COM methods which are used for every COM object must support returning a pointer to any possible COM object. So, the specific COM interface cannot be specified - this results in the `void`. The double pointer is because, again, we need the function to return a pointer to the COM object. A function can only have one return value, so the function should populate the pointer to the COM - this is a double pointer `**`.
- `QueryInterface()` is used to jump between the interfaces in a multi inheritence style COM object (i.e. object which implements 2 or more interfaces). We cannot cast the pointer, but we can ask the object to return a new pointer to it's other implementation. 
- Use `IID_PPV_ARGS` (**I**nterface **ID**entifier **P**ointer to a **P**ointer to a **V**ariable **ARG**uments) for additional type safety when required to pass the GUID of the COM interface & the pointer pointer to be populated (in `CoCreateInstance`, `QueryInterface`, or alike).
- To avoid manual reference counting, and use idiomatic C++ RAII, Microsoft provides a smart pointer over COM object pointers called `CComPtr<COM Interface>` in Active Template Library (ATL) (`#include <atlbase.h>`). ([Ref](https://learn.microsoft.com/en-us/windows/win32/learnwin32/com-coding-practices#com-smart-pointers))
- Always use SUCCEEDED and FAILED macros, and only implement your own checks for specific error signals on top of SUCCEEDED and FAILED macros. ([Ref](https://learn.microsoft.com/en-us/windows/win32/learnwin32/error-handling-in-com#:~:text=always%20test%20for%20errors%20by%20using%20the%20SUCCEEDED%20or%20FAILED%20macro))

## Abbriviations
- `HRESULT`: **H**andle **Result**
- `IID_PPV_ARGS`: **I**nterface **ID**entifier **P**ointer to a **P**ointer to a **V**ariable **ARG**uments
- `CoInitializeEx` **C**omponent **O**bject **Initialize** **Ex**tended