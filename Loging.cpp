/*******************************************************************

FILENAME:	Loging.cpp

--------------------------------------------------------------------
MODULE DESCRIPTION:
	Loging functions.

--------------------------------------------------------------------
GLOBAL FUNCTIONS:
	void InitializeLogFile(char *InitialMessage);
	void CleanUpLogFile(char *CloseMessage);
	void CurrentSystemDate(char *curDate);

--------------------------------------------------------------------
COMPILER: Visual C++ 6.0	INVOCATION: Build ->Compile	Loging.cpp

--------------------------------------------------------------------
$HISTORY: $

*******************************************************************/
#include "stdafx.h"
#include "Loging.h"

//bool hadtoopenfile = false;
bool hadtoopenfile;
ofstream LogFile;

void InitializeLogFile(char *InitialMessage)
{
//	strcpy(logfilename,"C:\\Assignments\\Calibration\\T4Calibration\\QalibT4Client\\Log\\Client.log");
	strcpy(logfilename,"C:\\Calibration\\Logs\\Client.log");
	LogFile.open(logfilename,ios::out | ios::app);
//	CurrentSystemDate(curDate);
	LogFile << InitialMessage << endl;
	LogFile << curDate << endl;
}

void CleanUpLogFile(char *CloseMessage)
{
	hadtoopenfile = false;
	LogFile << CloseMessage << endl;
	LogFile.close();
}

/***************************************************
void CurrentSystemDate(char *curDate)
Gets the current date and time.

INPUT
	curDate - String to return current date.
OUTPUT
	none.
RETURN
	none.
***************************************************/
void CurrentSystemDate(char *curDate)
{
	struct tm *newtime;
	char am_pm[] = "AM";
	time_t long_time;

	time( &long_time );					/* Get time as long integer. */
	newtime = localtime( &long_time );	/* Convert to local time. */

	if( newtime->tm_hour > 12 )			/* Set up extension. */
		strcpy( am_pm, "PM" );
	if( newtime->tm_hour > 12 )			/* Convert from 24-hour */
		newtime->tm_hour -= 12;			/*   to 12-hour clock.  */
	if( newtime->tm_hour == 0 )			/*Set hour to 12 if midnight. */
		newtime->tm_hour = 12;

	sprintf(curDate,"%.19s %s\n", asctime( newtime ), am_pm );
}

HRESULT ErrorMessage(HRESULT phr, CString error_source, CString severity, 
					 CString error_description, VARIANT *error_msg)
{
	HRESULT	hr;
	long	k;
	char	*ptrMsgText;
	CString	partialMsg;

    SAFEARRAY FAR* psa_error_msg = NULL;
    SAFEARRAYBOUND error_sabound[1];

	// Build error message.
	partialMsg.FormatMessage(_T("Error: Source %1!s!. %2!s!."), 
		error_source.GetBuffer(error_source.GetLength()),
		error_description.GetBuffer(error_description.GetLength()));

	// Change error message format.
	ptrMsgText = (char *)partialMsg.GetBuffer(partialMsg.GetLength());
//	ptrMsgText = partialMsg.GetBuffer(partialMsg.GetLength());

	// Set size of error array to pass to client.
	error_sabound[0].cElements = 2;
	error_sabound[0].lLbound = 0;
	psa_error_msg = SafeArrayCreate(VT_BSTR, 1, error_sabound);

	if (LogFile.is_open() == 0)
	{
		InitializeLogFile(ptrMsgText);
	}
	else
	{
		LogFile << ptrMsgText << endl;
	}

	LogFile << "\tFailure code: " << dec << phr << "\t(" << hex << phr << ")" << endl;
	CleanUpLogFile(ptrMsgText);

	k=0;
	hr = SafeArrayPutElement(psa_error_msg, &k, severity.AllocSysString());
	k++;
	hr = SafeArrayPutElement(psa_error_msg, &k, error_description.AllocSysString());

	// Set the return error message, array of VT_BSTR.
	// VT_BSTR, strings. Type of data to return in perror_msg.
	// Which values are editable. i.e. can be changed.
	V_VT(error_msg) = VT_ARRAY | VT_BSTR;
	// Set return Editable array to contain error messages.
	V_ARRAY(error_msg) = psa_error_msg;

	return phr;
}


/************************************************************
HRESULT OKMessage(VARIANT *error_msg)

	Display current OK message.

-------------------------------------------------------------
 INPUT
	*error_msg - OK message buffer.

-------------------------------------------------------------
 OUTPUT
	OK message.

-------------------------------------------------------------
 LOCAL
	hr - Return code.
	k - Index for SAFEARRAYs.
	psa_error_msg - SAFEARRAY pointer to set error message.
	error_sabound[1] - Error message array boundary.

-------------------------------------------------------------
 RETURN
	None.

*************************************************************/
HRESULT OKMessage(VARIANT *error_msg)
{
	HRESULT	hr;
	long	k;

    SAFEARRAY FAR* psa_error_msg = NULL;
    SAFEARRAYBOUND error_sabound[1];

	BSTR code = SysAllocString(L"0");
	BSTR msg = SysAllocString(L"OK");

	// Set size of error array to pass to client.
	error_sabound[0].cElements = 2;
	error_sabound[0].lLbound = 0;
	psa_error_msg = SafeArrayCreate(VT_BSTR, 1, error_sabound);

	k=0;
	hr = SafeArrayPutElement(psa_error_msg, &k, code);
	k++;
	hr = SafeArrayPutElement(psa_error_msg, &k, msg);

	// Set the return error message, array of VT_BSTR.
	// VT_BSTR, strings. Type of data to return in perror_msg.
	// Which values are editable. i.e. can be changed.
	V_VT(error_msg) = VT_ARRAY | VT_BSTR;
	// Set return Editable array to contain error messages.
	V_ARRAY(error_msg) = psa_error_msg;

	return S_OK;
}

void DisplayVariant(VARIANT *displayVariant)
{
    SAFEARRAY FAR*	psa_displayVariant;		// sample plot list.
	HRESULT			hr;
	LONG			cElements, lLBound, lUBound;

	long i=0;

	if (LogFile.is_open() == 0)
	{
		InitializeLogFile("\n\nBEGIN DisplayVariant");
	}
	else
	{
		LogFile << "BEGIN DisplayVariant" << endl;
	}

	// set psa_plotList safearray pointer to the current plot list.
	psa_displayVariant = V_ARRAY(displayVariant);

	// Get array lower bound.
	hr = SafeArrayGetLBound(psa_displayVariant, 1, &lLBound);
	if (FAILED(hr))
	{
		LogFile << "Array lower bound failed!" << endl;
	}
	else
	{
		// Get array upper bound.
		hr = SafeArrayGetUBound(psa_displayVariant, 1, &lUBound);
		if(FAILED(hr))
		{
			LogFile << "Array upper bound failed!" << endl;
		}
		else
		{
			// Number of elements in array.
			cElements = lUBound-lLBound+1;

			LogFile << "Number of elements to display = " << cElements << endl;

			// Test array's type.
			if ( displayVariant->vt == 8200 )	// if ( displayVariant->vt == VT_BSTR )
			{
				BSTR bstr = NULL;

				LogFile << "Current array type = BSTR" << endl;

				// Get current string to display.
				while ((hr = SafeArrayGetElement(psa_displayVariant, &i, &bstr)) == S_OK)
				{
					LogFile << (CString)bstr << endl;
					i++;
				}

				LogFile << "Number of BSTRs = " << i << endl;
			}
			else if ( displayVariant->vt == 8197 )	// if ( displayVariant->vt == VT_R8 )
			{
				double data_value;
			
				LogFile << "Current array type = VT_R8" << endl;

				// Get current double value to display.
				while ((hr = SafeArrayGetElement(psa_displayVariant, &i, &data_value)) == S_OK)
				{
					LogFile << data_value << endl;
					i++;
				}
				
				LogFile << "Number of VT_R8s = " << i << endl;
			}
		}
	}

//	CleanUpLogFile("END DisplayVariant");
	LogFile << "END DisplayVariant" << endl << endl << endl;
}

void DisplayBSTR(BSTR toDisplay, CString source)
{
	CString temp;

	temp = toDisplay;

	DisplayCString(&temp, source);
}

void DisplayCString(CString *displayCString, CString source)
{
	char			buf[256];

	sprintf(buf,"\nBEGIN %s", source);

	if (LogFile.is_open() == 0)
	{
		InitializeLogFile(buf);
	}
	else
	{
		LogFile.write(buf, strlen(buf));
	}

	if (displayCString->GetLength() > 0)
	{
		sprintf(buf,"%s\n", *displayCString);
		LogFile.write(buf, strlen(buf));
	}
	else
	{
		sprintf(buf,"\t%s is empty!\n", source);
		LogFile.write(buf, strlen(buf));
	}

	sprintf(buf,"END %s\n\n", source);
	CleanUpLogFile(buf);
}
