#include <windows.h>
#include <shobjidl.h>
#include <atlbase.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HRESULT hr;
	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if FAILED(hr) { return 0; }
	
	CComPtr<IFileOpenDialog> fileOpen;  // (smart) pointer to file open dialog COM interface
	hr = fileOpen.CoCreateInstance(__uuidof(FileOpenDialog));
	if FAILED(hr) { return 0; }
	
	COMDLG_FILTERSPEC fileTypes[] = {
	{ L"Text Files (*.txt)", L"*.txt" },
	{ L"C++ Source Files (*.cpp)", L"*.cpp" },
	{ L"All Files (*.*)", L"*.*" }
	};
	hr = fileOpen->SetFileTypes(_countof(fileTypes), fileTypes);
	if FAILED(hr) { return 0; }

	hr = fileOpen->SetFileTypeIndex(1);
	if FAILED(hr) { return 0; }

	hr = fileOpen->Show(NULL);
	if FAILED(hr) { return 0; }
	
	CComPtr<IShellItem> pItem;
	hr = fileOpen->GetResult(&pItem);
	if FAILED(hr) { return 0; }
	
	CComHeapPtr<WCHAR> filePath;  // Smart pointer to wide char/string, as oppose to PWSTR (pointer to wide string), Refs: https://stackoverflow.com/a/72506240, https://learn.microsoft.com/en-us/cpp/atl/memory-management-classes?view=msvc-170#:~:text=CComHeapPtr%20A%20smart,COM%20interface%20pointers.
	hr = pItem->GetDisplayName(
		SIGDN_FILESYSPATH,  // How the name should look
		&filePath  // GetDisplayName allocates memory internally using CoTaskMemAlloc (Ref: https://learn.microsoft.com/en-us/windows/win32/learnwin32/memory-allocation-in-com)
	);
	if FAILED(hr) { return 0; }
	
	MessageBoxW(NULL, filePath, L"File Path", MB_OK);
	CoUninitialize();
	return 0;
}