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


    int getChunk(uint8_t* buffer, int bufferSize){

        if(this->file.available() > 0){
            int nRead = file.readBytes(buffer, bufferSize);
            Serial.println("In chunk, read bytes: " + String(nRead));
            return nRead;
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