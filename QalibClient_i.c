/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Oct 12 13:41:03 2005
 */
/* Compiler settings for C:\Qalib\_Calibration\QalibClient\QalibClient.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IQalibClientMain = {0x084F9ED2,0xD274,0x4314,{0xA6,0x1E,0xE3,0xE9,0xF9,0x04,0x10,0xEC}};


const IID LIBID_QALIBCLIENTLib = {0xBE3B34EB,0x5511,0x450A,{0xA7,0x02,0x12,0x11,0xA6,0x1A,0xCA,0x97}};


const CLSID CLSID_QalibClientMain = {0xF36AF9A7,0xD575,0x49C1,{0x9B,0xBF,0xC9,0x7A,0x2A,0x69,0x4D,0x46}};


#ifdef __cplusplus
}
#endif

