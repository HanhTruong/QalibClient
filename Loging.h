/*******************************************************************

FILENAME:	Loging.h

--------------------------------------------------------------------
MODULE DESCRIPTION:
	Loging functions declarations.

--------------------------------------------------------------------
GLOBAL FUNCTIONS:

--------------------------------------------------------------------
COMPILER: Visual C++ 6.0	INVOCATION: Build ->Compile	Loging.h

--------------------------------------------------------------------
$HISTORY: $

*******************************************************************/
#include <fstream.h>

extern ofstream	LogFile;
static char	logfilename[256];
static char	curDate[128];
extern bool	hadtoopenfile;

void InitializeLogFile(char *InitialMessage);
void CleanUpLogFile(char *CloseMessage);
void CurrentSystemDate(char *curDate);

HRESULT ErrorMessage(HRESULT phr, CString error_source, CString severity, 
					 CString error_description, VARIANT *error_msg);

HRESULT OKMessage(VARIANT *error_msg);

void DisplayVariant(VARIANT *displayVariant);
void DisplayBSTR(BSTR toDisplay, CString source);
void DisplayCString(CString *displayCString, CString source);

