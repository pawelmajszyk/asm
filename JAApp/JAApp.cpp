#include <windows.h>
#include <iostream>
#include <sstream>
#include <string.h>
#include "Image.h"
#include <chrono>
#include<thread>
#include <vector>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#define ID_BEEP 1
#define ID_QUIT 2
#define ID_FILE 3 
#define ID_TEXT 4
#define ID_ASM 5
#define ID_CPP 6
#define ID_FILE_NAME 7

typedef int(__stdcall* Sepia)(byte* pixels, int size, int32 bytesPerPixel);

void AddControls(HWND hwnd);
std::string open_file(HWND hwnd);
void checkButton(HWND hwnd, std::string fileName);
std::string fileName;


void prepareThreads(Sepia& ProcAdd, const HINSTANCE& hinstLib, BOOL& fRunTimeLinkSuccess, int32& bytesPerPixel, const int32& width, const int32& height, byte* pixels,int threads);
void prepareData(std::string fileName, int threads);


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PWSTR lpCmdLine, int nCmdShow) {



    MSG  msg;
    WNDCLASSW wc = { 0 };
    wc.lpszClassName = L"Sepia";
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"Buttons",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        150, 150, 700, 500, 0, 0, hInstance, 0);

    while (GetMessage(&msg, NULL, 0, 0)) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {

    int threads = 1;
    checkButton(hwnd, fileName);
    switch (msg) {

    case WM_CREATE:

        AddControls(hwnd);
        break;

    case WM_COMMAND:

        if (LOWORD(wParam) == ID_BEEP) {
            threads = GetDlgItemInt(hwnd, ID_TEXT,NULL,NULL);
            prepareData(fileName, threads);
            PostQuitMessage(0);
        }

        if (LOWORD(wParam) == ID_FILE) {

            fileName = open_file(hwnd);
        }
        if (LOWORD(wParam) == ID_QUIT) {

            PostQuitMessage(0);
        }
        if (LOWORD(wParam) == ID_ASM) {
            CheckDlgButton(hwnd, 6, BST_UNCHECKED);

        }
        if (LOWORD(wParam) == ID_CPP) {

            CheckDlgButton(hwnd, 5, BST_UNCHECKED);
        }

        break;

    case WM_DESTROY:

        PostQuitMessage(0);
        break;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void AddControls(HWND hwnd)
{
    CreateWindowEx(NULL, L"BUTTON", L"Choose file!", WS_CHILD | WS_VISIBLE
        , 285, 200, 150, 36, hwnd, (HMENU)ID_FILE, NULL, NULL);

    CreateWindowW(L"Static", L"How many threads?(1-64):",
        WS_VISIBLE | WS_CHILD | WS_TABSTOP,
        290, 150, 400, 25, hwnd, (HMENU)ID_FILE, NULL, NULL);
    CreateWindow(L"EDIT", L"1", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_NUMBER, 320, 165, 50, 20, hwnd, (HMENU)ID_TEXT, NULL, 0);

    CreateWindowW(L"Static", L"not chosen yet",
        WS_VISIBLE | WS_CHILD | WS_TABSTOP,
        450, 215, 130, 25, hwnd, (HMENU)ID_FILE, NULL, NULL);
    CreateWindowW(L"Static", L"Your choice:",
        WS_VISIBLE | WS_CHILD | WS_TABSTOP,
        450, 190, 130, 25, hwnd, (HMENU)ID_FILE, NULL, NULL);
    CreateWindowEx(NULL, L"BUTTON", L"C++!", WS_CHILD | WS_VISIBLE |
        BS_AUTOCHECKBOX, 280, 300, 60, 20, hwnd, (HMENU)ID_CPP, NULL, NULL);
    CreateWindowEx(NULL, L"BUTTON", L"ASM!", WS_CHILD | WS_VISIBLE |
        BS_AUTOCHECKBOX, 380, 300, 60, 20, hwnd, (HMENU)ID_ASM, NULL, NULL);

    CreateWindowW(L"Button", L"Start",
        WS_VISIBLE | WS_CHILD,
        360, 360, 80, 25, hwnd, (HMENU)ID_BEEP, NULL, NULL);
    EnableWindow(GetDlgItem(hwnd, ID_BEEP), false); 

    CreateWindowW(L"Button", L"Quit",
        WS_VISIBLE | WS_CHILD,
        260, 360, 80, 25, hwnd, (HMENU)ID_QUIT, NULL, NULL);
    return;
}
std::string open_file(HWND hwnd)
{
    OPENFILENAME ofn;
    wchar_t file_name[100];
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter =
        L"Image files (*.jpg;*.png;*.bmp)\0*.jpg;*.png;*.bmp\0";
    ofn.lpstrFile = file_name;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 100;
    ofn.nFilterIndex = 1;
    GetOpenFileName(&ofn);
    MessageBox(NULL, ofn.lpstrFile, L"", MB_OK);
    std::wstring ws(file_name);
    std::string str(ws.begin(), ws.end());
    return str;
}
void checkButton(HWND hwnd, std::string)
{
    UINT checkCpp = IsDlgButtonChecked(hwnd, ID_CPP);
    UINT checkAsm = IsDlgButtonChecked(hwnd, ID_ASM);

    if ((checkCpp == BST_CHECKED || checkAsm == BST_CHECKED))
    {
        EnableWindow(GetDlgItem(hwnd, ID_BEEP), true); // to disable button or other control

    }
}

void prepareData(std::string fileName, int threads)
{
    char buffer[50];
    strcpy(buffer, fileName.c_str());
    HINSTANCE hinstLib;
    Sepia ProcAdd;
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;
    byte* pixels;
    int32 width;
    int32 height;
    int32 bytesPerPixel;
    readImage(buffer, &pixels, &width, &height, &bytesPerPixel);

    hinstLib = LoadLibrary(TEXT("C:\\Sem5\\JAApp\\x64\\Release\\CppDLL.dll"));
    if (hinstLib != NULL)
    {
        prepareThreads(ProcAdd, hinstLib, fRunTimeLinkSuccess, bytesPerPixel, width, height, pixels,threads);
        // fFreeResult = FreeLibrary(hinstLib);
    }
    writeImage("finalOutput.bmp", pixels, width, height, bytesPerPixel);
//    free(pixels);
}

void prepareThreads(Sepia& ProcAdd, const HINSTANCE& hinstLib, 
    BOOL& fRunTimeLinkSuccess, int32& bytesPerPixel, const int32& width,
    const int32& height, byte* pixels, int thread)
{
    ProcAdd = (Sepia)GetProcAddress(hinstLib, "sepia");
    if (NULL != ProcAdd)
    {
        fRunTimeLinkSuccess = TRUE;
        int threadsAmount = 2;
        int sizeOfSubArray = (bytesPerPixel * width * height) / threadsAmount;
        std::vector<std::thread> threads;


        for (int i = 0; i < threadsAmount; i++) {

            threads.push_back(std::thread(ProcAdd, pixels + i * sizeOfSubArray, sizeOfSubArray, bytesPerPixel));
        }
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        for (auto& th : threads) {
            th.join();
        }
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::cout << "xD";
       long long x =  std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
       std::cout << x;

    }
}
