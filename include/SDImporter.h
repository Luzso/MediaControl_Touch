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
    uint8_t* colors;

    ~BMP(){
        if(colors != NULL)
            delete colors;
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

    void setColors(uint8_t* u8colors, int nColorBytes){

        for(int i = 0; i < nColorBytes; i++){
            Serial.print(String(u8colors[i]) + " ");
        }

        this->colors = new uint8_t(nColorBytes);
        for(int i_colorByte = 0; i_colorByte < nColorBytes; i_colorByte++){
            this->colors[i_colorByte] = u8colors[i_colorByte];
        }

        for(int i = 0; i < nColorBytes; i++){
            Serial.print(String(colors[i]) + " ");
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