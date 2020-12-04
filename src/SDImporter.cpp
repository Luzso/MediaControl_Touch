#include "SDImporter.h"


SDImporter::SDImporter(){

    bool began = SD.begin(BUILTIN_SDCARD);

    if(began){
        Serial.println("SD Card setup on internal card.\n");

        File root = SD.open("/");
        this->printDirectory(root, 0);
    }
    else{
        Serial.println("Unable to start the SD Card reader library.");
    }

}

BMP SDImporter::getBitmapFile(String* filename){

    File file;
    if(tryGetFile(filename, &file)){
        
        Serial.println("Found bitmap file.");
        Serial.println("Loading image data...");

        // Header 
        int hdrNBytes = 14;
        char hdrBf[hdrNBytes]; // 14 bytes in header
        if(file.available() > 0){
            file.readBytes(hdrBf, hdrNBytes);
            int filesize = this->getBitmapFileSize(hdrBf);
            Serial.println("Filesize: " + String(filesize) + " Bytes.");
        }
        else{
            Serial.println("No available header data.");
        }

        // HeaderInfo
        BMP retBMP;
        int hdrInfoNBytes = 40;
        char hdrInfoBf[hdrInfoNBytes];
        if(file.available() > 0){
            Serial.println("Reading file header info.");
            int nBytes = file.readBytes(hdrInfoBf, hdrInfoNBytes);
            Serial.println("Read " + String(nBytes) + " bytes.");
            retBMP.width = this->getBitmapWidth(hdrInfoBf);
            retBMP.height = this->getBitmapHeight(hdrInfoBf);

            Serial.println("BMP Width: " + String(retBMP.width));
            Serial.println("BMP Height: " + String(retBMP.height));
        }

    }
    else{
        Serial.println("Unable to load bitmap file.");
    }
}

bool SDImporter::tryGetFile(String* filename, File* file){

    Serial.println("Looking for bitmap file: " + *filename);
    const char* c_filename = filename->c_str();
    if(SD.exists(c_filename)){
        *file = SD.open(c_filename);

        return true;
    }
    else{
        Serial.println("Specified file doesn't exist");
        Serial.println(c_filename);
        return false;
    }
    
}

// Offsets from http://www.ece.ualberta.ca/~elliott/ee552/studentAppNotes/2003_w/misc/bmp_file_format/bmp_file_format.htm
long SDImporter::getBitmapFileSize(char* header){
    static int offset = 0x2;
    return read32(header + offset);
}


long SDImporter::getBitmapWidth(char* headerInfo){
    static int offset = 0x12 - 14;
    return read32(headerInfo + offset);
}


long SDImporter::getBitmapHeight(char* headerInfo){
    static int offset = 0x16 - 14;
    return read32(headerInfo + offset);
}


long SDImporter::read32(char* ptr){
    return ptr[0] | (ptr[1] << 8L) | (ptr[2] << 16L) | (ptr[3] << 24L);
}


void SDImporter::printDirectory(File dir, int numTabs){
    File entry; 
    while (entry = dir.openNextFile()) {

        if (! entry) {
        // no more files
            break;
        }

        for (uint8_t i = 0; i < numTabs; i++) {
            Serial.print('\t');
        }

        Serial.print(entry.name());

        if (entry.isDirectory()) {
            Serial.println("/");
            printDirectory(entry, numTabs + 1);
        } 
        else {

            // files have sizes, directories do not
            Serial.print("\t\t");
            Serial.println(entry.size(), DEC);
        }

        entry.close();

  }
}
