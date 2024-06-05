/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2017, All rights reserved.               */
/*                                                                            */
/*    Module:     vex_sonar.h                                                 */
/*    Author:     James Pearman                                               */
/*    Created:    7 July 2017                                                 */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VEX_SONAR_CLASS_H
#define   VEX_SONAR_CLASS_H

/*-----------------------------------------------------------------------------*/
/** @file    vex_sonar.h
  * @brief   IQ Sonar sensor device class header
*//*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------*/
/** @brief Sonar sensor device class                                           */
/*-----------------------------------------------------------------------------*/
namespace vex {
  class sonar : public device {
      
      public:
        /**
         * @brief Creates a new sonar sensor object on the port specified in the parameter.
         * @param port index to the brain port.
        */
        sonar( int32_t index );  
        ~sonar();
    
        bool            installed();

        /**
         * @brief Gets the value of the sonar sensor.
         * @return Returns an integer that represents the distance to the largest object in mm
         */
        int32_t         value();

        // settings
        void            setMaximum( double distance, distanceUnits units );

        /**
         * @brief Gets the value of the sonar sensor.
         * @return Returns an integer that represents the unit value specified by the parameter of the sonar sensor. 
         * @param units The measurement unit for the sonar device.
         */
        double          distance( distanceUnits units );

        /**
         * @brief Gets an object is present in front of the sonar sensor
         * @return Returns a boolean that will be true if the sonar sensor is detecting an object.
         */
        bool            foundObject();    

        /**
         * @brief Calls a function when the sonar detect an object.
         * @param callback A reference to a function.
         */
        void            objectDetected( void (* callback)(void) );

        /**
         * @brief Calls a function when the sonar value changes.
         * @param callback A reference to a function.
         */
        void            changed( void (* callback)(void) );
      
        // action

      private:
        uint8_t         _eventId_1;
        uint32_t        _maxdistance;
        uint32_t        _mindistance;
        uint32_t        _distance;

        enum class tEventType {
          EVENT_OBJECT   = 1,
          EVENT_CHANGED  = 2
        };
      
        void            setMinimum( double distance, distanceUnits units );
        void            setFilter( uint32_t value );
        void            setBrightnessThreshold( uint32_t value );
        
        uint32_t        distanceToRaw( double distance, distanceUnits units );
        double          rawToDistance( uint32_t raw, distanceUnits units );
  };
};

#endif // VEX_SONAR_CLASS_H