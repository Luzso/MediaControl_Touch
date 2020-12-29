#include "PanelGUI.h"
#include "MyTools.h"

#define CS_PIN 21
#define DC_PIN 20
#define RST_PIN 255 // 3.3V
#define SCLK_PIN 14
#define MOSI_PIN 7
#define MISO_PIN 12

#define TCKL_PIN 0
#define TCS_PIN 0
#define TDIN_PIN 0
#define DOUT_PIN 0
#define IRQ_PIN 0

#define ROTATION 3 // Horizontal

#define FONT_HEIGHT_WIDTH_RATIO 1.3333f



PanelGUI::PanelGUI(){
    
    this->initGraphics();
   
}   

void PanelGUI::initGraphics(){
    this->monitor = new ILI9488_t3(CS_PIN, DC_PIN, RST_PIN, MOSI_PIN, SCLK_PIN, MISO_PIN);
    this->monitor->begin();
    //this->monitor->setFrameBuffer(this->frame_buffer);
    //this->monitor->useFrameBuffer(true);
    this->monitor->setRotation(ROTATION);
    this->setSaveFont(Arial_12_Bold);
    // Test
    this->monitor->setTextColor(ILI9488_CYAN);
    this->setDefaultBackgroundColor(ILI9488_BLACK);
    this->clearScreen();

}

void PanelGUI::clearScreen(){

    this->monitor->fillScreen(backgroundColor);
    this->updateScreen_d();
}

void PanelGUI::setDefaultBackgroundColor(uint16_t color){

    this->backgroundColor = color;

}

void PanelGUI::drawBitmap(int x, int y, String filename){

    Serial.println("Drawing Bitmap");

    SDImporter sdImporter;
    BMP bmp = sdImporter.readBMPFile(&filename);
    Serial.print("File size: " + String(sizeof(bmp.file)));

    uint16_t palette[bmp.nColors];
    this->getColorsFromFile(&bmp, palette);
    
    uint8_t pixelBuffer[BLOCK_SIZE] = {};
    uint8_t flippedBufferVertical[BLOCK_SIZE];

    int idrow = 0;
    int nRead = 0;
    int iBlock = 0;
    static int bytesPerRow = 480 * bmp.bitsPerPixel / 8;
    while(bmp.file.available() > 0){
        
        // Info on read data
        int nGetBytes = (BLOCK_SIZE / bytesPerRow) * bytesPerRow; // Find max number of rows that fits within buffer size.
        nRead = bmp.getChunk(pixelBuffer, nGetBytes);
        int nRowsRead = nRead / bytesPerRow; // Number of rows retrieved
        
        Serial.println("Read n bytes1: " + String(nRead));

        // Reverse row order since BMP file y-axis is flipped
        int bufferSize = sizeof(pixelBuffer) / sizeof(pixelBuffer[0]);
        Serial.println("nRows: " + String(nRowsRead));
        
        Serial.println("Read n bytes2: " + String(nRead));
        
        //tools::flipBufferVertical(pixelBuffer, flippedBufferVertical, nRowsRead, bmp.width, bmp.bitsPerPixel);
        
        Serial.println("Read n bytes3: " + String(nRead));

        // Draw image in block from the bottom and up
        this->monitor->writeRectNBPP(x, y + bmp.height - (nRowsRead + idrow), bmp.width, nRowsRead, bmp.bitsPerPixel, pixelBuffer, palette);

        Serial.println("Read n bytes4: " + String(nRead));

        /*
        this->monitor->writeRectNBPP(x, y + idrow , bmp.width, nRowsRead, bmp.bitsPerPixel, pixelBuffer, palette);
*/
        idrow += nRowsRead;
    }
}



void PanelGUI::getColorsFromFile(BMP* bmpFile, uint16_t* rgbPalette){
        for(int idxColorOffset = 0; idxColorOffset < bmpFile->nColors; idxColorOffset++){
        uint16_t tempColor = CL(bmpFile->gbrColors[idxColorOffset*4 + 2], bmpFile->gbrColors[idxColorOffset*4 + 0], bmpFile->gbrColors[idxColorOffset*4 + 1]);
        //Serial.println("Saved color: " + String(tempColor) );
        //Serial.print(String(bmpFile->gbrColors[idxColorOffset*4 + 2]) + ", " + String(bmpFile->gbrColors[idxColorOffset*4 + 0]) + ", " + String(bmpFile->gbrColors[idxColorOffset*4 + 1]) + "\n\n");
        *(rgbPalette + idxColorOffset) = tempColor;
    }
}

// BUTTON GRAPHICS
void PanelGUI::drawButtonSquare(int x, int y, int width, int height, bool selected, bool update){
    if( x + width <= SCREEN_WIDTH && y + height <= SCREEN_HEIGHT){
        this->clearRect(x, y, width, height);

        uint16_t color = ILI9488_CYAN;
        this->monitor->drawRect(x, y, width, height, color);

        int margin = 3;
        uint16_t selectedColor = ILI9488_NAVY;
        this->monitor->fillRect(x + margin, y + margin, width - margin*2, height - margin*2, selectedColor);

        if(update)
            this->updateScreen_d();
    }
    else{
        this->drawError(buttonsquareError);
    }
}

void PanelGUI::drawCrossHair(int x, int y, uint16_t color, bool doUpdate){
    int outerWidth = 20;
    int outerHeight = 20;

    int rectStartX = x - outerWidth / 2;
    int rectStartY = y - outerHeight / 2;
    this->clearRect(rectStartX, rectStartY, outerWidth, outerHeight);

    this->monitor->drawRect(rectStartX, rectStartY, outerWidth, outerHeight, color);
    this->monitor->drawLine(x - outerWidth / 4, y, x + outerWidth /4, y, color);
    this->monitor->drawLine(x, y - outerHeight / 4, x, y + outerHeight / 4, color);

    if(doUpdate)
        this->updateScreen_d();
}

// TEXT EDITING

void PanelGUI::setSaveFont(const ILI9341_t3_font_t& font){
    this->monitor->setFont(font);
    this->currentFont = font;
}

ILI9341_t3_font_t PanelGUI::getFont(){
    return this->currentFont;
}

FontSize PanelGUI::getFontSize(){
    // Parse the font 
    FontSize size;
    size.width = this->currentFont.bits_width;
    size.height = currentFont.cap_height;

    return size;
}


void PanelGUI::writeInBox_boundaries(String text, int xStart, int xEnd, int yStart, int yEnd, bool doCenter, TextboxBackground background, bool update){
    int width = xEnd - xStart;
    int height = yEnd - yStart;

    this->writeInBox_sizes(text, xStart, yStart, width, height, doCenter, background, update);
}

void PanelGUI::writeInBox_sizes(String text, int x, int y, int width, int height, bool doCenter, TextboxBackground background, bool update){

    FontSize size = this->getFontSize();
    int numChars = text.length();

    int xOrigin = 0;
    int yOrigin = 0;
    int textWidth = size.height/FONT_HEIGHT_WIDTH_RATIO*numChars;
    int textHeight = size.height;
    if(x >= 0 && y >= 0 && x + width - 1 <= SCREEN_WIDTH && y + height - 1 <= SCREEN_HEIGHT){
        if(doCenter){
            xOrigin = width/2 - textWidth / 2.0;
            yOrigin = height/2 - textHeight / 2.0;
        }
        xOrigin += x;
        yOrigin += y;
    }
    else{
        this->drawError(textError);
    }
    if(background.useDefaultBackground)
        this->clearRect(xOrigin, yOrigin, textWidth, textHeight + 3); // +3 to account for commas
    else
        this->monitor->fillRect(xOrigin, yOrigin, textWidth, textHeight, background.color);

    monitor->setCursor(xOrigin, yOrigin);
    this->monitor->print(text);

    if(update)
        this->updateScreen_d();

}

void PanelGUI::clearRect(int x, int y, int width, int height, bool doUpdate){
    this->monitor->fillRect(x, y, width, height, this->backgroundColor);

    if(doUpdate){
        this->updateScreen_d();
        this->drawDebug();
    }
}

void PanelGUI::updateScreen_d(){
    this->monitor->updateScreen();
    //this->monitor->freeFrameBuffer();
}

void PanelGUI::drawError(Error error){
    int width = 5;
    int height = 5;
    int x = SCREEN_WIDTH - width;
    int y =SCREEN_HEIGHT - height;

    this->monitor->setCursor(x, y);
    this->monitor->fillRect(x, y, width, height, ILI9488_RED);
    this->monitor->updateScreen();
}


void PanelGUI::drawDebug(){
    int width = 5;
    int height = 5;
    int x = SCREEN_WIDTH - width;
    int y =SCREEN_HEIGHT - height*2;

    this->monitor->setCursor(x, y);
    this->monitor->fillRect(x, y, width, height, ILI9488_GREEN);
    this->monitor->updateScreen();
}

