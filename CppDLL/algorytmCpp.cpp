#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include <utility>
#include <limits.h>
#include "algorytmCpp.h"



// Get the current index position in the sequence.
void  sepia(byte* pixels, int size, int32 bytesPerPixel)
{

    float tmpGreen;
    float tmpRed;
    float tmpBlue;
    float sepiaRed;
    float sepiaBlue;
    float sepiaGreen;
    for (int i = 0; i < size; i += 3)
    {
        tmpGreen = (float)pixels[i + 1];
        tmpRed = (float)pixels[i + 2];
        tmpBlue = (float)pixels[i];

        sepiaRed = (int)(0.393 * tmpRed + 0.769 * tmpGreen + 0.189 * tmpBlue); //red
        sepiaGreen = (int)(0.349 * tmpRed + 0.686 * tmpGreen + 0.168 * tmpBlue); //green
        sepiaBlue = (int)(0.272 * tmpRed + 0.534 * tmpGreen + 0.131 * tmpBlue); //blue

        sepiaRed = min(sepiaRed, 255);
        sepiaGreen = min(sepiaGreen, 255);
        sepiaBlue = min(sepiaBlue, 255);

        pixels[i + 2] = sepiaRed;
        pixels[i + 1] = sepiaGreen;
        pixels[i] = sepiaBlue;


    }

}