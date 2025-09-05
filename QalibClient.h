/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Oct 12 13:41:03 2005
 */
/* Compiler settings for C:\Qalib\_Calibration\QalibClient\QalibClient.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __QalibClient_h__
#define __QalibClient_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IQalibClientMain_FWD_DEFINED__
#define __IQalibClientMain_FWD_DEFINED__
typedef interface IQalibClientMain IQalibClientMain;
#endif 	/* __IQalibClientMain_FWD_DEFINED__ */


#ifndef __QalibClientMain_FWD_DEFINED__
#define __QalibClientMain_FWD_DEFINED__

#ifdef __cplusplus
typedef class QalibClientMain QalibClientMain;
#else
typedef struct QalibClientMain QalibClientMain;
#endif /* __cplusplus */

#endif 	/* __QalibClientMain_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IQalibClientMain_INTERFACE_DEFINED__
#define __IQalibClientMain_INTERFACE_DEFINED__

/* interface IQalibClientMain */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IQalibClientMain;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("084F9ED2-D274-4314-A61E-E3E9F90410EC")
    IQalibClientMain : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCalibrationResults( 
            /* [in] */ LONG calibrationID,
            /* [out] */ BSTR __RPC_FAR *partNumber,
            /* [out] */ BSTR __RPC_FAR *waveLength,
            /* [out] */ BSTR __RPC_FAR *species,
            /* [out] */ BSTR __RPC_FAR *diluent,
            /* [out] */ BSTR __RPC_FAR *mold,
            /* [out] */ BSTR __RPC_FAR *rotor,
            /* [out] */ BSTR __RPC_FAR *cuvette,
            /* [out] */ BSTR __RPC_FAR *mode,
            /* [out] */ BSTR __RPC_FAR *user,
            /* [out] */ BSTR __RPC_FAR *date,
            /* [out] */ VARIANT __RPC_FAR *description,
            /* [out] */ VARIANT __RPC_FAR *originalFitParameters,
            /* [out] */ VARIANT __RPC_FAR *newFitParameters,
            /* [out] */ VARIANT __RPC_FAR *minLimits,
            /* [out] */ VARIANT __RPC_FAR *maxLimits,
            /* [out] */ VARIANT __RPC_FAR *originalDisposition,
            /* [out] */ VARIANT __RPC_FAR *newDisposition,
            /* [out] */ VARIANT __RPC_FAR *calibrationData,
            /* [out] */ VARIANT __RPC_FAR *statusData,
            /* [out] */ VARIANT __RPC_FAR *rates,
            /* [out] */ VARIANT __RPC_FAR *plotData,
            /* [out] */ BSTR __RPC_FAR *comment,
            /* [retval][out] */ VARIANT __RPC_FAR *perror_msg) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendUpdatedFitParameters( 
            /* [in] */ LONG calibrationID,
            /* [in] */ VARIANT __RPC_FAR *newFitPars,
            /* [retval][out] */ VARIANT __RPC_FAR *error_msg) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEditableFitParameters( 
            /* [in] */ LONG calibrationID,
            /* [out] */ VARIANT __RPC_FAR *EditableFitParameters,
            /* [retval][out] */ VARIANT __RPC_FAR *error_msg) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendComment( 
            /* [in] */ LONG calibrationID,
            /* [in] */ BSTR __RPC_FAR *comment,
            /* [retval][out] */ VARIANT __RPC_FAR *error_msg) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetUserRights( 
            /* [in] */ BSTR user,
            /* [in] */ BSTR password,
            /* [out] */ VARIANT __RPC_FAR *modeList,
            /* [out] */ VARIANT __RPC_FAR *chemistryList,
            /* [retval][out] */ VARIANT __RPC_FAR *error_msg) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAssignedValues( 
            /* [in] */ BSTR chemistry,
            /* [in] */ const VARIANT __RPC_FAR *sampleIDsList,
            /* [out] */ VARIANT __RPC_FAR *assignedValues,
            /* [retval][out] */ VARIANT __RPC_FAR *error_msg) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendClientData( 
            /* [in] */ BSTR chemistry,
            /* [in] */ INT outlierMethod,
            /* [in] */ BSTR mode,
            /* [in] */ BSTR user,
            /* [in] */ VARIANT __RPC_FAR *sampleData,
            /* [in] */ VARIANT __RPC_FAR *serialNumberList,
            /* [in] */ VARIANT __RPC_FAR *barCode,
            /* [in] */ VARIANT __RPC_FAR *sampleSpecies,
            /* [in] */ VARIANT __RPC_FAR *sampleDataStatus,
            /* [out][in] */ LONG __RPC_FAR *calibrationID,
            /* [retval][out] */ VARIANT __RPC_FAR *error_msg) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IQalibClientMainVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IQalibClientMain __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IQalibClientMain __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IQalibClientMain __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IQalibClientMain __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IQalibClientMain __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IQalibClientMain __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IQalibClientMain __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCalibrationResults )( 
            IQalibClientMain __RPC_FAR * This,
            /* [in] */ LONG calibrationID,
            /* [out] */ BSTR __RPC_FAR *partNumber,
            /* [out] */ BSTR __RPC_FAR *waveLength,
            /* [out] */ BSTR __RPC_FAR *species,
            /* [out] */ BSTR __RPC_FAR *diluent,
            /* [out] */ BSTR __RPC_FAR *mold,
            /* [out] */ BSTR __RPC_FAR *rotor,
            /* [out] */ BSTR __RPC_FAR *cuvette,
            /* [out] */ BSTR __RPC_FAR *mode,
            /* [out] */ BSTR __RPC_FAR *user,
            /* [out] */ BSTR __RPC_FAR *date,
            /* [out] */ VARIANT __RPC_FAR *description,
            /* [out] */ VARIANT __RPC_FAR *originalFitParameters,
            /* [out] */ VARIANT __RPC_FAR *newFitParameters,
            /* [out] */ VARIANT __RPC_FAR *minLimits,
            /* [out] */ VARIANT __RPC_FAR *maxLimits,
            /* [out] */ VARIANT __RPC_FAR *originalDisposition,
            /* [out] */ VARIANT __RPC_FAR *newDisposition,
            /* [out] */ VARIANT __RPC_FAR *calibrationData,
            /* [out] */ VARIANT __RPC_FAR *statusData,
            /* [out] */ VARIANT __RPC_FAR *rates,
            /* [out] */ VARIANT __RPC_FAR *plotData,
            /* [out] */ BSTR __RPC_FAR *comment,
            /* [retval][out] */ VARIANT __RPC_FAR *perror_msg);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendUpdatedFitParameters )( 
            IQalibClientMain __RPC_FAR * This,
            /* [in] */ LONG calibrationID,
            /* [in] */ VARIANT __RPC_FAR *newFitPars,
            /* [retval][out] */ VARIANT __RPC_FAR *error_msg);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEditableFitParameters )( 
            IQalibClientMain __RPC_FAR * This,
            /* [in] */ LONG calibrationID,
            /* [out] */ VARIANT __RPC_FAR *EditableFitParameters,
            /* [retval][out] */ VARIANT __RPC_FAR *error_msg);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendComment )( 
            IQalibClientMain __RPC_FAR * This,
            /* [in] */ LONG calibrationID,
            /* [in] */ BSTR __RPC_FAR *comment,
            /* [retval][out] */ VARIANT __RPC_FAR *error_msg);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetUserRights )( 
            IQalibClientMain __RPC_FAR * This,
            /* [in] */ BSTR user,
            /* [in] */ BSTR password,
            /* [out] */ VARIANT __RPC_FAR *modeList,
            /* [out] */ VARIANT __RPC_FAR *chemistryList,
            /* [retval][out] */ VARIANT __RPC_FAR *error_msg);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAssignedValues )( 
            IQalibClientMain __RPC_FAR * This,
            /* [in] */ BSTR chemistry,
            /* [in] */ const VARIANT __RPC_FAR *sampleIDsList,
            /* [out] */ VARIANT __RPC_FAR *assignedValues,
            /* [retval][out] */ VARIANT __RPC_FAR *error_msg);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendClientData )( 
            IQalibClientMain __RPC_FAR * This,
            /* [in] */ BSTR chemistry,
            /* [in] */ INT outlierMethod,
            /* [in] */ BSTR mode,
            /* [in] */ BSTR user,
            /* [in] */ VARIANT __RPC_FAR *sampleData,
            /* [in] */ VARIANT __RPC_FAR *serialNumberList,
            /* [in] */ VARIANT __RPC_FAR *barCode,
            /* [in] */ VARIANT __RPC_FAR *sampleSpecies,
            /* [in] */ VARIANT __RPC_FAR *sampleDataStatus,
            /* [out][in] */ LONG __RPC_FAR *calibrationID,
            /* [retval][out] */ VARIANT __RPC_FAR *error_msg);
        
        END_INTERFACE
    } IQalibClientMainVtbl;

    interface IQalibClientMain
    {
        CONST_VTBL struct IQalibClientMainVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IQalibClientMain_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IQalibClientMain_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IQalibClientMain_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IQalibClientMain_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IQalibClientMain_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IQalibClientMain_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IQalibClientMain_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IQalibClientMain_GetCalibrationResults(This,calibrationID,partNumber,waveLength,species,diluent,mold,rotor,cuvette,mode,user,date,description,originalFitParameters,newFitParameters,minLimits,maxLimits,originalDisposition,newDisposition,calibrationData,statusData,rates,plotData,comment,perror_msg)	\
    (This)->lpVtbl -> GetCalibrationResults(This,calibrationID,partNumber,waveLength,species,diluent,mold,rotor,cuvette,mode,user,date,description,originalFitParameters,newFitParameters,minLimits,maxLimits,originalDisposition,newDisposition,calibrationData,statusData,rates,plotData,comment,perror_msg)

#define IQalibClientMain_SendUpdatedFitParameters(This,calibrationID,newFitPars,error_msg)	\
    (This)->lpVtbl -> SendUpdatedFitParameters(This,calibrationID,newFitPars,error_msg)

#define IQalibClientMain_GetEditableFitParameters(This,calibrationID,EditableFitParameters,error_msg)	\
    (This)->lpVtbl -> GetEditableFitParameters(This,calibrationID,EditableFitParameters,error_msg)

#define IQalibClientMain_SendComment(This,calibrationID,comment,error_msg)	\
    (This)->lpVtbl -> SendComment(This,calibrationID,comment,error_msg)

#define IQalibClientMain_GetUserRights(This,user,password,modeList,chemistryList,error_msg)	\
    (This)->lpVtbl -> GetUserRights(This,user,password,modeList,chemistryList,error_msg)

#define IQalibClientMain_GetAssignedValues(This,chemistry,sampleIDsList,assignedValues,error_msg)	\
    (This)->lpVtbl -> GetAssignedValues(This,chemistry,sampleIDsList,assignedValues,error_msg)

#define IQalibClientMain_SendClientData(This,chemistry,outlierMethod,mode,user,sampleData,serialNumberList,barCode,sampleSpecies,sampleDataStatus,calibrationID,error_msg)	\
    (This)->lpVtbl -> SendClientData(This,chemistry,outlierMethod,mode,user,sampleData,serialNumberList,barCode,sampleSpecies,sampleDataStatus,calibrationID,error_msg)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IQalibClientMain_GetCalibrationResults_Proxy( 
    IQalibClientMain __RPC_FAR * This,
    /* [in] */ LONG calibrationID,
    /* [out] */ BSTR __RPC_FAR *partNumber,
    /* [out] */ BSTR __RPC_FAR *waveLength,
    /* [out] */ BSTR __RPC_FAR *species,
    /* [out] */ BSTR __RPC_FAR *diluent,
    /* [out] */ BSTR __RPC_FAR *mold,
    /* [out] */ BSTR __RPC_FAR *rotor,
    /* [out] */ BSTR __RPC_FAR *cuvette,
    /* [out] */ BSTR __RPC_FAR *mode,
    /* [out] */ BSTR __RPC_FAR *user,
    /* [out] */ BSTR __RPC_FAR *date,
    /* [out] */ VARIANT __RPC_FAR *description,
    /* [out] */ VARIANT __RPC_FAR *originalFitParameters,
    /* [out] */ VARIANT __RPC_FAR *newFitParameters,
    /* [out] */ VARIANT __RPC_FAR *minLimits,
    /* [out] */ VARIANT __RPC_FAR *maxLimits,
    /* [out] */ VARIANT __RPC_FAR *originalDisposition,
    /* [out] */ VARIANT __RPC_FAR *newDisposition,
    /* [out] */ VARIANT __RPC_FAR *calibrationData,
    /* [out] */ VARIANT __RPC_FAR *statusData,
    /* [out] */ VARIANT __RPC_FAR *rates,
    /* [out] */ VARIANT __RPC_FAR *plotData,
    /* [out] */ BSTR __RPC_FAR *comment,
    /* [retval][out] */ VARIANT __RPC_FAR *perror_msg);


void __RPC_STUB IQalibClientMain_GetCalibrationResults_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IQalibClientMain_SendUpdatedFitParameters_Proxy( 
    IQalibClientMain __RPC_FAR * This,
    /* [in] */ LONG calibrationID,
    /* [in] */ VARIANT __RPC_FAR *newFitPars,
    /* [retval][out] */ VARIANT __RPC_FAR *error_msg);


void __RPC_STUB IQalibClientMain_SendUpdatedFitParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IQalibClientMain_GetEditableFitParameters_Proxy( 
    IQalibClientMain __RPC_FAR * This,
    /* [in] */ LONG calibrationID,
    /* [out] */ VARIANT __RPC_FAR *EditableFitParameters,
    /* [retval][out] */ VARIANT __RPC_FAR *error_msg);


void __RPC_STUB IQalibClientMain_GetEditableFitParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IQalibClientMain_SendComment_Proxy( 
    IQalibClientMain __RPC_FAR * This,
    /* [in] */ LONG calibrationID,
    /* [in] */ BSTR __RPC_FAR *comment,
    /* [retval][out] */ VARIANT __RPC_FAR *error_msg);


void __RPC_STUB IQalibClientMain_SendComment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IQalibClientMain_GetUserRights_Proxy( 
    IQalibClientMain __RPC_FAR * This,
    /* [in] */ BSTR user,
    /* [in] */ BSTR password,
    /* [out] */ VARIANT __RPC_FAR *modeList,
    /* [out] */ VARIANT __RPC_FAR *chemistryList,
    /* [retval][out] */ VARIANT __RPC_FAR *error_msg);


void __RPC_STUB IQalibClientMain_GetUserRights_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IQalibClientMain_GetAssignedValues_Proxy( 
    IQalibClientMain __RPC_FAR * This,
    /* [in] */ BSTR chemistry,
    /* [in] */ const VARIANT __RPC_FAR *sampleIDsList,
    /* [out] */ VARIANT __RPC_FAR *assignedValues,
    /* [retval][out] */ VARIANT __RPC_FAR *error_msg);


void __RPC_STUB IQalibClientMain_GetAssignedValues_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IQalibClientMain_SendClientData_Proxy( 
    IQalibClientMain __RPC_FAR * This,
    /* [in] */ BSTR chemistry,
    /* [in] */ INT outlierMethod,
    /* [in] */ BSTR mode,
    /* [in] */ BSTR user,
    /* [in] */ VARIANT __RPC_FAR *sampleData,
    /* [in] */ VARIANT __RPC_FAR *serialNumberList,
    /* [in] */ VARIANT __RPC_FAR *barCode,
    /* [in] */ VARIANT __RPC_FAR *sampleSpecies,
    /* [in] */ VARIANT __RPC_FAR *sampleDataStatus,
    /* [out][in] */ LONG __RPC_FAR *calibrationID,
    /* [retval][out] */ VARIANT __RPC_FAR *error_msg);


void __RPC_STUB IQalibClientMain_SendClientData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IQalibClientMain_INTERFACE_DEFINED__ */



#ifndef __QALIBCLIENTLib_LIBRARY_DEFINED__
#define __QALIBCLIENTLib_LIBRARY_DEFINED__

/* library QALIBCLIENTLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_QALIBCLIENTLib;

EXTERN_C const CLSID CLSID_QalibClientMain;

#ifdef __cplusplus

class DECLSPEC_UUID("F36AF9A7-D575-49C1-9BBF-C97A2A694D46")
QalibClientMain;
#endif
#endif /* __QALIBCLIENTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
