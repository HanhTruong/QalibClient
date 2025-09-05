// QalibClientMain.h: Definition of the QalibClientMain class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QALIBCLIENTMAIN_H__ACEA6AF3_9828_4A65_86F9_06DDA5988E76__INCLUDED_)
#define AFX_QALIBCLIENTMAIN_H__ACEA6AF3_9828_4A65_86F9_06DDA5988E76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"       // main symbols

// Include support for IQalibServer interface.
#include "../QalibServer/QalibServer_i.c"

/////////////////////////////////////////////////////////////////////////////
// QalibClientMain

class QalibClientMain : 
	public IDispatchImpl<IQalibClientMain, &IID_IQalibClientMain, &LIBID_QALIBCLIENTLib>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<QalibClientMain,&CLSID_QalibClientMain>
{
public:
	QalibClientMain() {}
BEGIN_COM_MAP(QalibClientMain)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IQalibClientMain)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(QalibClientMain) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_REGISTRY_RESOURCEID(IDR_QalibClientMain)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IQalibClientMain
public:
	STDMETHOD(SendClientData)(/*[in]*/ BSTR chemistry, /*[in]*/ INT outlierMethod, /*[in]*/ BSTR mode, /*[in]*/ BSTR user, /*[in]*/ VARIANT *sampleData, /*[in]*/ VARIANT *serialNumberList, /*[in]*/ VARIANT *barCode, /*[in]*/ VARIANT *sampleSpecies, /*[in]*/ VARIANT *sampleDataStatus, /*[in,out]*/ LONG *calibrationID, /*[out,retval]*/ VARIANT *error_msg);
	STDMETHOD(GetAssignedValues)(/*[in]*/ BSTR chemistry, /*[in]*/ const VARIANT *sampleIDsList, /*[out]*/ VARIANT *assignedValues, /*[out,retval]*/ VARIANT *error_msg);
	STDMETHOD(GetUserRights)(/*[in]*/ BSTR user,/*[in]*/ BSTR password,/*[out]*/ VARIANT *modeList,/*[out]*/ VARIANT *chemistryList,/*[out,retval]*/ VARIANT *error_msg);
	STDMETHOD(SendComment)(/*[in]*/ LONG calibrationID, /*[in]*/ BSTR *comment, /*[out,retval]*/ VARIANT *error_msg);
	STDMETHOD(GetEditableFitParameters)(/*[in]*/ LONG calibrationID, /*[out]*/ VARIANT *EditableFitParameters, /*[out,retval]*/ VARIANT *error_msg);
	STDMETHOD(SendUpdatedFitParameters)(/*[in]*/ LONG calibrationID, /*[in]*/ VARIANT *newFitPars, /*[out,retval]*/ VARIANT *error_msg);
	STDMETHOD(GetCalibrationResults)(/*[in]*/ LONG calibrationID,/*[out]*/ BSTR *partNumber,/*[out]*/ BSTR *waveLength,/*[out]*/ BSTR *species,/*[out]*/ BSTR *diluent,/*[out]*/ BSTR *mold,/*[out]*/ BSTR *rotor,/*[out]*/ BSTR *cuvette,/*[out]*/ BSTR *mode,/*[out]*/ BSTR *user,/*[out]*/ BSTR *date,/*[out]*/ VARIANT *description,/*[out]*/ VARIANT *originalFitParameters,/*[out]*/ VARIANT *newFitParameters,/*[out]*/ VARIANT *minLimits,/*[out]*/ VARIANT *maxLimits,/*[out]*/ VARIANT *originalDisposition,/*[out]*/ VARIANT *newDisposition,/*[out]*/ VARIANT *calibrationData,/*[out]*/ VARIANT *statusData,/*[out]*/ VARIANT *rates,/*[out]*/ VARIANT *plotData,/*[out]*/ BSTR *comment,/*[out,retval]*/ VARIANT *perror_msg);
};

#endif // !defined(AFX_QALIBCLIENTMAIN_H__ACEA6AF3_9828_4A65_86F9_06DDA5988E76__INCLUDED_)
