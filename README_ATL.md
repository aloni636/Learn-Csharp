# Developing Simple ATL Objects in Visual Studio

## Creating and Registering an ATL Object

1. Create a new project using the "ATL Project" template in Visual Studio.
2. Use default settings.
3. Add a new ATL object by right-clicking the project in Solution Explorer and selecting **Add -> New Item... -> ATL Simple Object**. Choose a name and continue with the default wizard options.
4. To configure IntelliSense and register the object, build the project:
   - **To register the ATL object for all users (requires admin):**
     - Open Visual Studio in administrator mode.
     - Build the project:
       ```
       Build -> Clean Solution
       Build -> Rebuild Solution
       ```
     - **Note:** Registration requires admin rights because the ATL class is written to `Computer\HKEY_CLASSES_ROOT` (see `getRegistrySubKeyPath` in the NativeComDll project). Setting **Per-user Redirection** enables registration under the current user **without admin** rights.
   - **To register per user (no admin required):**
     - Open Configuration Properties and set `Linker > General > Per-user Redirection` to **Yes**.
     - Build the project:
       ```
       Build -> Clean Solution
       Build -> Rebuild Solution
       ```
   - To disable automatic registration, set `Configuration Properties > Linker > General > Register Output` to **No**.
5. To view the registered ATL COM object:
   - Locate the UUID of the ATL object in your project under **Source Files -> AtlComDll.idl**. The coclass UUID is the registered identifier.
   - Open **regedit.exe** (Win+R -> regedit.exe) and navigate to:
     - **System-wide:** `Computer\HKEY_CLASSES_ROOT\CLSID\{coclass UUID}`
     - **Per-user:** `HKEY_CURRENT_USER\Software\Classes\CLSID\{coclass UUID}`
6. To clean up the registration, run:
   ```
   regsvr32.exe /u .\x64\Debug\AtlComDll.dll
   ```

## Adding Methods

1. Open **View -> Class View**.
2. Locate the `IGreeter` interface under the **AtlComDll** project.
3. Right-click and select **Add -> Add Method...**
4. Specify the method name and arguments.
5. Open `Greeter.cpp` and implement the method.
6. Build the project.

## Using the COM Object from a C++ Consumer

To use the object, import it into your C++ consumer project with the `#import` directive:

```cpp
#import "libid:{coclass UUID}" \
        named_guids \
        raw_interfaces_only \
        no_namespace
```

Internally, this directive locates the object's dll from the registry:

- **System-wide:** `HKEY_CLASSES_ROOT\TypeLib\{F5EB3F19-113A-4265-93D5-83CAB932C7B5}`
- **Per-user:** `HKEY_CURRENT_USER\Software\Classes\TypeLib\{F5EB3F19-113A-4265-93D5-83CAB932C7B5}`

Once the compiler finds the appropriate DLL file for the supported platform (Win32, x64, etc.), it reads the embedded type information from it or the associated `.tlb` file (type library) which is used to declare the available COM objects and interfaces.

