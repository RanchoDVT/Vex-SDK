/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2017, All rights reserved.               */
/*                                                                            */
/*    Module:     vex_colorsensor.h                                           */
/*    Author:     James Pearman                                               */
/*    Created:    7 July 2017                                                 */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VEX_COLORSENSOR_CLASS_H
#define   VEX_COLORSENSOR_CLASS_H

/*-----------------------------------------------------------------------------*/
/** @file    vex_colorsensor.h
  * @brief   Color sensor device class header
*//*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------*/
/** @brief IQ Color sensor device class                                        */
/*-----------------------------------------------------------------------------*/
namespace vex {
  class colorsensor : public device {
      
      public:
        /**
         * @brief Creates a new color sensor object on the port specified in the parameter.
         * @param port index to the brain port.
        */
        colorsensor( int32_t index );  
        ~colorsensor();
    
        bool            installed();
        
        /**
         * @brief Gets the value of the color sensor.
         * @return Returns an integer that represents the hue the color sensor has detected.
         */
        int32_t         value();

        /**
         * @brief Gets the name of the detected color.
         * @return Returns a colorType that represents the name of the closest color detected to red, green or blue.
         */
        colorType       colorname3();

        colorType       colorname12();

        /**
         * @brief Gets the name of the detected color.
         * @return Returns a colorType that represents the name of the closest color detected to twelve possible value.
         */
        colorType       colorname() {
            return colorname12();
        }

        /**
         * @brief Gets the detected color as a fully saturated vex::color
         * @return Returns a vex::color object that represents the hue of the closest color detected to ten possible values.
         */
        vex::color      color();

        /**
         * @brief Gets the hue detected by the color sensor.
         * @return Returns an integer that represents the hue the color sensor has detected.
         */
        int32_t         hue();

        /**
         * @brief Gets the brightness value detected by the color sensor.
         * @return Returns an integer that represents the brightness value the color sensor has detected.
         */
        int32_t         brightness( bool bRaw = false );

        /**
         * @brief Check to see if an object is detected by the color sensor.
         * @return Returns a boolean that represents whether an object has been detected.
         */
        bool            isNearObject();

        /**
         * @brief Check to see if the color sensor is detecting a color.
         * @return Returns a boolean that represents whether the color has been detected.
         */
        bool            detects( colorType color );

        /**
         * @brief Check to see if the color sensor is detecting a vex::color.
         * @return Returns a boolean that represents whether the color has been detected.
         */
        bool            detects( vex::color color );

        /**
         * @brief Calls a function when the color sensor proximity sensor detects an object.
         * @param callback A reference to a function.
         */
        void            objectDetected( void (* callback)(void) );
                        
        /**
         * @brief Turns the led on the color sensor on or off.
         */
        void            setLight( ledState state );
        void            setLight( int32_t intensity, percentUnits units = percentUnits::pct );

      private:
        enum class tEventType {
          EVENT_OBJECT   = 1,
        };
        
        uint8_t         _eventId_1;
        uint8_t         _lastrgb;
        uint8_t         _lasthue;
        void            pollColors( void );
  };
};

#endif // VEX_COLORSENSOR_CLASS_H