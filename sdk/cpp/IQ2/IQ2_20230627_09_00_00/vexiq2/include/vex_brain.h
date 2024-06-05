/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2020, All rights reserved.               */
/*                                                                            */
/*    Module:     vex_brain.h                                                 */
/*    Author:     James Pearman                                               */
/*    Created:    6 April 2020                                                */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VEX_BRAIN_CLASS_H
#define   VEX_BRAIN_CLASS_H

#include "vex_timer.h"

/*-----------------------------------------------------------------------------*/
/** @file    vex_brain.h
  * @brief   IQ2 brain class header
*//*---------------------------------------------------------------------------*/

namespace vex {
  /** 
    * @brief Use the brain class to see battery information, SD card information, or write to the Screen.
  */
  class brain {
    private:

    protected:
      static int32_t _getIndex();
            
    public:
      /** 
        * @brief Creates a new brain object.
      */
      brain();
      ~brain();

    private:
      enum class tEventType {
        EVENT_UP_PRESSED     = 1,
        EVENT_UP_RELEASED    = 2,
        EVENT_DOWN_PRESSED   = 4,
        EVENT_DOWN_RELEASED  = 8,
        EVENT_CHECK_PRESSED  = 16,
        EVENT_CHECK_RELEASED = 32
      };

    public:
      /** 
       * @brief Use the button class to get values from the brain's buttons.
      */
      class button {
        private:
          uint8_t  _id;
          
        public:
          button() : _id( -1 ) {};
          button( const int id ) : _id( id ) {};
          ~button() {};
          
          /**
           * @brief Sets the function to be called when the button is pressed.
           * @param callback A reference to a function.
          */
          void    pressed( void (* callback)(void) );
          /**
           * @brief Sets the function to be called when the button is released.
           * @param callback A reference to a function.
          */
          void    released( void (* callback)(void) );
          /**
           * @brief Sets the function to be called when the button is released.
           * @param callback A reference to a function.
          */
         bool     pressing( void );        
      };
      
      /**
       * @brief A button that represents the Up/Left button on the brain
       */
      button       buttonUp    = button(0);
      button      &buttonLeft  = buttonUp;
      
      /**
       * @brief A button that represents the Down/Right button on the brain
       */
      button       buttonDown  = button(1);
      button      &buttonRight = buttonDown;

      /**
       * @brief A button that represents the Check button on the brain
       */
      button       buttonCheck = button(2);


/*----------------------------------------------------------------------------*/
      /** 
        * @brief Use this class to write or draw to the brain's LCD screen.
      */      
      class lcd {
        private:
          int16_t   _row;
          int16_t   _maxrows;
          int16_t   _rowheight;
          
          int16_t   _col;
          int16_t   _maxcols;
          int32_t   _colwidth;

          int32_t   _penWidth;

          uint32_t  _textbase;

          char      _textStr[128];

          int32_t   rowToPixel( int32_t row );
          int32_t   colToPixel( int32_t col );
          
          bool      _transparent;
          
          int       _origin_x;
          int       _origin_y;

          #define   FONT_MONO_CELL_WIDTH   10    
          #define   FONT_MONO_CELL_HEIGHT  20
          #define   FONT_MONO_CELL_BASE     4         
            
          // Not sure what to do with this yet
          // does not make much sense with proportional font 
          // but we need to specify a location somehow
          #define   FONT_PROP_CELL_WIDTH   10    
          #define   FONT_PROP_CELL_HEIGHT  20
          #define   FONT_PROP_CELL_BASE     4         
          
        public:
          lcd();
          ~lcd() {};
                  
          /** 
           * @brief Sets the cursor to the row and column number set in the parameters.
           * @param row Sets the row number for where the cursor is placed.
           * @param col Sets the column number for where the cursor is placed. 
          */
          void     setCursor( int32_t row, int32_t col ); 

          /** 
           * @brief Sets the font type to be displayed on the Screen that is determined by the parameter.
           * @param font The type of font that is displayed.
          */
          void     setFont( fontType font );

          /** 
           * @brief Sets the pen's width.
           * @param width This represents the width of the pen when drawing. A larger width equals a wider pen stroke.
          */
          void     setPenWidth( uint32_t width ); 

          /** 
           * @brief Sets the origin of the screen to the parameters defined in the function.
           * @param x The x location of the origin.
           * @param y The y location of the origin.
          */
          void     setOrigin( int32_t x, int32_t y );

          /** 
           * @brief An integer that tracks the current cursor position's column, starting at 1.
           * @return Returns an integer that tracks the current cursor position's column, starting at 1.
          */
          int32_t  column();

          /** 
           * @brief An integer that tracks the current cursor position's row, starting at 1.
           * @return Returns an integer that tracks the current cursor position's row, starting at 1.
          */
          int32_t  row();

          /** 
           * @brief Sets the color of the pen to a specified color.
           * @param color A color unit where colors can be defined as names.
          */          
          void     setPenColor( const color& color );

          /** 
           * @brief Sets the color of the pen to a specified color using a hex value.
           * @param color A hexadecimal value that represents color.
          */ 
          void     setPenColor( const char *color );

          /** 
           * @brief Sets the color of the pen to a specified color.
           * @param hue The integer represents the hue of the color.
          */ 
          void     setPenColor( int hue ); 

          /** 
           * @brief Sets the default fill color for any subsequent draw command.
           * @param color In a color unit, colors can be defined as names.
          */          
          void     setFillColor( const color& color );

          /** 
           * @brief Sets the default fill color for any subsequent draw command..
           * @param color A hexadecimal value that represents color.
          */ 
          void     setFillColor( const char *color ); 

          /** 
           * @brief Sets the default fill color for any subsequent draw command.
           * @param hue The integer represents the hue of the color.
          */
          void     setFillColor( int hue );

          /** 
           * @brief Gets the width in pixels of the given string.
           * @return Returns an integer that represents the width of the string in pixels.
          */
          int32_t  getStringWidth( const char *cstr );

          /** 
           * @brief Gets the height in pixels of the given string.
           * @return Returns an integer that represents the height of the string in pixels.
          */
          int32_t  getStringHeight( const char *cstr );

          /** 
           * @brief Prints a number, string, or Boolean.
           * @param format This is a reference to a char format that prints the value of variables.
           * @param ... A variable list of parameters to insert into format string.
          */          
          void     print( const char *format, ... );
          void     print( char *format, ... );

          /** 
           * @brief Prints a number, string, or Boolean at an x, y cursor location.
           * @param x The x-coordinate at which to print a message on the screen.
           * @param y The y-coordinate at which to print a message on the screen.
           * @param format A reference to a char format to print the value of variables.
           * @param ... A variable list of parameters to insert into format string.
           * @notes this uses cursor location rather than pixel locati0n as on the V5
           * it's shouthand for using setCursor followed by print.
          */
          void     printAt( int32_t x, int32_t y, const char *format, ... );

          /** 
           * @brief Prints a number, string, or Boolean at an x, y cursor location.
           * @param x The x pixel location where the print should start
           * @param y The y pixel location where the print should start
           * @param bOpaque If set to false, the print will be transparent.
           * @param format A reference to a char format to print the value of variables.
           * @param ... A variable list of parameters to insert into format string. 
           * @notes this uses cursor location rather than pixel locati0n as on the V5
           * it's shouthand for using setCursor followed by print.
          */
          void     printAt( int32_t x, int32_t y, bool bOpaque, const char *format, ... );

          /** 
           * @brief Clears the whole Screen to a default color or otherwise specified color.
          */          
          void     clearScreen( void );

          /** 
           * @brief Clears the whole Screen to a default color or otherwise specified color.
           * @param color In a color unit, colors can be defined as names. 
          */
          void     clearScreen( const color& color );

          /** 
           * @brief Clears the whole Screen to a default color or otherwise specified color.
           * @param color A hexadecimal value that represents color.
          */
          void     clearScreen( const char *color );

          /** 
           * @brief Clears the whole Screen to a default color or otherwise specified color.
           * @param hue The integer represents the hue of the color.
          */
          void     clearScreen( int hue );

          /** 
           * @brief Clears the specified line and sets it to a specified color.
           * @param number The integer sets the line that is to be cleared.
           * @param color A color unit where colors can be defined as names.
          */          
          void     clearLine( int number, const color& color );

          /** 
           * @brief Clears the specified line and sets it to a specified color.
           * @param number The integer sets the line that is to be cleared.
           * @param color A hexadecimal value that represents color.
          */
          void     clearLine( int number, const char *color );

          /** 
           * @brief Clears the specified line and sets it to a specified color.
           * @param number The integer sets the line that is to be cleared.
           * @param hue An integer that represents the hue of the color.
          */
          void     clearLine( int number, int hue );

          /** 
           * @brief Clears the specified line and sets it to the background color.
           * @param number The integer sets the line that is to be cleared.
          */
          void     clearLine( int number );

          /** 
           * @brief Clears the rest of the line from where the cursor is located. 
          */
          void     clearLine( void );

          /** 
           * @brief Clears the rest of the line from where the cursor is located and then moves the cursor to the beginning of the next line.
           * (actually not, just moves cursor at the moment as that was what the V5 does, we will address later)
          */
          void     newLine( void );

          /** 
           * @brief Draws a single pixel to the screen in the specified x and y location.
           * @param x The x location of where to draw the pixel.
           * @param y The y location of where to draw the pixel.
          */
          void     drawPixel( int x, int y );

          /** 
           * @brief Draws a line connecting the two specified points in the parameters.
           * @param x1 The x location of the first point.
           * @param y1 The y location of the first point.
           * @param x2 The x location of the second point.
           * @param y2 The y location of the second point.
          */
          void     drawLine( int x1, int y1, int x2, int y2 );

          /** 
           * @brief Draws a rectangle using the specified points and attributes set in the parameters. Fills the rectangle with the current pen and fill color.
           * @param x The x-coordinate at which the left edge of the rectangle will be drawn on the screen.
           * @param y The y-coordinate at which the top edge of the rectangle will be drawn on the screen.
           * @param width The width of the rectangle.
           * @param height The height of the rectangle.
          */
          void     drawRectangle( int x, int y, int width, int height );

          /** 
           * @brief Draws a rectangle using the specified points and attributes set in the parameters. Fills the rectangle with the color specified.
           * @param x The x-coordinate at which the left edge of the rectangle will be drawn on the screen.
           * @param y The y-coordinate at which the top edge of the rectangle will be drawn on the screen.
           * @param width The width of the rectangle.
           * @param height The height of the rectangle.
           * @param color A color unit where colors can be defined as names.
          */
          void     drawRectangle( int x, int y, int width, int height, const color& color );

          /** 
           * @brief Draws a rectangle using the specified points and attributes set in the parameters. Fills the rectangle with the color specified.
           * @param x The x-coordinate at which the left edge of the rectangle will be drawn on the screen.
           * @param y The y-coordinate at which the top edge of the rectangle will be drawn on the screen.
           * @param width The width of the rectangle.
           * @param height The height of the rectangle.
           * @param color A hexadecimal value that represents color.
          */
          void     drawRectangle( int x, int y, int width, int height, const char *color );

          /** 
           * @brief Draws a rectangle using the specified points and attributes set in the parameters. Fills the rectangle with the color specified.
           * @param x The x-coordinate at which the left edge of the rectangle will be drawn on the screen.
           * @param y The y-coordinate at which the top edge of the rectangle will be drawn on the screen.
           * @param width The width of the rectangle.
           * @param height The height of the rectangle. 
           * @param hue The color of the rectangle.
          */
          void     drawRectangle( int x, int y, int width, int height, int hue );

          /** 
           * @brief Draws a circle using the specified points and attributes set in the parameters. Fills the circle with the current pen and fill color.
           * @param x The central x location of the circle.
           * @param y The central y location of the circle.
           * @param radius Sets the radius of the circle to be drawn on the Screen.
          */
          void     drawCircle( int x, int y, int radius );

          /** 
           * @brief Draws a circle using the specified points and attributes set in the parameters. Fills the circle with the color specified.
           * @param x The central x location of the circle.
           * @param y The central y location of the circle.
           * @param radius Sets the radius of the circle to be drawn on the Screen.
           * @param color A color unit where colors can be defined as names.
          */
          void     drawCircle( int x, int y, int radius, const color& color );

          /** 
           * @brief Draws a circle using the specified points and attributes set in the parameters. Fills the circle with the color specified.
           * @param x The central x location of the circle.
           * @param y The central y location of the circle.
           * @param radius Sets the radius of the circle to be drawn on the Screen.
           * @param color A hexadecimal value that represents color.
          */
          void     drawCircle( int x, int y, int radius, const char *color );

          /** 
           * @brief Draws a circle using the specified points and attributes set in the parameters. Fills the circle with the color specified.
           * @param x The central x location of the circle.
           * @param y The central y location of the circle.
           * @param radius Sets the radius of the circle to be drawn on the Screen.
           * @param hue An integer that represents the hue of the color.
          */
          void     drawCircle( int x, int y, int radius, int hue );

          /** 
           * @brief Sets the clip region for screen output.  Only effects the current thread.
           * @param x The x-coordinate at the left edge of the clip region.
           * @param y The y-coordinate at the top edge of the clip region.
           * @param width The width of the clip region.
           * @param height The height of the clip region. 
          */
          void     setClipRegion( int x, int y, int width, int height );

          /**
           * @brief Draws an image on the screen using the contents of the memory buffer.
           * @param buffer A pointer to a buffer containing image data in bmp format.
           * @param x The x-coordinate at which the left edge of the image will be drawn.
           * @param y The y-coordinate at which the top edge of the image will be drawn.
           * @param bufferLen The size of the source image buffer in bytes.
           * @return Returns true if the image was successfully drawn on the screen.
           * @details
           *  This function draws an image on the screen using the contents of a buffer into
           *  which BMP raw data has already been read.  The contents may have come from a
           *  file on the SD card or have been statically declared in the code.  The image can be
           *  no larger than 1/4 of the IQ Screen, that is, a maximum of 80 pixels wide by 64 pixels high.
           *  The top/left corner of the image is placed at the coordinates given by x and y, these can
           *  be negative if desired.
          */
          bool     drawImageFromBuffer( uint8_t  *buffer, int x, int y, int bufferLen );

          /**
           * @brief Draws an image on the screen using the contents of the memory buffer.
           * @param buffer A pointer to a buffer containing raw 32 bit per pixel image data.
           * @param x The x-coordinate at which the left edge of the image will be drawn.
           * @param y The y-coordinate at which the top edge of the image will be drawn.
           * @param width The width of the image.
           * @param height The height of the image. 
           * @return Returns true if the image was successfully drawn on the screen.
           * @details
           *  This funtion draws an image on the screen using the contents of a buffer into which
           *  raw RGB pixels have been placed.  Each pixel is represented by a 16 bit value. The buffer contains
           *  pixels for the first row of the image immediately followed by pixels for the second row and so on.
           *  The image should be no larger than the IQ Screen, that is, a maximum of 160 pixels wide by 128 pixels high.
           *  The top/left corner of the image is placed at the coordinates given by x and y, these can
           *  be negative if desired.
          */
          bool     drawImageFromBuffer( uint32_t *buffer, int x, int y, int width, int height );

          /**
           * @brief Draws an image on the screen using a file on the SD Card as the source.
           * @param name The name of the image, it must have a ".bmp" extension.
           * @param x The x-coordinate at which the left edge of the image will be drawn.
           * @param y The y-coordinate at which the top edge of the image will be drawn.
           * @return Returns true if the image was successfully drawn on the screen.
           * @details
           *  This funtion draws an image on the screen using the contents of a file on an SD Card.
           *  The file should be no larger than 6K bytes and must have a ".bmp" extension.
           *  The image should be no larger than 1/4 the IQ Screen, that is, a maximum of 80 pixels wide by 64 pixels high.
           *  The top/left corner of the image is placed at the coordinates given by x and y, these can
           *  be negative if desired.
          */
          bool     drawImageFromFile( const char *name, int x, int y );

          /**
           * @brief Synchronizes drawing with screen refresh
           * @returns true
          */
          bool     render();

        private:
          void     _setPenColor( uint32_t rgb ); 
          void     _setFillColor( uint32_t rgb ); 
          void     _clearScreen( uint32_t rgb );
          void     _clearLine( int number, uint32_t rgb );
          void     _drawRectangle( int x, int y, int width, int height, uint32_t rgb );
          void     _drawCircle( int x, int y, int radius, uint32_t rgb );

          enum class tImageBufferType {
            kImageBufferTypeUnknown = 0,
            kImageBufferTypeBmp,
            kImageBufferTypePng
          };
            
          tImageBufferType _validateImageBuffer( uint8_t *buffer );

          uint32_t  webColorToRgb( const char *color );      
          uint32_t  hueToRgb( uint32_t color );          

          bool      render( bool bVsyncWait, bool bRunScheduler );
          void      waitForRefresh();
      };

      /** 
       * @brief Use the Screen class to write or draw to the screen.
       */
      lcd         Screen;

      /** 
       * @brief Gets the value of the timer in the units specified.
       * @param units The unit of time that will be returned.
       * @return Returns a double that represents the value of the timer.
      */
      double      timer( timeUnits units );

      /** 
       * @brief Resets the timer to zero.
      */
      void        resetTimer();

      /** 
       * @brief Sets the timer to a value and time unit.
       * @param value The value that the timer is set to.
       * @param units The unit of time that will be returned.
      */
      void        setTimer( double value, timeUnits units );

      /** 
       * @brief Use the Timer class to obtain the system time.
       */
      vex::timer  Timer;

/*----------------------------------------------------------------------------*/

      /** 
       * @brief Use the battery class to see information about the battery.
      */      
      class battery {
        public:
          battery() {};
          ~battery() {};

          /** 
           * @brief Gets the battery capacity.
           * @return Returns an integer that represents the batteries capacity in the units specified by the parameter.
           * @param units (Optional) The type of unit that will be returned. By default, this parameter is a percentage. 
          */
          uint16_t  capacity( percentUnits units = percentUnits::pct );

          /** 
           * @brief Gets the battery voltage.
           * @return Returns a double that represents the batteries voltage in the units specified by the parameter.
           * @param units The unit of voltage to be returned.
          */
          double    voltage( voltageUnits units = voltageUnits::volt );

          /** 
           * @brief Gets the battery current.
           * @return Returns a double that represents the batteries current in the units specified by the parameter.
           * @param units The type of current to be returned.
          */
          double    current( currentUnits units = currentUnits::amp );
      };
      
      /** 
       * @brief This is the Brain's instance of the battery.
       */
      battery     Battery;

      /** 
        * @brief Use the SD Card class to load or save files on your SD card.
      */      
      class sdcard {
        public:
          sdcard();
          ~sdcard();
          
          /** 
           * @brief Gets the state of the SD card
           * @return Returns true if the SD card is inserted. Returns false if there is not an SD card inserted.
          */
          bool    isInserted();
          
          /** 
           * @return Returns the number of bytes read from the file.
           * @brief Loads a file from the SD card.
           * @param name The name of the file.
           * @param buffer Pointer to a buffer for file data.
           * @param len The length of the buffer in bytes. Usually set to the max length of the buffer.
          */
          int32_t loadfile(const char *name, uint8_t *buffer, int32_t len );

          /** 
           * @brief Saves a file to the SD card.
           * @return Returns the number of bytes saved to the file.
           * @param name The name of the file.
           * @param buffer Pointer to a buffer with file data.
           * @param len The length of the buffer in bytes. Usually set to the max length of the buffer.
          */
          int32_t savefile(const char *name, uint8_t *buffer, int32_t len );

          /** 
           * @brief Appends data to an existing file.
           * @return Returns the number of bytes saved to the file.
           * @param name The name of the file.
           * @param buffer Pointer to a buffer with file data.
           * @param len The length of the buffer in bytes. Usually set to the max length of the buffer.
          */
          int32_t appendfile(const char *name, uint8_t *buffer, int32_t len );
          
          /** 
           * @brief get the size in bytes of the named file
           * @return size of file in bytes
           * @param name The name of the file.
          */
          int32_t size(const char *name);

          /** 
           * @brief check if the named file exists
           * @return true if the file exists
           * @param name The name of the file.
          */
          bool    exists(const char *name);
      };
      /** 
       * @brief This is the instance of the SD card class.
       */
      sdcard      SDcard;

      /** 
       * @brief play one of the predefined sounds on the brain
       */
      void        playSound( soundType sound );

      /** 
       * @brief play one of the predefined tones on the brain
       */
      void        playTone( int32_t note, uint32_t volume, uint32_t duration );
      /** 
       * @brief play a note in the given octave on the brain
       */
      void        playNote( int32_t octave, int32_t note );
      /** 
       * @brief play a note in the given octave on the brain and wait for the given time before returning
       */
      void        playNote( int32_t octave, int32_t note, int32_t ms );
      /** 
       * @brief turn sound off on the brain
       */
      void        soundOff( void );
  };
};

#endif // VEX_BRAIN_CLASS_H