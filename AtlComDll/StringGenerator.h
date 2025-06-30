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
    public IEnumString  // IEnumString is the interface being implemented here
{
private:
	const fs::path WORDS_FILE_PATH{ "resources/google-10000-english-no-swears.txt" };
	
	// buffered words from words file
	std::vector<std::wstring> words_;
	// rng items
	std::mt19937::result_type seed_{ std::random_device{}() };
	std::mt19937 rng_{ seed_ };
	std::uniform_int_distribution<> dist_;


	[[nodiscard]] bool init() {
		// resolve path of words list file
		/*
		wchar_t module_path_buffer[MAX_PATH] = {};
		DWORD path_length = GetModuleFileNameW(
			_AtlBaseModule.GetModuleInstance(),
			module_path_buffer, _countof(module_path_buffer));
		fs::path module_path(std::wstring(module_path_buffer, path_length));
		fs::path words_path = module_path.parent_path() / WORDS_FILE_PATH;
		*/
		fs::path words_path = fs::path(__FILE__).parent_path() / WORDS_FILE_PATH;
		if (!fs::exists(words_path)) {
			std::cout << "[ATL]: Couldn't find words file in \"" << words_path.generic_string() << "\"" << std::endl;
			return false;
		}
		std::cout << "[ATL]: Located words file in \"" << words_path.generic_string() << "\"" << std::endl;

		// populate memory with words from words list file
		std::wifstream file(words_path);
		if (!file.is_open()) { return false; }
		std::wstring line;
		while (std::getline(file, line)) {
			words_.push_back(line);
		}
		std::cout << "[ATL]: Buffered " << words_.size() << " words into memory" << std::endl;

		// initialize distribution based on number of words
		dist_ = std::uniform_int_distribution<>(0, words_.size() - 1);
	}

	void increment(ULONG n) { rng_.discard(n); }
	std::wstring generate()
	{
		return words_[dist_(rng_)];
    }

public:
	CStringGenerator()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(107)
	DECLARE_NOT_AGGREGATABLE(CStringGenerator)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CStringGenerator)
		COM_INTERFACE_ENTRY(IEnumString)
	END_COM_MAP()

	HRESULT FinalConstruct()
	{
		std::wcout << L"[ATL]: Running FinalConstruct in CStringGenerator" << std::endl;

		// This function is called after the object is created, but before it is used.
		// Recommended for initialization tasks because it can, unlike the constructor, return a value (an HRESULT).
		bool init_success = init();
		if (init_success) { return S_OK; }
		return E_FAIL;
	}

	void FinalRelease()
	{
	}

	// IEnumString
	STDMETHOD(Next)(
		ULONG celt, /* number of items to fetch */
		LPOLESTR* rgelt, /* allocated array with the appropriate number of items to fetch*/
		ULONG* pceltFetched /* number of items fetched by Next method */ )
	{
		if (!rgelt) return E_POINTER;
		if (celt == 0) return S_FALSE;
		if (pceltFetched) *pceltFetched = 0;

		for (ULONG i = 0; i < celt; ++i)
		{
			std::wstring s = generate();
			size_t bytes = (s.size() + 1) * sizeof(wchar_t);
			rgelt[i] = static_cast<LPOLESTR>(::CoTaskMemAlloc(bytes));
			if (!rgelt[i]) return E_OUTOFMEMORY;
			memcpy_s(rgelt[i], bytes, s.c_str(), bytes);
			if (pceltFetched) ++*pceltFetched;
		}
		// we *never* run out – always S_OK
		return S_OK;
	}

	STDMETHOD(Skip)(ULONG celt) 
	{ 
		increment(celt);
		return S_OK; 
	}
	STDMETHOD(Reset)(void) { rng_.seed(seed_); return S_OK; }
	STDMETHOD(Clone)(IEnumString** ppenum) 
	{
		if (!ppenum)
			return E_POINTER;
		*ppenum = nullptr;

		// make a fresh ATL object (refcount starts at 0)
		CComObject<CStringGenerator>* pClone = nullptr;
		HRESULT hr = CComObject<CStringGenerator>::CreateInstance(&pClone);
		if (FAILED(hr))
			return hr;

		pClone->rng_ = this->rng_;
		pClone->seed_ = this->seed_;
		//pClone->words_ = this->words_; // = operator between 2 vectors results in deep copy
		pClone->dist_ = this->dist_;

		// hand it out to ppenum via QueryInterface
		pClone->AddRef(); // AddRef so QI’s AddRef/Release balance correctly
		hr = pClone->QueryInterface(__uuidof(IEnumString),reinterpret_cast<void**>(ppenum));
		pClone->Release(); // drop the extra ref from AddRef (QI already bumped it)

		return hr;
	}
};

OBJECT_ENTRY_AUTO(__uuidof(StringGenerator), CStringGenerator)
