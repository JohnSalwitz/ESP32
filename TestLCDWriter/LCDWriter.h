#ifndef LCD_WRITER
#define LCD_WRITER


#define  LCD_ROWS 4
#define  LCD_COLUMNS 20

class LiquidCrystal_I2C;

class LCDWriterClass
{
public:
    LCDWriterClass();
    void Init();
    void WriteRow(int row, const char *message);
    void WriteLn(const char *message);
    void Render();
    void Clear();

private:
    inline char *_rowAddress(int row) {return &_rows[row * (LCD_COLUMNS+1)];}

    LiquidCrystal_I2C *_lcd;
    char _blank_line[LCD_COLUMNS];
    char _rows[LCD_ROWS * (LCD_COLUMNS+1)];
    bool _dirty;
}

// singleton
extern LCDWriter;

#endif
