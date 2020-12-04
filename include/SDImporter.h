#include "SD.h "


struct BMP
{
    long width = 0;
    long height = 0;
    uint8_t data;
};


class SDImporter
{

public:
    SDImporter();

    BMP getBitmapFile(String* filename);
    bool tryGetFile(String* filename, File* file);
    void printDirectory(File dir, int numTabs);
    long getBitmapFileSize(char* header);
    long getBitmapWidth(char* headerInfo);
    long getBitmapHeight(char* headerIn);
    long read32(char* ptr);

};