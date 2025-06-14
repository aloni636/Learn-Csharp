// dllmain.h : Declaration of module class.

class CAtlComDllModule : public ATL::CAtlDllModuleT< CAtlComDllModule >
{
public :
	DECLARE_LIBID(LIBID_AtlComDllLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLCOMDLL, "{f5eb3f19-113a-4265-93d5-83cab932c7b5}")
};

extern class CAtlComDllModule _AtlModule;
