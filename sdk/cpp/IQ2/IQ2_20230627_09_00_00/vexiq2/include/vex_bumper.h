/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2017, All rights reserved.               */
/*                                                                            */
/*    Module:     vex_bumper.h                                                */
/*    Author:     James Pearman                                               */
/*    Created:    7 July 2017                                                 */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VEX_BUMPER_CLASS_H
#define   VEX_BUMPER_CLASS_H

/*-----------------------------------------------------------------------------*/
/** @file    vex_bumper.h
  * @brief   IQ2 Bumper switch device class header
*//*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------*/
/** @brief Bumper switch device class                                          */
/*-----------------------------------------------------------------------------*/
namespace vex {
  class bumper : public device {
      
      public:
        /**
         * @brief Creates a new bumper object on the port specified in the parameter.
         * @param port index to the brain port.
        */
        bumper( int32_t index );  
        ~bumper();
    
        bool            installed();
   
        /**
         * @brief Gets the value of the bumper device.
         * @return Returns an integer that represents the value of the bumper device. 
         */
        int32_t   value();

        /**
         * @brief Get the pressed status of the bumper device.
         * @return Returns the state of the bumper device. If it is pressed it will return a one. If unpressed, it will return a zero.
         */
        int32_t   pressing() { return value(); };

        /**
         * @brief Calls a function when the bumper switch is pressed.
         * @param callback A reference to a function.
         */
        void      pressed( void (* callback)(void) );

        /**
         * @brief Calls a function when the bumper switch is released.
         * @param callback A reference to a function.
         */
        void      released( void (* callback)(void) );
      
      private:
        enum class tEventType {
          EVENT_PRESSED  = 1,
          EVENT_RELEASED = 2
        };
  };
};

#endif // VEX_BUMPER_CLASS_H