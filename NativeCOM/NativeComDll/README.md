# TODOs
- [ ] Add ref counting test cases (Call double `Release()` and purposly forget to call `Release()` for each COM object and each COM factory, and for dll lifetime manager `DllCanUnloadNow()`)

# Debugging
Before doing **anything**, make sure that:
A. Solution Configuration is set to **Debug**.
B. NativeComDll project is set as the **startup project**.

To debug **Registration**, go to *Project* -> *Properites* -> *Debugging*:
- *Configuration*: **Debug**
- *Command*: `C:\Windows\System32\regsvr32.exe`
- *Command Arguments*: `"$(TargetPath)"`

To debug **Unregistration**, go to *Project* -> *Properites* -> *Debugging*:
- *Configuration*: **Debug**
- *Command*: `C:\Windows\System32\regsvr32.exe`
- *Command Arguments*: `/u "$(TargetPath)"`

When debugging, you may want to **view the registry** in the placed being edited by `regsvr32`.
To do so, go to this registry location by:
A. *win+r* -> `regedit`
B. Jump to this path by pasting it to the **address bar**: `Computer\HKEY_CURRENT_USER\Software\Classes\CLSID\{3233BC95-FB3D-4A97-AA10-A717C62F4AF7}`.
B. 