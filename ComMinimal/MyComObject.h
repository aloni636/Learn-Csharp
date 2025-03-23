//#pragma once
//#include <windows.h>
//#include <unknwn.h> // Includes IUnknown
//
//// Define a custom interface
//interface IMyComInterface : public IUnknown {
//    virtual HRESULT STDMETHODCALLTYPE SayHello() = 0;
//};
//
//// Unique identifier (GUID) for our COM class
//// {8F5722A1-1234-4F10-9876-56D88E6ABCD0}
//static const GUID CLSID_MyComObject =
//{ 0x8f5722a1, 0x1234, 0x4f10, { 0x98, 0x76, 0x56, 0xd8, 0x8e, 0x6a, 0xbc, 0xd0 } };
//
//// Unique identifier (GUID) for our interface
//// {3FA4AC20-5678-4D4A-BBC6-09876FE4CDEF}
//static const GUID IID_IMyComInterface =
//{ 0x3fa4ac20, 0x5678, 0x4d4a, { 0xbb, 0xc6, 0x09, 0x87, 0x6f, 0xe4, 0xcd, 0xef } };