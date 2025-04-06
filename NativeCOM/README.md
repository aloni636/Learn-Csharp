# Native COM
A playground to **fully understand COM** by implementing and registering a COM server which creates custom COM objects.

## Debug Instructions 
You can find debug instructions for `NativeComDLL` and `NativeComClient` individually.

## Build Instructions

A. Register the COM objects in `NativeComDll` using `regsvr32.exe .\x64\Debug\NativeComDll.dll`
B. Set `NativeComClient` as the **startup project**.
B. Press *f5* for debugging or *ctrl+f5* to run without a debugger.
