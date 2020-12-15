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

BMP SDImporter::readBMPFile(String* filename){

    BMP retBMP;
    if(tryGetFile(filename, &retBMP.file)){

        // Get all meta data from the file.
        Serial.println("Found bitmap file.");
        Serial.println("Loading image data...");
        long nAvailBytes = retBMP.file.available();
        Serial.println("There are " + String(nAvailBytes) + " available bytes.\n");

        long totalBytesRead = 0;
        // Header 
        int hdrNBytes = 14;
        char hdrBf[hdrNBytes]; // 14 bytes in header
        long dataOffset;
        if(retBMP.file.available() > 0){
            totalBytesRead += retBMP.file.readBytes(hdrBf, hdrNBytes);
            Serial.println("Read " + String(totalBytesRead) + " bytes in total.");
            int filesize = this->getBitmapFileSize(hdrBf);
            dataOffset = this->getDataOffset(hdrBf);
            Serial.println("Filesize: " + String(filesize) + " Bytes.\n");
            Serial.println("Data offset: " + String(dataOffset));
            Serial.println("");
        }
        else{
            Serial.println("No available header data.");
        }

        // HeaderInfo
        int hdrInfoNBytes = 40;
        char hdrInfoBf[hdrInfoNBytes];
        if(retBMP.file.available() > 0){
            Serial.println("Reading file header info.");
            totalBytesRead += retBMP.file.readBytes(hdrInfoBf, hdrInfoNBytes);
            Serial.println("Read " + String(totalBytesRead) + " bytes in total.");
            retBMP.setWidth(this->getBitmapWidth(hdrInfoBf));
            retBMP.setHeight(this->getBitmapHeight(hdrInfoBf));
            retBMP.setBitsPerPixel(this->getBitsPerPixel(hdrInfoBf));
            retBMP.nColors = this->getNColors(hdrInfoBf);
            long imageSize = this->getImageSize(hdrInfoBf);

            Serial.println("BMP Width: " + String(retBMP.width));
            Serial.println("BMP Height: " + String(retBMP.height));
            Serial.println("BMP Bits per Pixel: " + String(retBMP.bitsPerPixel));
            Serial.println("BMP Image size: " + String(imageSize));
            Serial.println("BMP number of colors: " + String(retBMP.nColors));
            Serial.println("");
        }


        // Color map
        // Get pointer to the colors
        int colorInfoNBytes = 4 * retBMP.nColors;
        if(retBMP.file.available() > 0){
            Serial.println("Reading color info.");
            int nColorBytes = retBMP.file.readBytes(retBMP.gbrColors, colorInfoNBytes); // Insert directly in array
            totalBytesRead += nColorBytes;
            Serial.println("Read " + String(nColorBytes) + " bytes in total.");            
        }


        // Reset to beginning of data
        long nSkipAddresses = dataOffset - totalBytesRead;
        if(retBMP.file.available() > 0){
            char nullBf[nSkipAddresses];
            int nSkipped = retBMP.file.readBytes(nullBf, nSkipAddresses);

            Serial.println("Available: " + String(retBMP.file.available()));
            Serial.println("File reset to beginning of data. Skipped bytes: " + String(nSkipped));
        } 
        
    }
    else{
        Serial.println("Unable to load bitmap file.");
    }

    return retBMP;
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

long SDImporter::getDataOffset(char* header){
    static int offset = 0xA;
    return read32(header + offset);
}

long SDImporter::getBitmapWidth(char* headerInfo){
    static int offset = 0x12;
    return read32_headerInfo(headerInfo + offset);
}

long SDImporter::getBitmapHeight(char* headerInfo){
    static int offset = 0x16;
    return read32_headerInfo(headerInfo + offset);
}

int SDImporter::getBitsPerPixel(char* headerInfo){
    static int offset = 0x1C;
    return read16_headerInfo(headerInfo + offset);
}

long SDImporter::getImageSize(char* headerInfo){
    static int offset = 0x22;
    return read32_headerInfo(headerInfo + offset);
}

long SDImporter::getNColors(char* headerInfo){
    static int offset = 0x2E;
    return read32_headerInfo(headerInfo + offset);
}

long SDImporter::read32_headerInfo(char* headerInfoPos){
    return read32(headerInfoPos - 14);
}

int SDImporter::read16_headerInfo(char* headerInfoPos){
    return read16(headerInfoPos - 14);
}

long SDImporter::read32(char* ptr){
    return ptr[0] | (ptr[1] << 8L) | (ptr[2] << 16L) | (ptr[3] << 24L);
}


int SDImporter::read16(char* ptr){
    return ptr[0] | (ptr[1] << 8);
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
