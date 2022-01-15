//#include <iostream>
//#include <windows.h> 
//#include "Image.h"
//#include<thread>
//#include <vector>
//
//
//typedef int(__cdecl* Sepia)(byte* pixels, int size, int32 bytesPerPixel);
//
//LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
//
//
//
//void prepareThreads(Sepia& ProcAdd, const HINSTANCE& hinstLib, BOOL& fRunTimeLinkSuccess, int32& bytesPerPixel, const int32& width, const int32& height, byte* pixels);
//
//int main()
////int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//    HINSTANCE hinstLib;
//    Sepia ProcAdd;
//    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;
//    byte* pixels;
//    int32 width;
//    int32 height;
//    int32 bytesPerPixel;
//    readImage("test.bmp", &pixels, &width, &height, &bytesPerPixel);
//
//    hinstLib = LoadLibrary(TEXT("C:\\Sem5\\JAApp\\Debug\\CppDLL.dll"));
//    if (hinstLib != NULL)
//    {
//        prepareThreads(ProcAdd, hinstLib, fRunTimeLinkSuccess, bytesPerPixel, width, height, pixels);
//        // fFreeResult = FreeLibrary(hinstLib);
//    }
//    writeImage("finalTest.bmp", pixels, width, height, bytesPerPixel);
//    free(pixels);
//    return 0;
//}
//
//void prepareThreads(Sepia& ProcAdd, const HINSTANCE& hinstLib, BOOL& fRunTimeLinkSuccess, int32& bytesPerPixel, const int32& width, const int32& height, byte* pixels)
//{
//    ProcAdd = (Sepia)GetProcAddress(hinstLib, "sepia");
//    if (NULL != ProcAdd)
//    {
//        fRunTimeLinkSuccess = TRUE;
//        int threadsAmount = 24;
//        int sizeOfSubArray = (bytesPerPixel * width * height) / threadsAmount;
//        std::vector<std::thread> threads;
//        for (int i = 0; i < threadsAmount; i++) {
//
//            threads.push_back(std::thread(ProcAdd, pixels + i * sizeOfSubArray, sizeOfSubArray, bytesPerPixel));
//        }
//        for (auto& th : threads) {
//            th.join();
//        }
//
//    }
//}
