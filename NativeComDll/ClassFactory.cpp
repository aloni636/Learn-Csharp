#include <windows.h>
#include <atomic>
// NOTE: Make sure it is in the same directory as the enclosing project. Mismatch can occur when moving files across projects using solution view which normally does not keep solution view and file view structure in sync
#include "MyComObject.h"
#include "ClassFactory.h"
#include <olectl.h>  // Including error codes for DllRegisterServer
#include <string>
#include <type_traits>  // For template type assertion in string_bytes_count


// Factory that creates Greeter instances
GreeterClassFactory::GreeterClassFactory() {};
GreeterClassFactory::~GreeterClassFactory() {};

// IUnknown
HRESULT STDMETHODCALLTYPE GreeterClassFactory::QueryInterface(REFIID riid, void** ppvObject) {
    if (ppvObject == nullptr) { return E_POINTER; }

    if (riid == IID_IUnknown) {
        *ppvObject = static_cast<IUnknown*>(this);
    }
    else if (riid == IID_IClassFactory) {
        *ppvObject = static_cast<IClassFactory*>(this);
    }
    else {
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }

    this->AddRef();
    return S_OK;
}

ULONG STDMETHODCALLTYPE GreeterClassFactory::AddRef() {
    return ++refCount;
}

ULONG STDMETHODCALLTYPE GreeterClassFactory::Release() {
    ULONG count = --refCount;  // storing in new variable to successfully return after delete
    if (count == 0) {
        dllReferences--;
        delete this;
    }
    return count;
}

// IClassFactory Ref: https://learn.microsoft.com/en-us/windows/win32/com/implementing-iclassfactory
HRESULT STDMETHODCALLTYPE GreeterClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppvObject) {
    if (pUnkOuter != NULL) { return CLASS_E_NOAGGREGATION; }

    Greeter* newGreeter = new Greeter();  // new keyword returns a pointer to the allocated object, with C style manual memory management semantics (as oppose to C++ style which is RAII semantics)
    HRESULT hr = newGreeter->QueryInterface(IID_IGreeter, ppvObject);

    // Why not return hr directly? because QueryInterface can return E_POINTER, which is not expected for CreateInstance
    if (FAILED(hr)) {
        return E_NOINTERFACE;
    }
    dllReferences++;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE GreeterClassFactory::LockServer(BOOL) {
    return E_FAIL;  // Not implemented; TODO: implement dll/exe load and code this method
}

// +---------------------------------------------------------------------------------------------------------------------------- +
// | Function            | In your DLL ?                | When it�s used                                                         |
// | DllGetClassObject   | Yes                          | COM calls this to get your factory when someone calls CoCreateInstance |
// | DllCanUnloadNow     | Yes                          | COM calls this to decide whether your DLL can be unloaded              |
// | DllRegisterServer   | Optional but recommended     | regsvr32 calls this to write CLSIDs into registry                      |
// | DllUnregisterServer | Optional                     | regsvr32 / u calls this to clean up                                    |
// | CoInitialize        | In the client                | Called by the client before any COM calls                              |
// | CoCreateInstance    | In the client                | Used to request an object from your DLL                                |
// +---------------------------------------------------------------------------------------------------------------------------- +

// Exported function for CoCreateInstance
// Ref: https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-dllgetclassobject
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID clsid, REFIID riid, LPVOID* ppv) {
    // TODO: Add clsid to the mix 
    GreeterClassFactory* factory = new GreeterClassFactory();
    HRESULT hr = factory->QueryInterface(riid, ppv);
    if (FAILED(hr)) {
        delete factory;
        // *ppv = NULL;  // No need to set *ppv to nullptr on fail because QueryInterface already does it for us
        return CLASS_E_CLASSNOTAVAILABLE;
    }
    else {
        dllReferences++;
        return S_OK;
    }
};

// Ref: https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-dllcanunloadnow
HRESULT STDMETHODCALLTYPE DllCanUnloadNow() {
    if (dllReferences == 0) {
        return S_OK;
    }
    return S_FALSE;
}

// NOTE: Including null byte
/**
* @brief Calculates the total size in bytes of a given string (including null terminator).
* @tparam T Can be std::string or std::wstring
**/
template <typename T>
DWORD string_bytes_count(T string_input) {
    return (string_input.length() + 1) * sizeof(decltype(string_input)::value_type);
}

// +-------------------+-----------------------------------------------------+
// | Function          | Purpose                                             |
// +-------------------+-----------------------------------------------------+
// | RegCreateKeyEx    | Open or create a registry key                       |
// | RegSetValueEx     | Set a named value inside a key                      |
// | RegCloseKey       | Close the key handle (always required)              |
// | StringFromCLSID   | Converts CLSID to string format for use as key name |
// | GetModuleFileName | Get path to your DLL for InprocServer32 value       |
// +-------------------+-----------------------------------------------------+
HRESULT STDMETHODCALLTYPE DllRegisterServer() {
    HRESULT hr;  // Result for windows operations in this function

    // HKEY_CLASSES_ROOT\CLSID\{clsid}\InprocServer32
    LPOLESTR clsidAsString; // Long Pointer to an OLE String
    hr = StringFromCLSID(CLSID_Greeter, &clsidAsString);
    if (FAILED(hr)) {
        return SELFREG_E_CLASS;
    }
    std::wstring registrySubKeyPath = (L"CLSID\\" + std::wstring(clsidAsString) + L"\\InprocServer32");
    // "The caller is responsible for freeing the memory allocated for the string by calling the CoTaskMemFree function." - Ref: https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-stringfromclsid
    CoTaskMemFree(clsidAsString);


    wchar_t currentModulePathBuffer[MAX_PATH];
    DWORD modulePathLength = GetModuleFileName(
        NULL,  // Retrieves the path of the executable file of the current process
        currentModulePathBuffer,
        MAX_PATH
    );
    DWORD lastError = GetLastError();
    if (modulePathLength == 0 or (modulePathLength == MAX_PATH and lastError==ERROR_INSUFFICIENT_BUFFER)) {  // Or get last error code which will be ERROR_INSUFFICIENT_BUFFER
        return SELFREG_E_CLASS;
    }
    std::wstring currentModulePath(currentModulePathBuffer);
    
    HKEY registryKeyHandle;
    DWORD keyExists;
    
    // Registry Key base
    hr = RegCreateKeyExW(  // Ref: https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regcreatekeyexa
        HKEY_CLASSES_ROOT,  // https://learn.microsoft.com/en-us/windows/win32/sysinfo/predefined-keys
        registrySubKeyPath.c_str(),
        0,
        NULL,  // Q: Should I have a class type for this?
        REG_OPTION_NON_VOLATILE,  // Q: Is it the correct REG_OPTION?
        NULL,  // Q: What's the appropriate security descriptor?
        NULL,  // Q: Relevant?
        &registryKeyHandle,
        &keyExists  // REG_CREATED_NEW_KEY | REG_OPENED_EXISTING_KEY
    );
    if (FAILED(hr)) {
        return SELFREG_E_CLASS;
    }
    if (keyExists == REG_CREATED_NEW_KEY) {
        std::string CLSID_TITLE = "Greeter Class";  // Automatically null terminated
        RegSetValueExW(
            registryKeyHandle,
            NULL,  // Set to (default)
            0,
            REG_SZ,  // Q: Is it the correct registry type
            (const BYTE*)CLSID_TITLE.c_str(),
            string_bytes_count(CLSID_TITLE)
        );
    }
    RegCloseKey(registryKeyHandle);  // Closing hKey resource no matter if it exists or not

    // ============================== //

    // Registry key InprocServer32 Subkey
    hr = RegCreateKeyExW(  // Ref: https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regcreatekeyexa
        HKEY_CLASSES_ROOT,  // https://learn.microsoft.com/en-us/windows/win32/sysinfo/predefined-keys
        (registrySubKeyPath + L"\\InprocServer32").c_str(),
        0,
        NULL,  // Q: Should I have a class type for this?
        REG_OPTION_NON_VOLATILE,  // Q: Is it the correct REG_OPTION?
        NULL,  // Q: What's the appropriate security descriptor?
        NULL,  // Q: Relevant?
        &registryKeyHandle,
        &keyExists  // REG_CREATED_NEW_KEY | REG_OPENED_EXISTING_KEY
    );
    if (FAILED(hr)) {
        return SELFREG_E_CLASS;
    }
    if (keyExists == REG_CREATED_NEW_KEY) {
        RegSetValueExW(
            registryKeyHandle,
            NULL,  // Set to (default)
            0,
            REG_SZ,  // Q: Is it the correct registry type
            (const BYTE*)currentModulePath.c_str(),  // Q: Is casting to const BYTE* correct?
            string_bytes_count(currentModulePath)
        );
        std::wstring THREADING_MODEL = L"Apartment";  // Can use const wchar_t* to avoid memory allocation
        RegSetValueExW(
            registryKeyHandle,
            L"ThreadingModel",  // Set to (default)
            0,
            REG_SZ,  // Q: Is it the correct registry type
            (const BYTE*)THREADING_MODEL.c_str(),  // Q: Is casting to const BYTE* correct?
            string_bytes_count(THREADING_MODEL)
        );
    }
    RegCloseKey(registryKeyHandle);

    return S_OK;  // Q: I assume if the key is already created it means that I already registered the server, and it's ok. Is it correct?

    // Return Values:
    // S_OK: The registry entries were created successfully.
    // SELFREG_E_TYPELIB: The server was unable to complete the registration of all the type libraries used by its classes.
    // SELFREG_E_CLASS: The server was unable to complete the registration of all the object classes.
};

HRESULT STDMETHODCALLTYPE DllUnregisterServer();











// CoRegisterClassObject  // Ref: https://learn.microsoft.com/en-us/windows/win32/api/unknwn/nf-unknwn-iclassfactory-createinstance#:~:text=the%20CLSID%20must%20be%20registered%20in%20the%20system%20registry%20with%20the%20CoRegisterClassObject%20function