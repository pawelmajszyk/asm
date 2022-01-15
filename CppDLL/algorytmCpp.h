#pragma once

typedef unsigned int int32;
typedef short int16;
typedef unsigned char byte;
#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif


extern "C" MATHLIBRARY_API void sepia(byte * pixels, int size,int32 bytesPerPixel);