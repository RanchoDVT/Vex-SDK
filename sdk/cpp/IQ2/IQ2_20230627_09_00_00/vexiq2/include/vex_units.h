/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2017, All rights reserved.               */
/*                                                                            */
/*    Module:     vex_units.h                                                 */
/*    Author:     James Pearman                                               */
/*    Created:    5 July 2017                                                 */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VEX_UNITS_H
#define   VEX_UNITS_H

/*-----------------------------------------------------------------------------*/
/** @file    vex_units.h
  * @brief   Header for global units
*//*---------------------------------------------------------------------------*/

namespace vex {
    /**
     @brief The measurement units for percentage values.
    */
    enum class percentUnits {
      /** @brief A percentage unit that represents a value from 0% to 100% */
      pct = 0
    };
    /**
     @brief The measurement units for time values.
    */
    enum class timeUnits {
      /** @brief A time unit that is measured in seconds.*/
      sec,
      /** @brief A time unit that is measured in milliseconds.*/
      msec
    };
    /**
     @brief The measurement units for current values.
    */
    enum class currentUnits {
      /** @brief A current unit that is measured in amps.*/
      amp
    };
    /**
     @brief The measurement units for voltage values.
    */
    enum class voltageUnits {
      /** @brief A voltage unit that is measured in volts.*/
      volt,
      /** @brief A voltage unit that is measured in millivolts.*/
      mV
    };
    /**
     @brief The measurement units for power values.
    */
    enum class powerUnits {
      /** @brief A power unit that is measured in watts.*/
      watt
    };
    /**
     @brief The measurement units for torque values.
    */
    enum class torqueUnits {
      /** @brief A torque unit that is measured in Newton Meters.*/
      Nm,
      /** @brief A torque unit that is measured in Inch Pounds.*/
      InLb
    };
    /**
     @brief The measurement units for rotation values.
    */
    enum class rotationUnits {
      /** @brief A rotation unit that is measured in degrees.*/
      deg,
      /** @brief A rotation unit that is measured in revolutions.*/
      rev,
      /** @brief A rotation unit that is measured in raw data form.*/
      raw = 99
    };
    /**
     @brief The measurement units for velocity values.
    */
    enum class velocityUnits {
      /** @brief A velocity unit that is measured in percentage.*/
      pct = (int)percentUnits::pct,
      /** @brief A velocity unit that is measured in rotations per minute.*/
      rpm,
      /** @brief A velocity unit that is measured in degrees per second.*/
      dps
    };
    /**
     @brief The measurement units for distance values.
    */
    enum class distanceUnits {
      /** @brief A distance unit that is measured in millimeters.*/
      mm,
      /** @brief A distance unit that is measured in inches.*/
      in,
      /** @brief A distance unit that is measured in centimeters.*/
      cm,
      /** @brief A distance unit that is measured in raw counts.*/
      counts
    };
    /**
     @brief The measurement units for analog values.
    */
    enum class analogUnits {
      /** @brief An analog unit that is measured in percentage.*/
      pct = (int)percentUnits::pct,
      /** @brief An analog unit that is measured in an 8-bit analog value (a value with 256 possible states).*/
      range8bit,
      /** @brief An analog unit that is measured in a 10-bit analog value (a value with 1024 possible states).*/
      range10bit,
      /** @brief An analog unit that is measured in a 12-bit analog value (a value with 4096 possible states).*/
      range12bit,
      /** @brief An analog unit that is measured in millivolts.*/
      mV
    };
    /**
     @brief The measurement units for temperature values.
    */
    enum class temperatureUnits {
      /** @brief A temperature unit that is measured in celsius.*/
      celsius,
      /** @brief A temperature unit that is measured in fahrenheit.*/
      fahrenheit
    };
    
    // Motor related
    /**
     @brief The defined units for direction values.
    */
    enum class directionType {
      /** @brief A direction unit that is defined as forward.*/
      fwd = 0,
      /** @brief A direction unit that is defined as backward.*/
      rev,
      undefined
    };

    /**
     @brief The defined units for turn values.
    */
    enum class turnType {
      /** @brief A turn unit that is defined as left turning.*/
      left,
      /** @brief A turn unit that is defined as right turning.*/
      right
      };
        
    /**
     @brief The defined units for brake values.
    */
    enum class brakeType {
      /** @brief A brake unit that is defined as coast.*/
      coast = kMotorBrakeModeCoast,
      /** @brief A brake unit that is defined as brake.*/
      brake = kMotorBrakeModeBrake,
      /** @brief A brake unit that is defined as hold.*/
      hold  = kMotorBrakeModeHold,
      undefined
    } ;
    /**
     @brief The defined units for gear values.
    */
    enum class gearSetting {
      /** @brief A gear unit that is defined as 1:1 gearing */
      ratio1_1 = kMotorGearSet_1,
      /** @brief A gear unit that is defined as 2:1 gearing */
      ratio2_1 = kMotorGearSet_2,
      /** @brief A gear unit that is defined as 3:1 gearing .*/
      ratio3_1 = kMotorGearSet_3
    };
    
    // Brain/LCD related
    /**
     @brief The defined units for font values.
    */
    enum class fontType {
      /** @brief A font unit that is defined as mono20.*/
      mono20 = 0,
      /** @brief A font unit that is defined as mono30.*/
      mono30,
      /** @brief A font unit that is defined as mono40.*/
      mono40,
      /** @brief A font unit that is defined as mono60.*/
      mono60,
      /** @brief A font unit that is defined as prop20.*/
      prop20,
      /** @brief A font unit that is defined as prop30.*/
      prop30,
      /** @brief A font unit that is defined as prop40.*/
      prop40,
      /** @brief A font unit that is defined as prop60.*/
      prop60,

      // not in spec
      /** @brief A font unit that is defined as mono15.*/
      mono15,
      /** @brief A font unit that is defined as mono12.*/
      mono12
    };          

    /**
     @brief The defined units for controller devices.
    */
    enum class controllerType {
      /** @brief A controller unit defined as a primary controller.*/
      primary = kIQControllerMaster
    };

    /**
     @brief The defined units for inertial sensor axis.
    */
    enum class axisType {
      xaxis,
      yaxis,
      zaxis
    };

    /**
     @brief The defined units for inertial sensor orientation.
    */
    enum class orientationType {
      roll,
      pitch,
      yaw
    };

    /**
     @brief The defined units for distance sensor object size.
    */
    enum class sizeType {
      none,
      small,
      medium,
      large
    };
        
    // color type from IQ SDK          
    enum class colorType {
      none,
      red,
      green,
      blue,
      white,
      yellow,
      orange,
      purple, 
      cyan,
      
      red_violet,
      violet,
      blue_violet,
      blue_green,
      yellow_green,
      yellow_orange,
      red_orange,
      
      black,
      transparent
    };

    // Touchled
    enum class fadeType {
      off,
      slow,
      fast
    };

    enum class gyroCalibrationType {
      calNormal,
      calSlow,
      calExtended
    };

    enum class rateUnits {
      dps,
      rps
    };
        
    enum class ledState {
      off,
      on,
      blink
    };
    
    // These are IQ sounds, will almost certainly change
    enum class soundType {
      siren            =  0,
      wrongWay         =  1,
      wrongWaySlow     =  2,
      fillup           =  3,
      headlightsOn     =  4,
      headlightsOff    =  5,
      tollBooth        =  6,
      alarm            =  7,
      tada             =  8,
      doorClose        =  9,
      ratchet          = 10,
      wrench           = 11,
      siren2           = 12,
      ratchet2         = 13,
      alarm2           = 14,
      powerDown        = 15
      };    

    /**
     @brief The defined units for optical sensor gesture types.
    */
    enum class gestureType {
      none,
      up,
      down,
      left,
      right
    };    

    /**
     @brief The defined types for pneumatic cylinders.
    */
    enum class cylinderType {
      cylinder1 = 0,
      cylinder2 = 1,
      cylinderAll = 0xff
    };
};

#endif // VEX_UNITS_H
