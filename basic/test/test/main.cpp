#include<windows.h>  
#include"mmsystem.h"  
#pragma comment(lib,"winmm.lib")  

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MCI_OPEN_PARMS openparms;
	openparms.lpstrDeviceType = "MPEGvideo";
	openparms.lpstrElementName = "F://1.mp3";

	CHAR	strMciError[300];

	mciSendCommand(NULL, MCI_OPEN,
		MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_WAIT,
		(DWORD)(LPVOID)(&openparms));

	MCI_PLAY_PARMS playparms;
	MCIERROR err = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&openparms);
	if (err)
	{
		mciGetErrorString(err, strMciError, sizeof(strMciError));
		

	}

	mciSendCommand(openparms.wDeviceID, MCI_CLOSE, NULL, NULL);
	return  0;
}