/********************************************************************

FILENAME:	Security.cpp
_____________________________________________________________________

MODULE DESCRIPTION:

	Client access to server.

_____________________________________________________________________

GLOBAL FUNCTIONS:

	Name			Description


	Name			Description

_____________________________________________________________________

COMPILER: Visual C++ 6.0		INVOCATION: Build->Compile Secuity.cpp

_____________________________________________________________________

HISTORY:

Version	Date		Author		Description
1.0.0.0	07/15/04	Alves		Client access to server.

********************************************************************/
#include "stdafx.h"
#include "QalibClient.h"
#include "QalibClientMain.h"
#include "Loging.h"


/********************************************************************
FUNCTION:
	InitializeCOMUser
_____________________________________________________________________
DESCRIPTION:
	Sets access data structure.
_____________________________________________________________________
GLOBAL VARIABLES:
	None.
____________________________________________________________________
LOCAL VARIABLES:
	hr - Function status code.
____________________________________________________________________
PARAMETERS:
	authIdentity - A COAUTHIDENTITY structure represents a user name and password
	authInfo	 - The COAUTHINFO structure provides security information 
				   to object creation functions across the network. 
	serverInfo	 - The COSERVERINFO structure is used primarily to 
				   identify a remote system in object creation functions.
	mqi			 - A set of pointers to interfaces to be returned 
				   from the same object in a single round-trip to the server.
	error_msg - Client error reporting.

____________________________________________________________________
TESTING HISTORY:

_____________________________________________________________________

MODIFICATIONS:

Version	Date		Author		Description
1.0.0.0	07/15/04	Alves		Initialize COM object, access.

********************************************************************/
HRESULT InitializeCOMUser(COAUTHIDENTITY *authIdentity,
						  COAUTHINFO *authInfo,
						  COSERVERINFO *serverInfo,
						  MULTI_QI *mqi,
						  VARIANT *error_msg)
{
	HRESULT hr=S_OK;

	ZeroMemory(serverInfo, sizeof(COSERVERINFO));
	ZeroMemory(authInfo, sizeof(COAUTHINFO));

	authIdentity->User = L"CreateComObjects";
	authIdentity->UserLength = wcslen(authIdentity->User);
// GET FROM REGISTRY ?????????????????????????????????????????????????
//	authIdentity->Domain = L"Rdswtestsvr";
	authIdentity->Domain = L"SQLWIN2000SRVR";
	authIdentity->DomainLength = wcslen(authIdentity->Domain);
// GET FROM REGISTRY ?????????????????????????????????????????????????
	authIdentity->Password = L"#!create!#";
	authIdentity->PasswordLength = wcslen(authIdentity->Password);
	authIdentity->Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;

	authInfo->dwAuthnSvc = RPC_C_AUTHN_WINNT;
	authInfo->dwAuthzSvc = RPC_C_AUTHZ_NONE;
	authInfo->pwszServerPrincName = NULL;
	authInfo->dwAuthnLevel = RPC_C_AUTHN_LEVEL_CONNECT;
//	authInfo->dwAuthnLevel = RPC_C_AUTHN_LEVEL_DEFAULT;
	authInfo->dwImpersonationLevel = RPC_C_IMP_LEVEL_IMPERSONATE;
	authInfo->pAuthIdentityData = authIdentity;
	authInfo->dwCapabilities = EOAC_NONE;

// GET FROM REGISTRY ?????????????????????????????????????????????????
	serverInfo->pwszName = L"\\\\SQLWIN2000SRVR";
//	serverInfo->pwszName = L"\\\\Rdswtestsvr";
// GET FROM REGISTRY ?????????????????????????????????????????????????
	serverInfo->pAuthInfo = authInfo;
//	serverInfo->pAuthInfo = NULL;
	serverInfo->dwReserved1 = 0;
	serverInfo->dwReserved2 = 0;

    // Initialize the result structure.
    mqi->pIID = &IID_IQalibServerMain;
    mqi->pItf = NULL;
    mqi->hr = 0;

	return hr;
}