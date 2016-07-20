#pragma once

#include <string>

#include <windows.h>
#include <dbghelp.h> 
using namespace std;

#pragma comment(lib, "version.lib")

class CSystemHelper
{
public:
	CSystemHelper(){}
	~CSystemHelper(){}

public:
	/**
	 * @breif ��ȡ�ļ��汾���������ʾ����v1.0.0.1
     * 
     * @param cFileName[in]  �ļ�·��
     *
     * @code
       int main(int argc, char* argv[])
        {
		    string cVersion = CSystemHelper::GetFileVersionString("D:\\WorkSpace\\ZCMsgService\\Release\\ZCMsgService.exe");
		    cout << cVersion << endl;

            ::system("pause");
            return 0;
        }
     * @endcode
	 */
	static string GetFileVersionString(char* cFileName)
	{
		string verString("unknown");

		DWORD dwHandle;
		int size = GetFileVersionInfoSizeA(cFileName, &dwHandle);
		if (size > 0)
		{
			byte *pBuffer = new byte[size];
			if (GetFileVersionInfoA(cFileName, dwHandle, size, pBuffer))
			{
				VS_FIXEDFILEINFO *pVI = NULL;
				if (VerQueryValue(pBuffer, (LPCWSTR)"\\", (LPVOID*)&pVI, (PUINT)&size))
				{
					char szVer[64] = { 0 };
					sprintf_s(szVer,64, "v%d.%d.%d.%d", HIWORD(pVI->dwFileVersionMS), LOWORD(pVI->dwFileVersionMS),
						HIWORD(pVI->dwFileVersionLS), LOWORD(pVI->dwFileVersionLS));
					verString = szVer;
				}
			}
			delete[] pBuffer;
		}

		return verString;
	} 

	/**
	 * @breif ��ȡ��ǰӦ�ó���汾���������ʾ����v1.0.0.1
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     string cVersion = CSystemHelper::GetCurrentFileVersionString();
		 cout << cVersion << endl;

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static string GetCurrentFileVersionString()
	{
		char fileName[MAX_PATH] = {0};
		GetModuleFileNameA(NULL, fileName, sizeof(fileName));

		return GetFileVersionString(fileName);
	}
};