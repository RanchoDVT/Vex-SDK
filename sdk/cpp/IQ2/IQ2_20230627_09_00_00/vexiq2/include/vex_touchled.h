/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2017, All rights reserved.               */
/*                                                                            */
/*    Module:     vex_touchled.h                                              */
/*    Author:     James Pearman                                               */
/*    Created:    7 July 2017                                                 */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VEX_LED_CLASS_H
#define   VEX_LED_CLASS_H

/*-----------------------------------------------------------------------------*/
/** @file    vex_touchled.h
  * @brief   IQ Touch led device class header
*//*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------*/
/** @brief Touch led device class                                              */
/*-----------------------------------------------------------------------------*/
namespace vex {
  class touchled : public device {
      
      public:
        /**
         * @brief Creates a new touchled sensor object on the port specified in the parameter.
         * @param port index to the brain port.
        */
        touchled( int32_t index );  
        ~touchled();
    
        bool            installed();

        /**
         * @brief Gets the value of the touchled sensor.
         * @return Returns an integer that represents whether the touchled is pressed of not
         */
        int32_t         value();

        /**
         * @brief Turn on the led in the touchled sensor.
         * @param color The color of the led
         * @param brightness The brightness for the led
         */
        void            on( colorType color, uint32_t brightness = 100 );

        /**
         * @brief Turn on the led in the touchled sensor.
         * @param hue The hue of the led
         * @param brightness The brightness for the led
         */
        void            on( uint32_t hue, uint32_t brightness = 100 );

        /**
         * @brief Turn on the led in the touchled sensor.
         * @param red The red value of the led
         * @param green The green value of the led
         * @param blue The blue value of the led
         * @param brightness The brightness for the led
         */
        void            on( uint8_t red, uint8_t green, uint8_t blue, uint32_t brightness = 100 );

        /**
         * @brief Turn on the led in the touchled sensor.
         * @param color vex::color specifying the color of the led
         * @param brightness The brightness for the led
         */
        void            on( vex::color color, uint32_t brightness = 100 );

        /**
         * @brief Turn off the led in the touchled sensor.
         */
        void            off( void );

        /**
         * @brief Turn on the led in the touchled sensor with specified color and current brightness.
         * @param color The color of the led
         */
        void            setColor( colorType color );

        /**
         * @brief Turn on the led in the touchled sensor with specified color and current brightness..
         * @param color vex::color specifying the color of the led
         */
        void            setColor( vex::color color );

        /**
         * @brief Sets the default fade time for the touchled sensor.
         * @param setting The type of fade the touchled will use, slow, fast or off
         */
        void            setFade( fadeType setting );

        /**
         * @brief Turn on the led in the touchled sensor, or change current brightness.
         * @param brightness The brightness for the led
         */
        void            setBrightness( uint32_t brightness );
        
        /**
         * @brief Set the led in the touchled sensor as blinking.
         * @param color The color of the led
         * @param onTime The time the led should remain on in seconds
         * @param offTime The time the led should remain off in seconds
         */
        void            setBlink( colorType color, double onTime = 0.25, double offTime = 0.25 );

        /**
         * @brief Set the led in the touchled sensor as blinking.
         * @param hue The hue of the led
         * @param onTime The time the led should remain on in seconds
         * @param offTime The time the led should remain off in seconds
         */
        void            setBlink( uint32_t hue, double onTime = 0.25, double offTime = 0.25 );

        /**
         * @brief Set the led in the touchled sensor as blinking.
         * @param color A vex::color specifying the color of the led
         * @param onTime The time the led should remain on in seconds
         * @param offTime The time the led should remain off in seconds
         */
        void            setBlink( vex::color color, double onTime = 0.25, double offTime = 0.25 );

        /**
         * @brief Get the pressed status of the touchled device.
         * @return Returns the state of the touchled device. If it is pressed it will return a one. If unpressed, it will return a zero.
         */
        bool            pressing();

        /**
         * @brief Calls a function when the touchled is pressed.
         * @param callback A reference to a function.
         */
        void            pressed( void (* callback)(void) );
        
        /**
         * @brief Calls a function when the touchled is released.
         * @param callback A reference to a function.
         */
        void            released( void (* callback)(void) );
      
      private:
        uint8_t         _red;
        uint8_t         _green;
        uint8_t         _blue;
        uint8_t         _brightness;
         
        ledState        _state;

        enum class tEventType {
          EVENT_PRESSED  = 1,
          EVENT_RELEASED = 2
        };
      
        void            _setBrightness( uint32_t brightness );
        void            _setColor( uint32_t rgb );
        void            _setBlink( double onTime, double offTime  );
        uint32_t        _colorToRgb( colorType color );
        uint32_t        _hueToRgb( uint32_t hue );
  };
};

#endif // VEX_LED_CLASS_H