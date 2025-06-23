// StringGenerator.h : Declaration of the CStringGenerator

#pragma once
#include "resource.h"       // main symbols

#include "AtlComDll_i.h"

#include <fstream>
#include <string>
#include <filesystem>
#include <iostream>
#include <random>

namespace fs = std::filesystem;



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CStringGenerator

class ATL_NO_VTABLE CStringGenerator :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStringGenerator, &CLSID_StringGenerator>,
	public IEnumString
{
private:
    const std::wstring WORDS_FILE_NAME = L"google-10000-english-no-swears.txt";
    fs::path words_path;
	fs::path get_words_path() 
	{
        if (!words_path.empty()) { return words_path; }
		wchar_t module_path_buffer[MAX_PATH] = {};
		DWORD path_length= GetModuleFileNameW(_AtlBaseModule.GetModuleInstance(), module_path_buffer, _countof(module_path_buffer));
        fs::path module_path(std::wstring(module_path_buffer, path_length));
		words_path = module_path.parent_path() / L"Data" / WORDS_FILE_NAME;
		return words_path;
	}

	std::vector<std::wstring> words;
	bool load_words()
	{
		fs::path path = get_words_path();
        std::wifstream file(path);
		if (!file.is_open()) { return false; }
		std::wstring line;
		while (std::getline(file, line)) {
			words.push_back(line);
		}
		return true;
	}

	int get_random_index() const
	{
		if (words.empty()) { return -1; }
		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, words.size() - 1);
		return dis(gen);
    }

	size_t current_index = 0;

public:
	CStringGenerator()
	{
	}

DECLARE_REGISTRY_RESOURCEID(107)

DECLARE_NOT_AGGREGATABLE(CStringGenerator)

BEGIN_COM_MAP(CStringGenerator)
	COM_INTERFACE_ENTRY(IEnumString)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

    // This function is called after the object is created, but before it is used.
	// Recommended for initialization tasks because it can, unlike the constructor, return a value (an HRESULT).
	HRESULT FinalConstruct()
	{
		std::cout << "[ATL]: Loading words... ";
        bool success = load_words();
        if (!success) {
            std::cerr << "Failed to load words from " << get_words_path() << std::endl;
            return E_FAIL;
        }
		std::cout << "Loaded " << words.size() << " words." << std::endl;
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



	HRESULT Clone(IEnumString** ppenum);
	HRESULT Next(ULONG celt, LPOLESTR* rgelt, ULONG* pceltFetched);
	HRESULT Reset();
	HRESULT Skip(ULONG celt);
};

OBJECT_ENTRY_AUTO(__uuidof(StringGenerator), CStringGenerator)

HRESULT CStringGenerator::Clone(IEnumString** ppenum)
{
	// TODO: Add your implementation code here.
	return E_NOTIMPL;
}

HRESULT CStringGenerator::Next(ULONG celt, LPOLESTR* rgelt, ULONG* pceltFetched)
{
	// TODO: Add your implementation code here.
	return E_NOTIMPL;
}

HRESULT CStringGenerator::Reset()
{
	// TODO: Add your implementation code here.
	return E_NOTIMPL;
}

HRESULT CStringGenerator::Skip(ULONG celt)
{
	// TODO: Add your implementation code here.
	return E_NOTIMPL;
}
