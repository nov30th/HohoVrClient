/*

  INET.H
  
	Header containing InternetGetFile and a wrapper function, InternetDownloadFile which also makes the Internet connection.
	
*/

#ifndef INET_H
#define INET_H
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#include <stdio.h>
#include <wininet.h>
#include <mmsystem.h>

enum
{
	INTERNET_ERROR_OPENURL=1,
		INTERNET_ERROR_FILEOPEN,
		INTERNET_ERROR_READFILE,
		INTERNET_ERROR_OPEN
};

UINT InternetGetFile (HINTERNET IN hOpen, // Handle from InternetOpen()
					  CHAR *szUrl,        // Full URL
					  CHAR *szFileName,
					  HWND hwndProgress,
					  int idStatusText,
					  int idProgressBar)
{
	DWORD dwSize;
	CHAR   szHead[] = "Accept: */*\r\nClient: http://www.nov30th.com/\r\n\r\n";
	VOID* szTemp[16384];
	HINTERNET  hConnect;
	FILE * pFile;
	if ( !(hConnect = InternetOpenUrlA ( hOpen, szUrl, szHead,
		lstrlenA (szHead), INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_RELOAD, 0)))
	{
		return INTERNET_ERROR_OPENURL;
	}
	
	if  ( !(pFile = fopen (szFileName, "wb" ) ) )
	{
		return INTERNET_ERROR_FILEOPEN;
	}
	
	DWORD dwByteToRead = 0;
	DWORD dwSizeOfRq = 4;
	DWORD dwBytes = 0;
	
	if (!HttpQueryInfo(hConnect, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, 
		(LPVOID)&dwByteToRead, &dwSizeOfRq, NULL))
	{
		dwByteToRead = 0;
	}
	do
	{
		// Keep coping in 16 KB chunks, while file has any data left.
		// Note: bigger buffer will greatly improve performance.
		if (!InternetReadFile (hConnect, szTemp, 16384,  &dwSize) )
		{
			fclose (pFile);
            return INTERNET_ERROR_READFILE;
		}
		if (!dwSize)
			break;  // Condition of dwSize=0 indicate EOF. Stop.
		else
			fwrite(szTemp, sizeof (char), dwSize , pFile);
		dwBytes+=dwSize;
		
	}   // do
	while (TRUE);
	fflush (pFile);
	fclose (pFile);
	return 0;
}

int InternetDownloadFile(HWND progressWindow, int idStatusText, int idProgressBar, char *URL, char *FileDest)
{
	DWORD dwFlags;
	DWORD dwResult = INTERNET_ERROR_OPEN;
	InternetGetConnectedState(&dwFlags, 0);
	if(dwFlags & 0x20)//take appropriate steps
		return INTERNET_ERROR_OPEN;
	CHAR strAgent[64];
	//sprintf(strAgent, "Agent%ld", timeGetTime());
	HINTERNET hOpen;
	if(!(dwFlags & INTERNET_CONNECTION_PROXY))
		hOpen = InternetOpenA(strAgent, INTERNET_OPEN_TYPE_PRECONFIG_WITH_NO_AUTOPROXY, NULL, NULL, 0);
	else
		hOpen = InternetOpenA(strAgent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if(hOpen)
	{
		dwResult = InternetGetFile(hOpen, URL, FileDest, progressWindow, idStatusText, idProgressBar);
		InternetCloseHandle(hOpen);
	}
	else return INTERNET_ERROR_OPEN;
	return dwResult;
}

#endif /*INET_H*/