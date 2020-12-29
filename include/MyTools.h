#include "string.h"

namespace tools{

    int getRowSizeBytes(int bitsPerPixel, int pixelWidth);
    void flipBufferVertical(uint8_t* srcBuffer, uint8_t* flippedBuffer, int nRows, int width, int bitsPerPixel);

    int getRowSizeBytes(int bitsPerPixel, int pixelWidth){ 
       return (int)(((float)bitsPerPixel / 8.f) * (float)pixelWidth);
    }

    void flipBufferVertical(uint8_t* srcBuffer, uint8_t* flippedBuffer, int nRows, int width, int bitsPerPixel){

        //int rowSizeBytes = getRowSizeBytes(bitsPerPixel, width);
        memcpy(flippedBuffer, srcBuffer, 320*240);
        /*for(int i_row = nRows - 1; i_row >= 0; i_row--){
            
            //memcpy(flippedBuffer + (nRows - 1 - i_row) * rowSizeBytes, srcBuffer + i_row * rowSizeBytes, rowSizeBytes);
            
        }*/
    }
}