#if defined(ARDUINO) && ARDUINO >= 100
  #include "arduino.h"
#else
  #include "WProgram.h
#endif

//Library version:1.1
#include "LCDWriter.h"
#include "LiquidCrystal_I2C.h"

LCDWriterClass::LCDWriterClass()
{
   memset(_blank_line, ' ', LCD_COLUMNS);
   memset(_rows, 0, LCD_ROWS * (LCD_COLUMNS+1));
  _dirty = false;
}

void LCDWriterClass::Init()
{
  _lcd = new LiquidCrystal_I2C(0x27, LCD_COLUMNS, LCD_ROWS);  
  _lcd->init();
  _lcd->backlight();
  Clear();
}

// change a row.  First clear it and then copy msg into it.
void LCDWriterClass::WriteRow(int row, const char *message)
{
   memset(_rowAddress(row), ' ', LCD_COLUMNS);
   memcpy(_rowAddress(row), message, strlen(message));
   _dirty = true;
}

// writes to bottom row... scrolls rest of rows up... (except top row)
void LCDWriterClass::WriteLn(const char *message)
{
   memcpy(_rowAddress(1), _rowAddress(2), LCD_COLUMNS);
   memcpy(_rowAddress(2), _rowAddress(3), LCD_COLUMNS);
   WriteRow(3, message);
   _dirty = true;
}

// Redraw if dirty
void LCDWriterClass::Render()
{
  if(_dirty)
  {
    for(int row = 0; row < LCD_ROWS;row++)
    {
      _lcd->setCursor(0, row);
      _lcd->print(_rowAddress(row));
    }
    _dirty = false;
  }
}


void LCDWriterClass::Clear()
{
    _lcd->clear();
}

// singleton
LCDWriterClass LCDWriter;
