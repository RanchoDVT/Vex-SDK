/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2017, All rights reserved.               */
/*                                                                            */
/*    Module:     vex_gyro.h                                                  */
/*    Author:     James Pearman                                               */
/*    Created:    7 July 2017                                                 */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VEX_GYRO_CLASS_H
#define   VEX_GYRO_CLASS_H

/*-----------------------------------------------------------------------------*/
/** @file    vex_gyro.h
  * @brief   IQ Gyro sensor device class header
*//*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------*/
/** @brief Gyro sensor device class                                            */
/*-----------------------------------------------------------------------------*/
namespace vex {
  class gyro : public device, public guido {      
      public:
        /**
         * @brief Creates a new gyro object on the port specified in the parameter.
         * @param port index to the brain port.
       */
        gyro( int32_t index, bool calibrate=false, turnType dir = turnType::left );  
        ~gyro();
    
        bool            installed();

        /**
         * @brief Gets the angle of the gyro sensor.
         * @return Returns an integer that represents the angle of the gyro sensor
         */
        int32_t         value();

        /**
         * @brief Gets the angle of the gyro sensor.
         * @return Returns a double that represents the unit value specified by the parameter of the gyro sensor.
         * @param units The measurement unit for the gyro device.
         */
        double          value( rotationUnits units = rotationUnits::deg );
      
        /**
         * @brief Starts recalibration of the gyro.
         * @param value (Optional) Sets the amount of calibration time. By default, this parameter is quick.
         * @param waitForCompletion wait for calibration to complete
         * @motes the IQ startCalibration method will block until calibration is finished.
         */
        bool            startCalibration( gyroCalibrationType value = gyroCalibrationType::calNormal, bool waitForCompletion=true );

        void            calibrate( gyroCalibrationType value = gyroCalibrationType::calNormal, bool waitForCompletion=true  ) {
          startCalibration( value, waitForCompletion );
        }
        // satisfy guido class requirements
        void            calibrate( int32_t value = 1 ) {
          startCalibration( gyroCalibrationType::calNormal, value ? true : false );
        }
        
        /**
         * @brief Returns true while the gyro sensor is performing a requested recalibration, changing to false once recalibration has completed.
         * @return Returns true if gyro is still calibrating.
         */
        bool            isCalibrating();

        /**
         * @brief reset the gyro sensor angle to 0
         */
        void            resetHeading();

        /**
         * @brief reset the gyro sensor rotation to 0
         */
        void            resetRotation();
        
        /**
         * @brief set the gyro sensor angle to angle
         * @param value The new heading for the gyro
         * @param units The rotation unit for the heading
         */
        void            setHeading( double value, rotationUnits units );

        /**
         * @brief set the gyro sensor rotation to angle
         * @param value The new absolute angle for the gyro
         * @param units The rotation unit for the angle
         */
        void            setRotation( double value, rotationUnits units );
      
        /**
         * @brief Gets the angle of the gyro sensor.
         * @return Returns a double that represents the unit value specified by the parameter of the gyro sensor.
         * @param units The measurement unit for the gyro device.
         */
        double          angle( rotationUnits units = rotationUnits::deg );

        /**
         * @brief Gets the angle of the gyro sensor.
         * @return Returns a double that represents the unit value specified by the parameter of the gyro sensor.
         * @param units The measurement unit for the gyro device.
         */
        double          heading( rotationUnits units = rotationUnits::deg );

        /**
         * @brief Gets the absolute angle of the gyro sensor.
         * @return Returns a double that represents the unit value specified by the parameter of the gyro sensor.
         * @param units The measurement unit for the gyro device.
         */
        double          rotation( rotationUnits units = rotationUnits::deg );

        /**
         * @brief Gets the turn rate of the gyro sensor.
         * @return Returns a double that represents the unit value specified by the parameter of the gyro sensor.
         * @param units The measurement unit for the gyro device.
         */
        double          rate( rateUnits units = rateUnits::dps );

        /**
         * @brief Calls a function when the gyro sensor value changes.
         * @param callback A reference to a function.
         */
        void            changed( void (* callback)(void) );

        /**
         * @brief Set direction for positive angles
         * @param dir turnType::right or turnType::left
         */
        void            setTurnType( turnType dir );

        /**
         * @brief Get direction for positive angles
         * @return turnType::right or turnType::left
         */
        turnType        getTurnType();
        
      private:
        enum class tSensitivity {
          low          = 1,      // 62.5  degrees per second
          normal       = 3,      //  250  degrees per second
          high         = 6,      // 2000  degrees per second
        };

        enum class tEventType {
          EVENT_CHANGED  = 2,
          EVENT_POLL     = 4
        };

        int32_t         _absolute;
        int32_t         _value;
        int32_t         _offset_h;
        int32_t         _offset_r;
        tSensitivity    _sensitivity;
        int32_t         _rate;
        bool            _calInit;
      
        void            getAngleAndRate( void );
        bool            calibrationFlagGet( void );
        void            setSensitivity( tSensitivity s );
        double          rawToAngle( int32_t raw, rotationUnits units );
        int32_t         angleToRaw( double angle, rotationUnits units );
  };
};

#endif // VEX_GYRO_CLASS_H