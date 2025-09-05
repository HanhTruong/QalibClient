/*******************************************************************

FILENAME:	QalibClientMain.cpp

--------------------------------------------------------------------
MODULE DESCRIPTION:
	Implementation of QalibClientMain, contains functions called
	from client.

--------------------------------------------------------------------
GLOBAL FUNCTIONS:

--------------------------------------------------------------------
COMPILER: Visual C++ 6.0	INVOCATION: Build ->Compile	QalibClientMain.cpp

--------------------------------------------------------------------
$HISTORY: $

*******************************************************************/
// QalibClientMain.cpp : Implementation of CQalibClientApp and DLL registration.

#include "stdafx.h"
#include "QalibClient.h"
#include "QalibClientMain.h"
#include <oledb.h>

#include "Loging.h"
#include "Security.h"

// Include support for the IQalibServer interface.
#include "..\QalibServer\QalibServer.h"

/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP QalibClientMain::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IQalibClientMain,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/*****************************************************************
SendClientData(
			BSTR partNumber, 
			int outlierMethod, 
			BSTR wavelength, 
			BSTR species, 
			BSTR diluent, 
			BSTR mold, 
			BSTR rotor, 
			BSTR cuvette, 
			BSTR mode, 
			VARIANT *sampleData, 
			VARIANT *sampleDataStatus, 
			BSTR *calibrationDate, 
			VARIANT *error_msg)
					
- Sends current calibration data from client to server.

INPUT
	partNumber - Current chemistry's part number.
	outlierMethod - Method to compute outliers.
	wavelength - Wavelength for current chemistry.
	species - Current calibration species .
	diluent - Diluent used in current calibration.
	mold - Mold of current calibration.
	rotor - Rotor being used.
	cuvette - Cuvette of chemistry being calibrated.
	mode - Calibration mode.
	sampleData - Data for calibration.
	sampleDataStatus - Status of current values.
	calibrationDate - Date of current chemistry.
	error_msg - Status of current process.

OUTPUT
	Current data sent to server.
	calibrationDate with current calibration date.
	eror_msg with status of system.

LOCAL
	hr		  - Handle returned from safearray object.
	m_pDoTest - Interface Pointer
	mqi		  - Interface we want to query.
	pSInfo	  - Server information.
	buf[80]	  - Buffer to set error messages.

FUNCTION CALLED
    CoInitialize - Initialize the COM environment.
    CoUninitialize - Uninitialize the COM environment.
    CoCreateInstanceEx - Create an instance of the object.
    m_pDoTest->ReceiveT4Data - Send current data set to the server.

*****************************************************************/
STDMETHODIMP QalibClientMain::SendClientData(
				BSTR chemistry, 
				INT outlierMethod, 
				BSTR mode, 
				BSTR user, 
				VARIANT *sampleData, 
				VARIANT *serialNumberList, 
				VARIANT *barCode, 
				VARIANT *sampleSpecies, 
				VARIANT *sampleDataStatus, 
				LONG *calibrationID, 
				VARIANT *error_msg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

    IQalibServerMain*	m_pDoTest;  // Interface Pointer
	HRESULT				hr;         // Query Result.

	MULTI_QI			mqi;        // Interface we want to query.
	COAUTHIDENTITY		authIdentity;
	COAUTHINFO			authInfo;
	COSERVERINFO		serverInfo;
	
	HRESULT				hrEM;
	CString				error_source = "SendClientData";
	CString				severity;
	CString				error_description;

    // Initialize the interface pointer.
    m_pDoTest = NULL;

    // Initialize the COM environment.
    CoInitialize(NULL);

	// Initialize user's permissions.
	// User that is allowed to create objects in the server.
	hr = InitializeCOMUser(&authIdentity,
						   &authInfo,
						   &serverInfo,
						   &mqi,
						   error_msg);
    if (FAILED(hr))
	{
		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_EMPTY)
		{
			severity = "3";
			error_description ="Login failed.";
			hrEM = ErrorMessage(hr, error_source, severity, 
					 error_description, error_msg);
		}

		return S_OK;
	}

    // Create an instance of the object.
    hr = CoCreateInstanceEx(CLSID_QalibServerMain,
                            NULL, 
                            CLSCTX_ALL,
                            &serverInfo,
                            1, 
                            &mqi);
 
	// If the creation failed, exit.
    if (FAILED(hr))
	{
		// The class isn't registered.
        if (hr == REGDB_E_CLASSNOTREG)
		{
			severity = "3";
			error_description ="The class isn't registered on the server.";
        }
		else if (hr == E_INVALIDARG)	// One or more of the arguments was invalid.
		{
			severity = "3";
			error_description ="One or more of the arguments were invalid.";
		}
		else if (hr == E_NOINTERFACE)	// None of the requested interfaces are available.
		{
			severity = "3";
			error_description ="None of the interfaces are available.";
		}
		else if (hr == CO_S_NOTALLINTERFACES)	// Only some of the requests succeeded.
		{
			severity = "3";
			error_description ="Some of the interfaces aren't available.";
		}
		else
		{
			// Display the general failure message and exit.
			severity = "3";
			error_description ="Object Creation Failed: Send client data.";
		}
    
		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_NULL || error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, severity, 
					 error_description, error_msg);
		}

		return S_OK;
	}

    // Check the result of the individual interface query.
    hr = mqi.hr;
    if (FAILED(hr))
	{
		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_NULL || error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, "3", "Interface query", error_msg);
		}
		
        return S_OK;
    }

	// Sets the authentication information that will be used 
	// to make calls on the specified proxy.
	hr = CoSetProxyBlanket(mqi.pItf, 
						   RPC_C_AUTHN_WINNT, 
						   RPC_C_AUTHZ_NONE, 
						   authIdentity.Domain,
						   RPC_C_AUTHN_LEVEL_PKT,
						   RPC_C_IMP_LEVEL_IMPERSONATE, 
						   &authIdentity,
						   EOAC_NONE);
    if (FAILED(hr))
	{
		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, "3", "CoSetProxyBlanket failed!", error_msg);
		}

        return S_OK;
    }

    // Store the interface pointer in our local variable.
    m_pDoTest = (IQalibServerMain*)mqi.pItf;

    // Send current data set to the server.
    hr = m_pDoTest->ReceiveClientData(chemistry, 
									  outlierMethod, 
									  mode,
									  user,
									  sampleData, 
									  serialNumberList, 
									  barCode,
									  sampleSpecies,
									  sampleDataStatus,
									  calibrationID, 
									  error_msg);
    if (FAILED(hr))
	{
		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_NULL || error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, "3", "Call to ReceiveClientData", error_msg);
		}

		return S_OK;
	}

    // Uninitialize the COM environment.
    CoUninitialize();

	OKMessage(error_msg);

	return S_OK;
}

/*****************************************************************
 GetCalibrationResults(
					LONG calibrationID, 
					INT outlierMethod, 
					BSTR *partNumber, 
					BSTR *waveLength, 
					BSTR *species, 
					BSTR *diluent, 
					BSTR *mold, 
					BSTR *rotor, 
					BSTR *cuvette, 
					BSTR *mode, 
					BSTR *user, 
					BSTR *date, 
					VARIANT *description, 
					VARIANT *originalFitParameters, 
					VARIANT *newFitParameters, 
					VARIANT *minLimits, 
					VARIANT *maxLimits, 
					VARIANT *originalDisposition, 
					VARIANT *newDisposition, 
					VARIANT *calibrationData, 
					VARIANT *statusData, 
					VARIANT *rates, 
					VARIANT *plotData, 
					BSTR *comment, 
					VARIANT *perror_msg)
					
- Get calibration results from server.

INPUT
	calibrationID
	outlierMethod
	*partNumber
	*waveLength
	*species
	*diluent
	*mold
	*rotor
	*cuvette
	*mode
	*user
	*date
	*description
	*originalFitParameters
	*newFitParameters
	*minLimits
	*maxLimits
	*originalDisposition
	*newDisposition
	*calibrationData
	*statusData
	*rates
	*plotData
	*comment
	*perror_msg

OUTPUT
	Current results from server.

LOCAL
	m_pDoTest - Interface Pointer
	hr - Query Result.
	mqi - Interface we want to query.
	pSInfo - Server information.
	buf[80] - Buffer for error message.

FUNCTION CALLED
    CoInitialize - Initialize the COM environment.
    CoUninitialize - Uninitialize the COM environment.
    CoCreateInstanceEx - Create an instance of the object.
    m_pDoTest->ReceiveT4Data - Send current data set to the server.

*****************************************************************/
STDMETHODIMP QalibClientMain::GetCalibrationResults(
				LONG calibrationID, 
				BSTR *partNumber, 
				BSTR *waveLength, 
				BSTR *species, 
				BSTR *diluent, 
				BSTR *mold, 
				BSTR *rotor, 
				BSTR *cuvette, 
				BSTR *mode, 
				BSTR *user, 
				BSTR *date, 
				VARIANT *description, 
				VARIANT *originalFitParameters, 
				VARIANT *newFitParameters, 
				VARIANT *minLimits, 
				VARIANT *maxLimits, 
				VARIANT *originalDisposition, 
				VARIANT *newDisposition, 
				VARIANT *calibrationData, 
				VARIANT *statusData, 
				VARIANT *rates, 
				VARIANT *plotData, 
				BSTR *comment, 
				VARIANT *error_msg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

    IQalibServerMain*   m_pDoTest;  // Interface Pointer
	HRESULT				hr;         // Query Result.
	MULTI_QI			mqi;        // Interface we want to query.
    COSERVERINFO		serverInfo;	// Server information.
	COAUTHIDENTITY		authIdentity;
	COAUTHINFO			authInfo;

	HRESULT			hrEM;
	CString			error_source = "GetCalibrationResults";
	CString			severity;
	CString			error_description;

    // Initialize the interface pointer.
    m_pDoTest = NULL;

    // Initialize the COM environment.
    CoInitialize(NULL);
 
	// Initialize user's permissions.
	// User that is allowed to create objects in the server.
	hr = InitializeCOMUser(&authIdentity,
						   &authInfo,
						   &serverInfo,
						   &mqi,
						   error_msg);

    if (FAILED(hr))
	{
		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_EMPTY)
		{
			severity = "3";
			error_description ="Login failed.";
			hrEM = ErrorMessage(hr, error_source, severity, 
					 error_description, error_msg);
		}

		return S_OK;
	}

    // Create an instance of the object.
    hr = CoCreateInstanceEx(CLSID_QalibServerMain,
                            NULL, 
                            CLSCTX_ALL,
                            &serverInfo,
                            1, 
                            &mqi);
 
	// If the creation failed, exit.
    if (FAILED(hr))
	{
		severity = "3";

		// The class isn't registered.
        if (hr == REGDB_E_CLASSNOTREG)
		{
			severity = "3";
			error_description ="The class isn't registered on the server.";
        }
		else if (hr == E_INVALIDARG)	// One or more of the arguments was invalid.
		{
			severity = "3";
			error_description ="One or more of the arguments were invalid.";
		}
		else if (hr == E_NOINTERFACE)	// None of the requested interfaces are available.
		{
			severity = "3";
			error_description ="None of the interfaces are available.";
		}
		else if (hr == CO_S_NOTALLINTERFACES)	// Only some of the requests succeeded.
		{
			severity = "3";
			error_description ="Some of the interfaces aren't available.";
		}
		else
		{
			// Display the general failure message and exit.
			severity = "3";
			error_description ="Object Creation Failed. Get calibration results.";
		}

		// Uninitialize the COM environment.
		CoUninitialize();
	
		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, severity, 
					 error_description, error_msg);
		}
		
		return S_OK;
	}

    // Check the result of the individual interface query.
    hr = mqi.hr;
    if (FAILED(hr))
	{
		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_NULL || error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, "3", "Interface query", error_msg);
		}

        return S_OK;
    }

	// Sets the authentication information that will be used 
	// to make calls on the specified proxy.
	hr = CoSetProxyBlanket(mqi.pItf, 
						   RPC_C_AUTHN_WINNT, 
						   RPC_C_AUTHZ_NONE, 
						   authIdentity.Domain,
						   RPC_C_AUTHN_LEVEL_PKT,
						   RPC_C_IMP_LEVEL_IMPERSONATE, 
						   &authIdentity,
						   EOAC_NONE);
    if (FAILED(hr))
	{
		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, "3", "CoSetProxyBlanket failed!", error_msg);
		}

        return S_OK;
    }

    // Store the interface pointer in our local variable.
    m_pDoTest = (IQalibServerMain*)mqi.pItf;
 
    // Get current data from the server.
	hr = m_pDoTest->SendCalibrationResults(
						calibrationID, 
						partNumber, 
						waveLength, 
						species, 
						diluent, 
						mold, 
						rotor, 
						cuvette, 
						mode, 
						user, 
						date, 
						description, 
						originalFitParameters, 
						newFitParameters, 
						minLimits, 
						maxLimits, 
						originalDisposition, 
						newDisposition, 
						calibrationData, 
						statusData, 
						rates, 
						plotData, 
						comment, 
						error_msg);

	if (FAILED(hr))
	{
	    // Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_NULL || error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, "3", "SendCalibrationResults failed", error_msg);
		}

		return S_OK;
	}

    // Uninitialize the COM environment.
    CoUninitialize();

	OKMessage(error_msg);

	return S_OK;
}

/*****************************************************************
GetT4DBAssignedValues(const VARIANT *sampleIDsList, 
					  VARIANT *curAssignedValues)
					
- Get assigned values from server.

INPUT
	*sampleIDsList - List of samples to get assigned values.
	*curAssignedValues - Return current assigned values.

OUTPUT
	Current assigned values from server.

LOCAL
	m_pDoTest - Interface Pointer
	hr - Query Result.
	mqi - Interface we want to query.
	pSInfo - Server information.
	buf[80] - Buffer for error message.

FUNCTION CALLED
    CoInitialize - Initialize the COM environment.
    CoUninitialize - Uninitialize the COM environment.
    CoCreateInstanceEx - Create an instance of the object.
    m_pDoTest->SendDBAssignedValuesToClient - Get assigned values from the server.
*****************************************************************/
STDMETHODIMP QalibClientMain::GetAssignedValues(
				BSTR chemistry, 
				const VARIANT *sampleIDsList, 
				VARIANT *assignedValues, 
				VARIANT *error_msg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

    IQalibServerMain*   m_pDoTest;  // Interface Pointer
	HRESULT				hr;			// Query Result.
	MULTI_QI			mqi;        // Interface we want to query.
    COSERVERINFO		serverInfo;	// Server information.
	COAUTHIDENTITY		authIdentity;
	COAUTHINFO			authInfo;

	HRESULT			hrEM;
	CString			error_source = "GetAssignedValues";
	CString			severity;
	CString			error_description;

    // Initialize the interface pointer.
    m_pDoTest = NULL;

    // Initialize the COM environment.
    CoInitialize(NULL);

	// Initialize user's permissions.
	// User that is allowed to create objects in the server.
	hr = InitializeCOMUser(&authIdentity,
						   &authInfo,
						   &serverInfo,
						   &mqi,
						   error_msg);
    if (FAILED(hr))
	{
		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_EMPTY)
		{
			severity = "3";
			error_description ="Login failed.";
			hrEM = ErrorMessage(hr, error_source, severity, 
					 error_description, error_msg);
		}

		return S_OK;
	}

    // Create an instance of the object.
    hr = CoCreateInstanceEx(CLSID_QalibServerMain,
                            NULL, 
                            CLSCTX_ALL,
                            &serverInfo,
                            1, 
                            &mqi);
 
	// If the creation failed, exit.
    if (FAILED(hr))
	{
		severity = "3";

		// The class isn't registered.
        if (hr == REGDB_E_CLASSNOTREG)
		{
			severity = "3";
			error_description ="The class isn't registered on the server.";
        }
		else if (hr == E_INVALIDARG)	// One or more of the arguments was invalid.
		{
			severity = "3";
			error_description ="One or more of the arguments were invalid.";
		}
		else if (hr == E_NOINTERFACE)	// None of the requested interfaces are available.
		{
			severity = "3";
			error_description ="None of the interfaces are available.";
		}
		else if (hr == CO_S_NOTALLINTERFACES)	// Only some of the requests succeeded.
		{
			severity = "3";
			error_description ="Some of the interfaces aren't available.";
		}
		else
		{
			// Display the general failure message and exit.
			severity = "3";
			error_description ="Object Creation Failed. Get assigned values.";
		}
		
		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_NULL || error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, severity, 
						 error_description, error_msg);
		}

		return S_OK;
	}
	
    // Check the result of the individual interface query.
    hr = mqi.hr;
    if (FAILED(hr))
	{
		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_NULL || error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, "3", "Interface query", error_msg);
		}

        return S_OK;
    }

	// Sets the authentication information that will be used 
	// to make calls on the specified proxy.
	hr = CoSetProxyBlanket(mqi.pItf, 
						   RPC_C_AUTHN_WINNT, 
						   RPC_C_AUTHZ_NONE, 
						   authIdentity.Domain,
						   RPC_C_AUTHN_LEVEL_PKT,
						   RPC_C_IMP_LEVEL_IMPERSONATE, 
						   &authIdentity,
						   EOAC_NONE);
    if (FAILED(hr))
	{
		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, "3", "CoSetProxyBlanket failed!", error_msg);
		}

        return S_OK;
    }

    // Store the interface pointer in our local variable.
    m_pDoTest = (IQalibServerMain*)mqi.pItf;

    // Get assigned values from the server.
    hr = m_pDoTest->SendAssignedValues(chemistry, sampleIDsList, assignedValues, error_msg);
    if (FAILED(hr))
	{
	    // Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_NULL || error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, "3", "SendAssignedValues failed", error_msg);
		}

		return S_OK;
	}

    // Uninitialize the COM environment.
    CoUninitialize();
	
	OKMessage(error_msg);

	return S_OK;
}

/*****************************************************************
	SendUpdatedFitParameters(
			LONG calibrationID, 
			VARIANT *newFitPars, 
			VARIANT *error_msg)
					
- Send new fit parameters to server. To calculate new "best fit tests".

INPUT
	chemistry - Chemistry to apply new fit parameters to.
	wMethod - Weight method to use for calculations.
	*newFitPars - Array with new fit parameters.

OUTPUT
	"best fit tests" calculated with new fit parameter values.

LOCAL
	m_pDoTest - Interface Pointer
	hr - Query Result.
	mqi - Interface we want to query.
	pSInfo - Server information.
	buf[80] - Buffer for error message.

FUNCTION CALLED
    CoInitialize - Initialize the COM environment.
    CoUninitialize - Uninitialize the COM environment.
    CoCreateInstanceEx - Create an instance of the object.
    m_pDoTest->SendDBAssignedValuesToClient - Get assigned values from the server.
*****************************************************************/
STDMETHODIMP QalibClientMain::SendUpdatedFitParameters(
				LONG calibrationID, 
				VARIANT *newFitPars, 
				VARIANT *error_msg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

    IQalibServerMain*   m_pDoTest;		// Interface Pointer
	HRESULT				hr,hrEM;		// Query Result.
	MULTI_QI			mqi;			// Interface we want to query.
    COSERVERINFO		serverInfo;		// Server information.
	COAUTHIDENTITY		authIdentity;
	COAUTHINFO			authInfo;

	CString			error_source = "SendUpdatedFitParameters";
	CString			severity;
	CString			error_description;

    // Initialize the interface pointer.
    m_pDoTest = NULL;
 
    // Initialize the COM environment.
    CoInitialize(NULL);
 
	// Initialize user's permissions.
	// User that is allowed to create objects in the server.
	hr = InitializeCOMUser(&authIdentity,
						   &authInfo,
						   &serverInfo,
						   &mqi,
						   error_msg);
    if (FAILED(hr))
	{
		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_EMPTY)
		{
			severity = "3";
			error_description ="Login failed.";
			hrEM = ErrorMessage(hr, error_source, severity, 
					 error_description, error_msg);
		}

		return S_OK;
	}

    // Create an instance of the object.
    hr = CoCreateInstanceEx(CLSID_QalibServerMain,
                            NULL, 
                            CLSCTX_ALL,
                            &serverInfo,
                            1, 
                            &mqi);
 
	// If the creation failed, exit.
    if (FAILED(hr))
	{
		severity = "3";

		// The class isn't registered.
        if (hr == REGDB_E_CLASSNOTREG)
		{
			severity = "3";
			error_description ="The class isn't registered on the server.";
        }
		else if (hr == E_INVALIDARG)	// One or more of the arguments was invalid.
		{
			severity = "3";
			error_description ="One or more of the arguments were invalid.";
		}
		else if (hr == E_NOINTERFACE)	// None of the requested interfaces are available.
		{
			severity = "3";
			error_description ="None of the interfaces are available.";
		}
		else if (hr == CO_S_NOTALLINTERFACES)	// Only some of the requests succeeded.
		{
			severity = "3";
			error_description ="Some of the interfaces aren't available.";
		}
		else
		{
			// Display the general failure message and exit.
			severity = "3";
			error_description ="Object Creation Failed. Send updated fit parameters.";
		}

		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_NULL || error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, severity, 
					 error_description, error_msg);
		}

		return S_OK;
	}
	
    // Check the result of the individual interface query.
    hr = mqi.hr;
    if (FAILED(hr))
	{
		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_NULL || error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, "3", "Interface query", error_msg);
		}

        return S_OK;
    }

	// Sets the authentication information that will be used 
	// to make calls on the specified proxy.
	hr = CoSetProxyBlanket(mqi.pItf, 
						   RPC_C_AUTHN_WINNT, 
						   RPC_C_AUTHZ_NONE, 
						   authIdentity.Domain,
						   RPC_C_AUTHN_LEVEL_PKT,
						   RPC_C_IMP_LEVEL_IMPERSONATE, 
						   &authIdentity,
						   EOAC_NONE);
    if (FAILED(hr))
	{
		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, "3", "CoSetProxyBlanket failed!", error_msg);
		}

        return S_OK;
    }

    // Store the interface pointer in our local variable.
    m_pDoTest = (IQalibServerMain*)mqi.pItf;
 
    // Get current data from the server.
    hr = m_pDoTest->GetUpdatedFitParameters(calibrationID,newFitPars,error_msg);
    if (FAILED(hr))
	{
	    // Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_NULL || error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, "3", "GetUpdatedFitParameters failed", error_msg);
		}

		return S_OK;
	}

    // Uninitialize the COM environment.
    CoUninitialize();

	OKMessage(error_msg);

	return S_OK;
}

/*****************************************************************
	GetEditableFitParameters
			(LONG calibrationID, 
			 VARIANT *EditableFitParameters, 
			 VARIANT *error_msg)
					
- Get fit parameters that are editable.

INPUT
	calibrationID - Calibration id.
	*EditableFitParameters - Parameters that are editable.
	*error_msg - Error messages.

OUTPUT
	Editable fit parameters.

LOCAL

FUNCTION CALLED
    CoInitialize - Initialize the COM environment.
    CoUninitialize - Uninitialize the COM environment.
    CoCreateInstanceEx - Create an instance of the object.
    m_pDoTest->SendEditableFitParameters 
			   - Send editable fit parameters to the server.
*****************************************************************/
STDMETHODIMP QalibClientMain::GetEditableFitParameters(
				LONG calibrationID, 
				VARIANT *EditableFitParameters, 
				VARIANT *error_msg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

    IQalibServerMain*   m_pDoTest;  // Interface Pointer
	HRESULT				hr;         // Query Result.
	MULTI_QI			mqi;        // Interface we want to query.
    COSERVERINFO		serverInfo;	// Server information.
	COAUTHIDENTITY		authIdentity;
	COAUTHINFO			authInfo;

	HRESULT			hrEM;
	CString			error_source = "GetEditableFitParameters";
	CString			severity;
	CString			error_description;

    // Initialize the interface pointer.
    m_pDoTest = NULL;

    // Initialize the COM environment.
    CoInitialize(NULL);

	// Initialize user's permissions.
	// User that is allowed to create objects in the server.
	hr = InitializeCOMUser(&authIdentity,
						   &authInfo,
						   &serverInfo,
						   &mqi,
						   error_msg);
    if (FAILED(hr))
	{
		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_EMPTY)
		{
			severity = "3";
			error_description ="Login failed.";
			hrEM = ErrorMessage(hr, error_source, severity, 
					 error_description, error_msg);
		}

		return S_OK;
	}

    // Create an instance of the object.
    hr = CoCreateInstanceEx(CLSID_QalibServerMain,
                            NULL, 
                            CLSCTX_ALL,
                            &serverInfo,
                            1, 
                            &mqi);
 
	// If the creation failed, exit.
    if (FAILED(hr))
	{
		severity = "3";

		// The class isn't registered.
        if (hr == REGDB_E_CLASSNOTREG)
		{
			severity = "3";
			error_description ="The class isn't registered on the server.";
        }
		else if (hr == E_INVALIDARG)	// One or more of the arguments was invalid.
		{
			severity = "3";
			error_description ="One or more of the arguments were invalid.";
		}
		else if (hr == E_NOINTERFACE)	// None of the requested interfaces are available.
		{
			severity = "3";
			error_description ="None of the interfaces are available.";
		}
		else if (hr == CO_S_NOTALLINTERFACES)	// Only some of the requests succeeded.
		{
			severity = "3";
			error_description ="Some of the interfaces aren't available.";
		}
		else
		{
			// Display the general failure message and exit.
			severity = "3";
			error_description ="Object Creation Failed. Get editable fit parameters.";
		}
		
		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_NULL || error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, severity, 
						 error_description, error_msg);
		}

		return S_OK;
	}
	
    // Check the result of the individual interface query.
    hr = mqi.hr;
    if (FAILED(hr))
	{
		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_NULL || error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, "3", "Interface query", error_msg);
		}

        return S_OK;
    }

	// Sets the authentication information that will be used 
	// to make calls on the specified proxy.
	hr = CoSetProxyBlanket(mqi.pItf, 
						   RPC_C_AUTHN_WINNT, 
						   RPC_C_AUTHZ_NONE, 
						   authIdentity.Domain,
						   RPC_C_AUTHN_LEVEL_PKT,
						   RPC_C_IMP_LEVEL_IMPERSONATE, 
						   &authIdentity,
						   EOAC_NONE);
    if (FAILED(hr))
	{
		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, "3", "CoSetProxyBlanket failed!", error_msg);
		}

        return S_OK;
    }

    // Store the interface pointer in our local variable.
    m_pDoTest = (IQalibServerMain*)mqi.pItf;

    // Get assigned values from the server.
    hr = m_pDoTest->SendEditableFitParameters(calibrationID, EditableFitParameters, error_msg);
    if (FAILED(hr))
	{
		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_NULL || error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, "3", "SendEditableFitParameters failed", error_msg);
		}

		return S_OK;
	}

    // Uninitialize the COM environment.
    CoUninitialize();

	OKMessage(error_msg);

	return S_OK;
}

/*****************************************************************
	SendComment
		(LONG calibrationID, 
		 BSTR *comment, 
		 VARIANT *error_msg)
					
- Send calibration comment to server.

INPUT
	calibrationID - Calibration id.
	*comment - Comment to add.
	*error_msg - Error messages.

OUTPUT
	None.

LOCAL

FUNCTION CALLED
    CoInitialize - Initialize the COM environment.
    CoUninitialize - Uninitialize the COM environment.
    CoCreateInstanceEx - Create an instance of the object.
    m_pDoTest->SetComment - Set comment to new value.
*****************************************************************/
STDMETHODIMP QalibClientMain::SendComment(
				LONG calibrationID, 
				BSTR *comment, 
				VARIANT *error_msg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

    IQalibServerMain*   m_pDoTest;		// Interface Pointer
	HRESULT				hr,hrEM;        // Query Result.
	MULTI_QI			mqi;			// Interface we want to query.
    COSERVERINFO		serverInfo;		// Server information.
	COAUTHIDENTITY		authIdentity;
	COAUTHINFO			authInfo;

	CString			error_source = "SendComment";
	CString			severity;
	CString			error_description;

    // Initialize the interface pointer.
    m_pDoTest = NULL;
 
    // Initialize the COM environment.
    CoInitialize(NULL);
 
	// Initialize user's permissions.
	// User that is allowed to create objects in the server.
	hr = InitializeCOMUser(&authIdentity,
						   &authInfo,
						   &serverInfo,
						   &mqi,
						   error_msg);
    if (FAILED(hr))
	{
		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_EMPTY)
		{
			severity = "3";
			error_description ="Login failed.";
			hrEM = ErrorMessage(hr, error_source, severity, 
					 error_description, error_msg);
		}

		return S_OK;
	}

    // Create an instance of the object.
    hr = CoCreateInstanceEx(CLSID_QalibServerMain,
                            NULL, 
                            CLSCTX_ALL,
                            &serverInfo,
                            1, 
                            &mqi);
 
	// If the creation failed, exit.
    if (FAILED(hr))
	{
		severity = "3";

		// The class isn't registered.
        if (hr == REGDB_E_CLASSNOTREG)
		{
			severity = "3";
			error_description ="The class isn't registered on the server.";
        }
		else if (hr == E_INVALIDARG)	// One or more of the arguments was invalid.
		{
			severity = "3";
			error_description ="One or more of the arguments were invalid.";
		}
		else if (hr == E_NOINTERFACE)	// None of the requested interfaces are available.
		{
			severity = "3";
			error_description ="None of the interfaces are available.";
		}
		else if (hr == CO_S_NOTALLINTERFACES)	// Only some of the requests succeeded.
		{
			severity = "3";
			error_description ="Some of the interfaces aren't available.";
		}
		else
		{
			// Display the general failure message and exit.
			severity = "3";
			error_description ="Object Creation Failed. Send comment.";
		}

		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_NULL || error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, severity, 
					 error_description, error_msg);
		}
		
		return S_OK;
	}
	
    // Check the result of the individual interface query.
    hr = mqi.hr;
    if (FAILED(hr))
	{
		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_NULL || error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, "3", "Interface query", error_msg);
		}

        return S_OK;
    }

	// Sets the authentication information that will be used 
	// to make calls on the specified proxy.
	hr = CoSetProxyBlanket(mqi.pItf, 
						   RPC_C_AUTHN_WINNT, 
						   RPC_C_AUTHZ_NONE, 
						   authIdentity.Domain,
						   RPC_C_AUTHN_LEVEL_PKT,
						   RPC_C_IMP_LEVEL_IMPERSONATE, 
						   &authIdentity,
						   EOAC_NONE);
    if (FAILED(hr))
	{
		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, "3", "CoSetProxyBlanket failed!", error_msg);
		}

        return S_OK;
    }

    // Store the interface pointer in our local variable.
    m_pDoTest = (IQalibServerMain*)mqi.pItf;
 
    // Set comment in currrent calibration.
    hr = m_pDoTest->SetComment(calibrationID,comment,error_msg);
    if (FAILED(hr))
	{
		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_NULL || error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, "3", "SetComment failed", error_msg);
		}

		return S_OK;
	}

    // Uninitialize the COM environment.
    CoUninitialize();

	OKMessage(error_msg);

	return S_OK;
}

/*****************************************************************
STDMETHODIMP QalibClientMain::GetUserRights(
				BSTR user, 
				BSTR password, 
				VARIANT *modeList, 
				VARIANT *chemistryList, 
				VARIANT *error_msg)
					
Get current user's database access rights.

INPUT
	user - Current user's id.
	password - Current user's password.
	modeList - List of modes of access.
	chemistryList - List of chemistries current user is allowed to calibrate.
	error_msg - Error messages.

OUTPUT
	Current user's database access rights.

LOCAL

FUNCTION CALLED
    CoInitialize - Initialize the COM environment.
    CoUninitialize - Uninitialize the COM environment.
    CoCreateInstanceEx - Create an instance of the object.
    m_pDoTest->SetComment - Set comment to new value.
------------------------------------------------------------------
1. Call CoCreateInstanceEx with alternate credentials.
2. Call CoSetProxyBlanket(or IClientSecurity::SetBlanket) on each and
   every returned interface with alternate credentials.

This is the recommended approach.

*****************************************************************/
STDMETHODIMP QalibClientMain::GetUserRights(
				BSTR user, 
				BSTR password, 
				VARIANT *chemistryList, 
				VARIANT *modeList, 
				VARIANT *error_msg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

    IQalibServerMain*   m_pDoTest;		// Interface Pointer
	HRESULT				hr,hrEM;		// Query Result.
	MULTI_QI			mqi;			// Interface we want to query.
    COSERVERINFO		serverInfo;		// Server information.
	COAUTHIDENTITY		authIdentity;
	COAUTHINFO			authInfo;

	CString				error_source = "GetUserRights";
	CString				severity;
	CString				error_description;

    // Initialize the interface pointer.
    m_pDoTest = NULL;
 
    // Initialize the COM environment.
    CoInitialize(NULL);
 
	// Initialize user's permissions.
	// User that is allowed to create objects in the server.
	hr = InitializeCOMUser(&authIdentity,
						   &authInfo,
						   &serverInfo,
						   &mqi,
						   error_msg);
    if (FAILED(hr))
	{
		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_EMPTY)
		{
			severity = "3";
			error_description ="Login failed.";
			hrEM = ErrorMessage(hr, error_source, severity, 
					 error_description, error_msg);
		}

		return S_OK;
	}

    // Create an instance of the object.
    hr = CoCreateInstanceEx(CLSID_QalibServerMain,
                            NULL, 
                            CLSCTX_ALL,
                            &serverInfo,
                            1, 
                            &mqi);
	// If the creation failed, exit.
    if (FAILED(hr))
	{
		severity = "3";

		// The class isn't registered.
        if (hr == REGDB_E_CLASSNOTREG)
		{
			severity = "3";
			error_description ="The class isn't registered on the server.";
        }
		else if (hr == E_INVALIDARG)	// One or more of the arguments was invalid.
		{
			severity = "3";
			error_description ="One or more of the arguments were invalid.";
		}
		else if (hr == E_NOINTERFACE)	// None of the requested interfaces are available.
		{
			severity = "3";
			error_description ="None of the interfaces are available.";
		}
		else if (hr == CO_S_NOTALLINTERFACES)	// Only some of the requests succeeded.
		{
			severity = "3";
			error_description ="Some of the interfaces aren't available.";
		}
		else
		{
			// Display the general failure message and exit.
			severity = "3";
			error_description ="Object Creation Failed. Get user rights.";
		}

		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_NULL || error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, severity, 
					 error_description, error_msg);
		}
		
		return S_OK;
	}
	
    // Check the result of the individual interface query.
    hr = mqi.hr;
    if (FAILED(hr))
	{
		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_NULL || error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, "3", "Interface query", error_msg);
		}

        return S_OK;
    }

	// Sets the authentication information that will be used 
	// to make calls on the specified proxy.
	hr = CoSetProxyBlanket(mqi.pItf, 
						   RPC_C_AUTHN_WINNT, 
						   RPC_C_AUTHZ_NONE, 
						   authIdentity.Domain,
						   RPC_C_AUTHN_LEVEL_PKT,
						   RPC_C_IMP_LEVEL_IMPERSONATE, 
						   &authIdentity,
						   EOAC_NONE);
    if (FAILED(hr))
	{
		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, "3", "CoSetProxyBlanket failed!", error_msg);
		}

        return S_OK;
    }

    // Store the interface pointer in our local variable.
    m_pDoTest = (IQalibServerMain*)mqi.pItf;

    // Get current user's database access rights.
    hr = m_pDoTest->SendUserRights(user, password, chemistryList, modeList, error_msg);
    if (FAILED(hr))
	{
		// Uninitialize the COM environment.
		CoUninitialize();

		// If error message is set. Pass up to caller.
		if (error_msg->vt == VT_NULL || error_msg->vt == VT_EMPTY)
		{
			hrEM = ErrorMessage(hr, error_source, "3", "GetUserRights failed", error_msg);
		}

		return S_OK;
	}

    // Uninitialize the COM environment.
    CoUninitialize();

	OKMessage(error_msg);

	return S_OK;
}
