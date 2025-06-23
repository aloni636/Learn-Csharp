

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 05:14:07 2038
 */
/* Compiler settings for AtlComDll.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0628 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __AtlComDll_i_h__
#define __AtlComDll_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IGreeter_FWD_DEFINED__
#define __IGreeter_FWD_DEFINED__
typedef interface IGreeter IGreeter;

#endif 	/* __IGreeter_FWD_DEFINED__ */


#ifndef __Greeter_FWD_DEFINED__
#define __Greeter_FWD_DEFINED__

#ifdef __cplusplus
typedef class Greeter Greeter;
#else
typedef struct Greeter Greeter;
#endif /* __cplusplus */

#endif 	/* __Greeter_FWD_DEFINED__ */


#ifndef __StringGenerator_FWD_DEFINED__
#define __StringGenerator_FWD_DEFINED__

#ifdef __cplusplus
typedef class StringGenerator StringGenerator;
#else
typedef struct StringGenerator StringGenerator;
#endif /* __cplusplus */

#endif 	/* __StringGenerator_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IGreeter_INTERFACE_DEFINED__
#define __IGreeter_INTERFACE_DEFINED__

/* interface IGreeter */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IGreeter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("95a4b435-2515-4038-86ca-017ba9b8b38f")
    IGreeter : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Greet( 
            /* [in] */ BSTR name) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGreeterVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGreeter * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGreeter * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGreeter * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGreeter * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGreeter * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGreeter * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGreeter * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        DECLSPEC_XFGVIRT(IGreeter, Greet)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Greet )( 
            IGreeter * This,
            /* [in] */ BSTR name);
        
        END_INTERFACE
    } IGreeterVtbl;

    interface IGreeter
    {
        CONST_VTBL struct IGreeterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGreeter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGreeter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGreeter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGreeter_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IGreeter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IGreeter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IGreeter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IGreeter_Greet(This,name)	\
    ( (This)->lpVtbl -> Greet(This,name) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGreeter_INTERFACE_DEFINED__ */



#ifndef __AtlComDllLib_LIBRARY_DEFINED__
#define __AtlComDllLib_LIBRARY_DEFINED__

/* library AtlComDllLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_AtlComDllLib;

EXTERN_C const CLSID CLSID_Greeter;

#ifdef __cplusplus

class DECLSPEC_UUID("7e88194a-d593-4257-9394-3790fa8c3853")
Greeter;
#endif

EXTERN_C const CLSID CLSID_StringGenerator;

#ifdef __cplusplus

class DECLSPEC_UUID("ff75d3d2-276d-4376-978d-ababb00e2ea2")
StringGenerator;
#endif
#endif /* __AtlComDllLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


