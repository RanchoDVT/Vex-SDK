/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2021, All rights reserved.               */
/*                                                                            */
/*    Module:     vex_generic.h                                               */
/*    Author:     James Pearman                                               */
/*    Created:    23 August 2021                                              */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
// Matches IQ generic class with additional features
//
#ifndef   VEX_GENERIC_CLASS_H
#define   VEX_GENERIC_CLASS_H

/*-----------------------------------------------------------------------------*/
/** @file    vex_generic.h
  * @brief   IQ2 generic sensor device class header
*//*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------*/
/** @brief generic sensor device class                                         */
/*-----------------------------------------------------------------------------*/
namespace vex {
  class generic : public device {      
      public:
        /**
         * @brief Creates a new generic sensor object on the port specified in the parameter.
         * @param port index to the brain port.
         * @param addr optional i2c 7 bit address for this sensor.
       */
        generic( int32_t index, int32_t addr = -1 );  
        ~generic();
    
        bool  installed();
        
        /*--------------------------------------------------------------------*/
        //
        // The following methods are for communication with generic devices
        // that conform to the IQ sensor reference spec and have been enumerated
        // by vexos as either generic or user sensors.
        //
        /*--------------------------------------------------------------------*/
        
        /**
         * @brief Gets the firmware version of the generic sensor.
         * @return Returns an integer with version or -1 on error
         */
        int32_t version();
        /**
         * @brief Gets the vendor id of the generic sensor.
         * @return Returns an integer with vendor id or -1 on error
         */
        int32_t vendorId();
        /**
         * @brief Gets the product id of the generic sensor.
         * @return Returns an integer with product id or -1 on error
         */
        int32_t productId();
        
        /**
         * @brief Read 1 byte from the generic sensor.
         * @param  reg the register to read from 
         * @return register value on success, -1 if error
         */
        int32_t readByte( uint8_t reg );
        /**
         * @brief Write 1 byte to the generic sensor.
         * @param  reg the register to write to 
         * @param  value the data to write
         * @return register value on success, -1 if error
         */
        int32_t writeByte( uint8_t reg, uint8_t value );
        
        /**
         * @brief Read 1 word (2 bytes) from the generic sensor.
         * @param  reg the register to read from 
         * @param  bLittleEndian the endianess of the word in the sensor
         * @return register value on success, -1 if error
         */
        int32_t readWord( uint8_t reg, bool bLittleEndian = false );
        /**
         * @brief  Write 1 word (2 bytes) to the generic sensor.
         * @param  reg the register to write to 
         * @param  value the data to write
         * @param  bLittleEndian the endianess of the word in the sensor
         * @return register value on success, -1 if error
         */
        int32_t writeWord( uint8_t reg, uint16_t value, bool bLittleEndian = false );

        /**
         * @brief  Read bytes from the generic sensor.
         * @param  reg the starting register to read from 
         * @param  pBytes pointer to buffer to read into 
         * @param  nLength number of bytes to read
         * @return number of bytes read, < 0 if error
         */
        int32_t readReg( uint8_t reg, uint8_t *pBytes, uint8_t nLength );
        /**
         * @brief  Write bytes to the generic sensor.
         * @param  reg the starting register to write to 
         * @param  pBytes pointer to buffer with data
         * @param  nLength number of bytes to write
         * @return number of bytes written, < 0 if error
         */
        int32_t writeReg( uint8_t reg, uint8_t *pBytes, uint8_t nLength );

        typedef enum _i2cRegType {
          // All sensors have these registers
          kRegAsciiVersion    = 0x00, // 8 bytes
          kRegAsciiVendor     = 0x08, // 8 bytes
          kRegAsciiDeviceId   = 0x10, // 8 bytes

          kRegUserVendorId    = 0x18, // user sensor specific
          kRegUserProductId   = 0x19, // user sensor specific
          
          kRegFirmwareVersion = 0x20,
          kRegDeviceType      = 0x21,
          kRegDeviceId        = 0x22,
          kRegDeviceStatus    = 0x23
        } i2cRegType;

        /*--------------------------------------------------------------------*/
        //
        // The following methods are for communication with generic devices
        // that do not conform to the IQ sensor reference spec and have an I2C
        // address that does not conflict with other sensors on the same bus.
        // raw sensors should not use I2C addresses that may be assigned to IQ
        // devices if sharing the bus with them.
        // (8 bit addresses)
        // 0x60
        // 0x20, 0x22, 0x24
        /*--------------------------------------------------------------------*/
        
        /**
         * @brief  Read bytes from the device.
         * @param  addr the 7 bit i2C address of the device
         * @param  pBytes pointer to buffer to read into 
         * @param  nLength number of bytes to read
         * @return number of bytes read, < 0 if error
         */
        int32_t readRaw( uint8_t addr, uint8_t *pBytes, uint8_t nLength );
        /**
         * @brief  Write bytes to the device.
         * @param  addr the 7 bit i2C address of the device
         * @param  pBytes pointer to buffer with data
         * @param  nLength number of bytes to write
         * @return number of bytes written, < 0 if error
         */
        int32_t writeRaw( uint8_t addr, uint8_t *pBytes, uint8_t nLength );
        /**
         * @brief  Write bytes to the device.
         * @param  addr the 7 bit i2C address of the device
         * @param  pBytes pointer to buffer with tx data
         * @param  nLength number of bytes to write
         * @param  pRxBytes pointer to buffer with rx data 
         * @param  nRxLength number of bytes to read
         * @return number of bytes read, < 0 if error
         */
        int32_t writeReadRaw( uint8_t addr, uint8_t *pBytes, uint8_t nLength, uint8_t *pRxBytes, uint8_t nRxLength );
                
      private:
        uint8_t   _i2c_addr;
  };
};

#endif // VEX_GENERIC_CLASS_H