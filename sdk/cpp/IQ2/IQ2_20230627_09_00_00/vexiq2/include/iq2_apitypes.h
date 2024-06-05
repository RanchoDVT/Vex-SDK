/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2019, All rights reserved.               */
/*                                                                            */
/*    Module:     iq2_apitypes.h                                              */
/*    Author:     James Pearman                                               */
/*    Created:    26 June 2019                                                */
/*                                                                            */
/*    Revisions:  V0.1                                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef IQ_APITYPES_H_
#define IQ_APITYPES_H_

#include "stdint.h"
#include "stdbool.h"

/*-----------------------------------------------------------------------------*/
/** @file    iq2_apitypes.h
  * @brief   Header for IQ API - type definitions
*//*---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/** @brief   scheduler task states - do not modify, from to rmtasks.h         */
/*----------------------------------------------------------------------------*/
// States a task can have
typedef enum _rmTaskStates {
    kTaskUndefined = 0,
    kTaskInitializing,
    kTaskRunning,
    kTaskTimerWait,
    kTaskStop,
    kTaskSemaphoreWait,
    kTaskSemaphoreRunPending,
    kTaskSuspended,

    kTaskInitializeSuspended,
    kTaskRunningSuspended,
    kTaskTimerWaitSuspended,
    kTaskSemaphoreWaitSuspended,
  
    kTaskComplete = 99
} rmTaskStates;

/*----------------------------------------------------------------------------*/
/** @brief   structure to hold semaphore - do not modify, from to rmtasks.h   */
/*----------------------------------------------------------------------------*/
typedef struct _rmSemaphore {
    uint8_t nOwningTask;
    uint8_t nLockCount;
} rmSemaphore;

/*----------------------------------------------------------------------------*/
/** @brief      Code signature                                                */
/*----------------------------------------------------------------------------*/
/** @details
 *   The first 16 bytes of a user code binary should contain the user code
 *   signature.  For simple user code programs this will be created by the
 *   startup code in the runtime library, certain types of user code,
 *   for example a virtual machine, may override the default settings to cause
 *   the IQ system code to enable custom functionality yet TBD.
 *
 *   to override the default use a definition like this in one of the user
 *   code source files.
 *
 *   __attribute__ ((section (".boot_data"))) vcodesig vexCodeSig =
 *   { IQ_SIG_MAGIC, 
 *     IQ_SIG_TYPE_USER, 
 *     IQ_SIG_OWNER_VEX, 
 *     IQ_SIG_OPTIONS_NONE
 *   };
 *
 *   IQ_SIG_MAGIC must be set, other fields and their behavior are TBD
 *
 *   vexCodeSig is defined as "weak" and this definition will override it.
 */
typedef struct  __attribute__ ((packed)) _vcodesig {
  uint32_t  magic;                        // Magic, must be 'VXQ2' 0x32515658 le
  uint32_t  type;                         // program type
  uint32_t  owner;                        // program originator
  uint32_t  options;                      // program options
} vcodesig ;

//
#define V5_SIG_MAGIC            0x35585658  //XVX5
#define IQ_SIG_MAGIC            0x32515658  //XVQ2
#define EX_SIG_MAGIC            0x45585658  //XVXE
#define IQ_SIG_TYPE_USER        0
#define IQ_SIG_OWNER_SYS        0
#define IQ_SIG_OWNER_VEX        1
#define IQ_SIG_OWNER_PARTNER    2
#define IQ_SIG_OPTIONS_NONE     0
#define IQ_SIG_OPTIONS_EXIT     (1 << 1)   // Kill threads when main exits

#define IQ_CODE_SIG( type, owner, options ) \
vcodesig  vexCodeSig  __attribute__ ((section (".boot_data"))) = \
 { IQ_SIG_MAGIC, type, owner, options };

/*----------------------------------------------------------------------------*/
/** @brief      Structures used by system time functions                      */
/*----------------------------------------------------------------------------*/

// Time
struct time {
  uint8_t   ti_hour;                      /// Hours 
  uint8_t   ti_min;                       /// Minutes
  uint8_t   ti_sec;                       /// Seconds
  uint8_t   ti_hund;                      /// Hundredths of seconds
};

// Time
struct date {
  uint16_t  da_year;                      /// Year - 1980
  uint8_t   da_day;                       /// Day of the month
  uint8_t   da_mon;                       /// Month (1 = Jan)
};
// DEVICE IDs

/*----------------------------------------------------------------------------*/
/** @brief      IQ Device type definitions                                    */
/*----------------------------------------------------------------------------*/
// TODO
// Do we really want to include the declare.h file ??
typedef enum {
  kDeviceTypeNoSensor        = 0,
  kDeviceTypeMotorSensor     = 2,
  kDeviceTypeLedSensor       = 3,
  kDeviceTypeRgbSensor       = 4,
  kDeviceTypeBumperSensor    = 5,
  kDeviceTypeGyroSensor      = 6,
  kDeviceTypeSonarSensor     = 7,
  kDeviceTypeRadioSensor     = 8,
  kDeviceTypeTetherSensor,   // 9
  kDeviceTypeBrainSensor,    // 10
  kDeviceTypeVisionSensor    = 11,
  kDeviceTypePneumaticSensor = 15,
  kDeviceTypeOpticalSensor   = 16,
  kDeviceTypeDistanceSensor  = 19,

  kDeviceTypeImuSensor       = 0x70, // TODO
    
  kDeviceTypeGenericSensor   = 0x80,
  kDeviceTypeGenericSerial   = 0x81,
  kDeviceTypeGenericDigital  = 0x82,
  kDeviceTypeUndefinedSensor = 0xFF
} IQ_DeviceType;

// Opaque pointer to IQ device type structure
typedef struct _IQ_Device * IQ_DeviceT;

// Some ports will be virtual, some physical
#define IQ_MAX_DEVICE_PORTS   32
typedef IQ_DeviceType IQ_DeviceTypeBuffer[IQ_MAX_DEVICE_PORTS];

typedef enum  {
    kButtonNone     = 0x00,
    kButtonSelect   = 0x01,
    kButtonExit     = 0x02,
    kButtonUp       = 0x04,
    kButtonDown     = 0x08
} IQBrainButtons;
  
/*----------------------------------------------------------------------------*/
/** @brief      IQ Gyro definitions                                           */
/*----------------------------------------------------------------------------*/
typedef enum {
  gyroLowSensitivity          = 1,      // 62.5  degrees per second
  gyroNormalSensitivity       = 3,      //  250  degrees per second
  gyroHighSensitivity         = 6,      // 2000  degrees per second
} IQGyroSensitivity;

typedef enum {
  gyroCalibrateSamplesOff     = 0,
  gyroCalibrateSamples64      = 6,
  gyroCalibrateSamples128     = 7,
  gyroCalibrateSamples256     = 8,
  gyroCalibrateSamples512     = 9,
  gyroCalibrateSamples1024    = 10,
  gyroCalibrateSamples2048    = 11,
  gyroCalibrateSamples4096    = 12,
  gyroCalibrateSamples8192    = 13,
  gyroCalibrateSamples16384   = 14,
  gyroCalibrateSamples32768   = 15
} IQGyroCalibrateSamples;

/*----------------------------------------------------------------------------*/
/** @brief      IQ RGB definitions                                            */
/*----------------------------------------------------------------------------*/
typedef enum {
  colorTypeUninitialized,
  colorTypeGrayscale_Ambient,
  colorTypeGrayscale_Reflected,
  colorTypeRGB_12Colors_Ambient,
  colorTypeRGB_12Colors_Reflected,
  colorTypeRGB_Hue_Ambient,
  colorTypeRGB_Hue_Reflected,
  colorTypeRGB_Raw_Ambient,
  colorTypeRGB_Raw_Reflected
} IORgbColorTypes;

/*----------------------------------------------------------------------------*/
/** @brief      IQ Motor definitions                                          */
/*----------------------------------------------------------------------------*/
// Most of this is still TBD and is currently based on the IQ implementation
typedef enum  {
    kMotorControlModeOFF         = 0,     /// Motor is off and in coast mode
    kMotorControlModeBRAKE       = 1,     /// Motor is off and in brake mode
    kMotorControlModeHOLD        = 2,     /// Motor is holding at current position
    kMotorControlModeSERVO       = 3,     /// Motor is in "Servo" mode. Move to position and hold at that position
    kMotorControlModePROFILE     = 4,     /// Motor moves to set position and stops.
    kMotorControlModeVELOCITY    = 5,     /// Motor is unlimited movement at set 'velocity'
    kMotorControlModeUNDEFINED   = 6      /// 
} IQMotorControlMode;

typedef enum _IQ_MotorBrakeMode {
    kMotorBrakeModeCoast       = 0,     /// Motor will coast when stopped
    kMotorBrakeModeBrake       = 1,     /// Motor will brake when stopped
    kMotorBrakeModeHold        = 2      /// Motor will hold position when stopped
} IQMotorBrakeMode;

typedef enum  {
    kMotorEncoderDegrees         = 0,     /// degrees Encoder Count Mode
    kMotorEncoderRotations       = 1,     /// rotations Encoder Count Mode
    kMotorEncoderCounts          = 2      /// Raw Encoder Count Mode
} IQMotorEncoderUnits;

typedef enum _IQMotorGearset {
    kMotorGearSet_1  = 0,                   /// No gearsets on IQ, just for V5 compatibity
    kMotorGearSet_2  = 1,
    kMotorGearSet_3  = 2
} IQMotorGearset;

// This is for 36:1 gear set
#define IQ_MOTOR_COUNTS_PER_ROT  1800.0

/*----------------------------------------------------------------------------*/
/** @brief      IQ Vision sensor definitions                                  */
/*----------------------------------------------------------------------------*/

// subject to change
typedef enum {
  kVisionModeNormal      = 0,
  kVisionModeMixed       = 1,
  kVisionModeLineDetect  = 2,
  kVisionTypeTest        = 3
} IQVisionMode;

typedef enum {
  kVisionTypeNormal      = 0,
  kVisionTypeColorCode   = 1,
  kVisionTypeLineDetect  = 2
} IQVisionBlockType;

// White balance
typedef enum {
  kVisionWBNormal       = 0,
  kVisionWBStart        = 1,
  kVisionWBManual       = 2
} IQVisionWBMode;

// LED control, from IQ or by the vision sensor
typedef enum {
  kVisionLedModeAuto    = 0,
  kVisionLedModeManual  = 1
} IQVisionLedMode;

// Wifi mode
typedef enum {
  kVisionWifiModeOff    = 0,
  kVisionWifiModeOn     = 1
} IQVisionWifiMode;

// signature should be 40 bytes and is the same data
// as sent to the vision sensor

// if bit0 is now set you know signature is read back
#define VISION_SIG_FLAG_STATUS    (1<<0) 

typedef struct __attribute__ ((__packed__)) _IQ_DeviceVisionSignature {
    uint8_t             id;
    //uint8_t             flags;
    //uint8_t             pad[2];
    float               range;
    int32_t             uMin;
    int32_t             uMax;
    int32_t             uMean;
    int32_t             vMin;
    int32_t             vMax;
    int32_t             vMean;
    uint32_t            mRgb;
    uint32_t            mType;
} IQ_DeviceVisionSignature;

typedef struct __attribute__ ((__packed__)) _IQ_DeviceVisionObject {
    uint16_t            signature;        /// block signature
    IQVisionBlockType   type;             /// block type
    uint16_t            xoffset;          /// left side of block
    uint16_t            yoffset;          /// top of block
    uint16_t            width;            /// width of block
    uint16_t            height;           /// height of block
    uint16_t            angle;            /// angle of CC block in 0.1 deg units
} IQ_DeviceVisionObject;

// Color structure, used for LED and white balance
typedef struct __attribute__ ((__packed__)) _IQ_DeviceVisionRgb {
    uint8_t             red;
    uint8_t             green;
    uint8_t             blue;
    uint8_t             brightness;    /// not used yet
} IQ_DeviceVisionRgb;

/*----------------------------------------------------------------------------*/
/** @brief      IQ IMU sensor definitions                                     */
/*----------------------------------------------------------------------------*/
// Not all of these may be used or valid on IQ2
//
// Quaternion data from IMU
typedef struct __attribute__ ((__packed__)) _IQ_DeviceImuQuaternion {
    double              a;
    double              b;
    double              c;
    double              d;
} IQ_DeviceImuQuaternion;

// Attitude data from IMU
typedef struct __attribute__ ((__packed__)) _IQ_DeviceImuAttitude {
    double              pitch;  // x
    double              roll;   // y
    double              yaw;    // z
} IQ_DeviceImuAttitude;

// Raw data from IMU
typedef struct __attribute__ ((__packed__)) _IQ_DeviceImuRaw {
    double              x;
    double              y;
    double              z;
    double              w;
} IQ_DeviceImuRaw;

// native is same direction as 3wire gyro
// clockwise is positive
typedef enum _IQImuHeadingnMode {
    kImuHeadingNative     = 0x00,
    kImuHeadingIQ         = 0x01
} _IQImuHeadingnMode;

// Orientation mode
typedef enum _IQImuOrientationMode {
    kImuOrientationZUp    = 0x00,
    kImuOrientationZDown  = 0x10,
    kImuOrientationXUp    = 0x20,
    kImuOrientationXDown  = 0x30,
    kImuOrientationYUp    = 0x40,
    kImuOrientationYDown  = 0x50,
    kImuOrientationAuto   = 0x80
} IQImuOrientationMode;

// Quaternion mode
typedef enum _IQImuQuaternionMode {
    kImuQuaternionProcessed = 0x000,
    kImuQuaternionRaw       = 0x100
} IQImuQuaternionMode;

/*----------------------------------------------------------------------------*/
/** @brief      IQ Optical sensor definitions                                 */
/*----------------------------------------------------------------------------*/
// for raw crgb data
typedef struct _IQ_DeviceOpticalRaw {
    uint16_t     clear;
    uint16_t     red;
    uint16_t     green;
    uint16_t     blue;
} IQ_DeviceOpticalRaw;

typedef struct _IQ_DeviceOpticalRgb {
    double       red;
    double       green;
    double       blue;
    double       brightness;
} IQ_DeviceOpticalRgb;

// gesture data
typedef struct _IQ_DeviceOpticalGesture {
    uint8_t      udata;
    uint8_t      ddata;
    uint8_t      ldata;
    uint8_t      rdata;
    uint8_t      type;
    uint8_t      pad;
    uint16_t     count;
    uint32_t     time;
} IQ_DeviceOpticalGesture;

/*----------------------------------------------------------------------------*/
/** @brief   structure holding image info - used by bmp/png read code         */
/*----------------------------------------------------------------------------*/
// data must point to suitable buffer now
typedef struct __attribute__ ((__packed__)) _iq2_image {
    uint16_t  width;
    uint16_t  height;
    uint32_t *data;
    uint32_t *p;
} iq2_image;

#define SYSTEM_DISPLAY_WIDTH       		160
#define SYSTEM_DISPLAY_HEIGHT      		128
// Height of the IQ2 status bar
// offset added to all graphics drawing
#define STATUS_BAR_HEIGHT              20

/*----------------------------------------------------------------------------*/
/** @brief      IQ SD File system definitions                                 */
/*----------------------------------------------------------------------------*/

// Opaque pointer (FIL *) to file structure
typedef   void          FIL;

// seek flags
// changed, Mar 6 2018 to be more consistent with stdio.h
#define   FS_SEEK_SET     0
#define   FS_SEEK_CUR     1
#define   FS_SEEK_END     2

// file status
#define   FS_FILE_EXIST   1
#define   FS_FILE_DIR     2

// File function return code (FRESULT)
typedef enum {
    FR_OK = 0U,                           /// (0) Succeeded
    FR_DISK_ERR,                          /// (1) A hard error occurred in the low level disk I/O layer
    FR_INT_ERR,                           /// (2) Assertion failed
    FR_NOT_READY,                         /// (3) The physical drive cannot work
    FR_NO_FILE,                           /// (4) Could not find the file
    FR_NO_PATH,                           /// (5) Could not find the path
    FR_INVALID_NAME,                      /// (6) The path name format is invalid
    FR_DENIED,                            /// (7) Access denied due to prohibited access or directory full
    FR_EXIST,                             /// (8) Access denied due to prohibited access
    FR_INVALID_OBJECT,                    /// (9) The file/directory object is invalid
    FR_WRITE_PROTECTED,                   /// (10) The physical drive is write protected
    FR_INVALID_DRIVE,                     /// (11) The logical drive number is invalid
    FR_NOT_ENABLED,                       /// (12) The volume has no work area
    FR_NO_FILESYSTEM,                     /// (13) There is no valid FAT volume
    FR_MKFS_ABORTED,                      /// (14) The f_mkfs() aborted due to any parameter error
    FR_TIMEOUT,                           /// (15) Could not get a grant to access the volume within defined period
    FR_LOCKED,                            /// (16) The operation is rejected according to the file sharing policy
    FR_NOT_ENOUGH_CORE,                   /// (17) LFN working buffer could not be allocated
    FR_TOO_MANY_OPEN_FILES,               /// (18) Number of open files > _FS_SHARE
    FR_INVALID_PARAMETER                  /// (19) Given parameter is invalid
} FRESULT;

/*----------------------------------------------------------------------------*/
/** @brief      IQ2 Controller definitions                                    */
/*----------------------------------------------------------------------------*/

typedef enum _IQ_ControllerIndex {
    kIQControllerAnaLeftX    =   0,
    kIQControllerAnaLeftY,
    kIQControllerAnaRightX,
    kIQControllerAnaRightY,
    kIQControllerAnaSpare1,
    kIQControllerAnaSpare2,

    kIQControllerButtonLU,
    kIQControllerButtonLD,
    kIQControllerButtonRU,
    kIQControllerButtonRD,
    kIQControllerButtonEU,
    kIQControllerButtonED,
    kIQControllerButtonFU,
    kIQControllerButtonFD,
    kIQControllerButtonG,
    kIQControllerButtonH,
    kIQControllerButtonSpare1,
    kIQControllerButtonSpare2,

    kIQControllerButtonSEL,

    kIQControllerBatteryLevel,

    // Used for set
    kIQControllerButtonAll,
    kIQControllerFlags,
    
    kIQControllerBatteryCapacity,
    kIQControllerSignalStrength,
    
    kIQControllerdevStatus = 0x80,         // private
    kIQControllerdevFlags                  // private
} IQ_ControllerIndex;

typedef enum _IQ_ControllerStatus {
    kIQControllerOffline = 0,
    kIQControllerOnline
} IQ_ControllerStatus;

typedef enum _IQ_ControllerId {
    kIQControllerMaster = 0
} IQ_ControllerId;

#ifdef __cplusplus
}
#endif
#endif /* IQ_APITYPES_H_*/
