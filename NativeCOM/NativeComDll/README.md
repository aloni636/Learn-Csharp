# TODOs
- [] Add ref counting test cases (Call double `Release()` and purposly forget to call `Release()` for each COM object and each COM factory, and for dll lifetime manager `DllCanUnloadNow()`)

# Debugging
*Note*: Make sure that:
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
