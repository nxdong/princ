#include "stdafx.h"
#include "UnicodeChange.h"
CString ANSIToUnicode( char* str )
{
	int  unicodeLen = ::MultiByteToWideChar( CP_ACP,
		0,
		str,
		-1,
		NULL,
		0 );  
	wchar_t *  pUnicode;  
	pUnicode = new  wchar_t[unicodeLen+1];  
	memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));  
	::MultiByteToWideChar( CP_ACP,
		0,
		str,
		-1,
		(LPWSTR)pUnicode,
		unicodeLen );  
	CString rt;  
	rt = ( wchar_t* )pUnicode;
	delete  pUnicode; 
	return  rt;  
}
char* UnicodeToANSI( CString str )
{
	char*     pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte( CP_ACP,
		0,
		str,
		-1,
		NULL,
		0,
		NULL,
		NULL );
	pElementText = new char[iTextLen + 1];
	memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );
	::WideCharToMultiByte( CP_ACP,
		0,
		str,
		-1,
		pElementText,
		iTextLen,
		NULL,
		NULL );
	char * strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}