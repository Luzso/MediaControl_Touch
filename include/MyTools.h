#include "string.h"

namespace tools{

    int getRowSizeBytes(int bitsPerPixel, int pixelWidth);
  
    int getRowSizeBytes(int bitsPerPixel, int pixelWidth){ 
       return (int)(((float)bitsPerPixel / 8.f) * (float)pixelWidth);
    }

}