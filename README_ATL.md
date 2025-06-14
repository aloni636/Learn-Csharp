# How to develop simple ATL objects

1. Create a new project of template "ATL Project" in Visual Studio.

2. Use default settings.

3. Add a new ATL object to the project by right-clicking on the project in Solution Explorer and selecting "Add" -> "New item..." -> "ATL Simple Object". Choose a name and continue with default settings in the wizard.

4. To configure IntelliSense and register the object, build the project:

   - **To register the ATL object for all users (requires admin):**
     - Open Visual Studio in administrator mode.
     - Build the project:
       ```
       Build -> Clean Solution
       Build -> Rebuild Solution
       ```
     - **Note:** The reason registration requires admin rights by default is because the ATL class is registered at `Computer\HKEY_CLASSES_ROOT` (see `getRegistrySubKeyPath` in NativeComDll project). Setting **Per-user Redirection** allows registration under the current user **without admin**.
   - **To register per user without admin:**
     - Open Configuration Properties and set `Linker > General > Per-user Redirection` to **Yes**.
     - Build the project: 
       ```
       Build -> Clean Solution
       Build -> Rebuild Solution
       ```
   - To disable automatic registration, set `Configuration Properties > Linker > General > Register Output` to **No**.

5. To view the registered ATL COM object, locate the UUID of the ATL object in current project Source Files -> `AtlComDll.idl`. The coclass UUID is the registered UUID. Open regedit.exe (Win+R -> regedit.exe) and view the entry for the corresponding key above:

   - For **admin** registration, see: `Computer\HKEY_CLASSES_ROOT\CLSID\{coclass UUID}`. 
   - For **per-user** registration, see: `HKEY_CURRENT_USER\Software\Classes\CLSID\{coclass UUID}`.

6. To clean up the registration, run:
    ```
    regsvr32.exe /u .\x64\Debug\AtlComDll.dll
    ```

# Adding Methods
