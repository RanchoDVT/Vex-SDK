/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2017-2020, All rights reserved.          */
/*                                                                            */
/*    Module:     vex_controller.h                                            */
/*    Author:     James Pearman                                               */
/*    Created:    20 May 2020                                                 */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VEX_CONTROLLER_CLASS_H
#define   VEX_CONTROLLER_CLASS_H

/*-----------------------------------------------------------------------------*/
/** @file    vex_controller.h
  * @brief   IQ controller class header
*//*---------------------------------------------------------------------------*/

namespace vex {
  /** 
   * @brief Use the controller class to get values from the remote controller as well as write to the controller's screen.
   */
  class controller {
    private:
      // copy if the controller id when this class was instantiated
      controllerType		_controllerId;
      // internal device id for this controller
      int32_t           _index;
      
      int32_t value( IQ_ControllerIndex channel );

    protected:
      int32_t _getIndex();
      
    public:

      /** 
       * @brief Creates a new controller object.
       */
      controller();
      ~controller();

      bool installed();

    private:
      // bit masks for events
      enum class tEventType {
        EVENT_L_UP_PRESSED     = 0,
        EVENT_L_UP_RELEASED    = 1,
        EVENT_L_DN_PRESSED     = 2,
        EVENT_L_DN_RELEASED    = 3,
        
        EVENT_R_UP_PRESSED     = 4,
        EVENT_R_UP_RELEASED    = 5,
        EVENT_R_DN_PRESSED     = 6,
        EVENT_R_DN_RELEASED    = 7,
        
        EVENT_E_UP_PRESSED     = 8,
        EVENT_E_UP_RELEASED    = 9,
        EVENT_E_DN_PRESSED     = 10,
        EVENT_E_DN_RELEASED    = 11,

        EVENT_F_UP_PRESSED     = 12,
        EVENT_F_UP_RELEASED    = 13,
        EVENT_F_DN_PRESSED     = 14,
        EVENT_F_DN_RELEASED    = 15,

        EVENT_G_PRESSED        = 16,
        EVENT_G_RELEASED       = 17,
        EVENT_H_PRESSED        = 18,
        EVENT_H_RELEASED       = 19,

        EVENT_A_CHANGED        = 24,
        EVENT_B_CHANGED        = 25,
        EVENT_C_CHANGED        = 26,
        EVENT_D_CHANGED        = 27
      };

      enum class tButtonType {
        kButtonLUp = 0,
        kButtonLDown,
        kButtonRUp,
        kButtonRDown,
        kButtonEUp,
        kButtonEDown,
        kButtonFUp,
        kButtonFDown,
        kButtonG,
        kButtonH,

        kButtonUndefined
      };
    /** 
     * @brief Use the button class to get values from the controller's buttons.
     */
    public:
      class button {
        private:
          tButtonType  _id;
          controller   *_parent;
          tEventType _buttonToPressedEvent() const;
          tEventType _buttonToReleasedEvent() const;
          
        public:
          button() : _id( tButtonType::kButtonUndefined), _parent(NULL) {};
          button( const tButtonType id, controller *parent ) : _id( id ), _parent(parent) {};
          ~button() {};
          /**
           * @brief Sets the function to be called when the button is pressed.
           * @param callback A reference to a function.
           */
          void     pressed( void (* callback)(void) ) const;

          /**
           * @brief Sets the function to be called when the button is released.
           * @param callback A reference to a function.
           */
          void     released( void (* callback)(void) ) const;

          /**
           * @brief Gets the status of a button.
           * @return Returns a Boolean value based on the pressed states of the button. If the button is pressed it will return true.
           */
          bool     pressing( void ) const;        

          //mevent  PRESSED   = { (uint32_t)_parent->_getIndex(), (uint32_t)_buttonToPressedEvent()  };
          //mevent  RELEASED  = { (uint32_t)_parent->_getIndex(), (uint32_t)_buttonToReleasedEvent()  };
      };
      
    public:
      const button  ButtonLUp    = button( tButtonType::kButtonLUp   , this );
      const button  ButtonLDown  = button( tButtonType::kButtonLDown , this );
      const button  ButtonRUp    = button( tButtonType::kButtonRUp   , this );
      const button  ButtonRDown  = button( tButtonType::kButtonRDown , this );
      const button  ButtonEUp    = button( tButtonType::kButtonEUp   , this );
      const button  ButtonEDown  = button( tButtonType::kButtonEDown , this );
      const button  ButtonFUp    = button( tButtonType::kButtonFUp   , this );
      const button  ButtonFDown  = button( tButtonType::kButtonFDown , this );
      const button  ButtonL3     = button( tButtonType::kButtonG     , this );
      const button  ButtonR3     = button( tButtonType::kButtonH     , this );

    private:
      enum class tAxisType {
        kAxisA = 0,
        kAxisB,
        kAxisC,
        kAxisD,
        
        kAxisUndefined
      };
      
      
    public:
      /** 
       * @brief Use the axis class to get values from one of the controller's joysticks
       */
      class axis {
        private:
          tAxisType  _id;
          controller   *_parent;
          tEventType _joystickToChangedEvent() const;
          
        public:
          axis() : _id( tAxisType::kAxisUndefined), _parent(NULL) {};
          axis( const tAxisType id, controller *parent ) : _id( id ), _parent(parent) {};
          ~axis() {};
          
          /**
           * @brief Sets the function to be called when the joystick axis value changes.
           * @param callback A reference to a function.
           */
          void     changed( void (* callback)(void) ) const;

          /**
           * @brief Gets the value of the joystick axis on a scale from -127 to 127.
           * @return Returns an integer that represents the value of the joystick axis.
           */
          int32_t  value( void ) const;

          /**
           * @brief Gets the position of the joystick axis on a scale from -100 to 100.
           * @return Returns an integer that represents the position of the joystick axis as defined by the unit in the parameter.
           * @param units (Optional) The type of unit that will be returned. By default, this parameter is a percentage.
           */        
          int32_t  position( percentUnits units = percentUnits::pct ) const;        

          //mevent  CHANGED   = { (uint32_t)_parent->_getIndex(), (uint32_t)_joystickToChangedEvent()  };
      };
      
     
    public:
      const axis  AxisA = axis( tAxisType::kAxisA, this );
      const axis  AxisB = axis( tAxisType::kAxisB, this );
      const axis  AxisC = axis( tAxisType::kAxisC, this );
      const axis  AxisD = axis( tAxisType::kAxisD, this );      
  };
};

#endif  // VEX_CONTROLLER_CLASS_H