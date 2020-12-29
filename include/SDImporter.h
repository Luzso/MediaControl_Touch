#include "SD.h "

#define BLOCK_SIZE 80000

struct BMP
{
    long width = 0;
    long height = 0;
    int bitsPerPixel = 0;
    int bytesPerPixel = 0;
    long nColors = 0;
    File file;
    long currentRow = 0;
    long nBytes;
    uint8_t gbrColors[256*4];

    ~BMP(){
    }

    void setWidth(long w){
        this->width = w;
    }

    void setHeight(long h){
        this->height = h;
    }

    void setBitsPerPixel(int nBits){
        this->bitsPerPixel = nBits;
        this->bytesPerPixel = nBits / 8;

        if(width != 0 && height != 0){
            this->nBytes = width * height * bytesPerPixel;
        }
    }

    // Returns the number of rows that were read.
    //
    // buffer: The buffer array where the read data is stored
    // bufferSizeBytes: The size of the buffer in bytes
    // nBytesPerRow: How many bytes there are in each row
    int getChunk(uint8_t* buffer, int bufferSizeBytes, int nBytesPerRow){

        if(this->file.available() > 0){
            int nReadTotal = 0;
            int nRowsRead = 0;
            int nMaxRows = (bufferSizeBytes / nBytesPerRow);
            int idrow = nMaxRows - 1;
            // Read data rows and fill the buffer from the back, since the y-axis of the image is flipped
            while(this->file.available() > 0 && nRowsRead <= nMaxRows && idrow >= 0){
                int nRead = this->file.readBytes(buffer + idrow*nBytesPerRow, nBytesPerRow); // Read one row of bytes
                nReadTotal += nRead;

                if(nRead == nBytesPerRow)
                    nRowsRead++;

                idrow--;
            }

            // Move the data so that it starts at the beginning of the buffer
            memcpy(buffer, buffer + ((idrow + 1)*nBytesPerRow), nReadTotal);

            if(nRowsRead > 0)
                return nReadTotal;
            else 
                return -1;
        }
        else{
            return -1;
        }

    }
};


class SDImporter
{

public:
    SDImporter();

    BMP readBMPFile(String* filename);
    bool tryGetFile(String* filename, File* file);
    void printDirectory(File dir, int numTabs);
    long getBitmapFileSize(char* header);
    long getDataOffset(char* header);
    long getBitmapWidth(char* headerInfo);
    long getBitmapHeight(char* headerInfo);
    int getBitsPerPixel(char* headerInfo);
    long getImageSize(char* headerInfo);
    long getNColors(char* headerInfo);
    long read32_headerInfo(char* headerInfoPos);
    int read16_headerInfo(char* headerInfoPos);
    long read32(char* ptr);
    int read16(char* ptr);

};