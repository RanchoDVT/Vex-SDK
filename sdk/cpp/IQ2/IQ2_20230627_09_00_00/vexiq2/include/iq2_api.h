/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2019, All rights reserved.               */
/*                                                                            */
/*    Module:     iq2_api.h                                                   */
/*    Author:     James Pearman                                               */
/*    Created:    26 June 2019                                                */
/*                                                                            */
/*    Revisions:  V0.1                                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef IQ_API_H_
#define IQ_API_H_

#include "stdint.h"
#include "stdbool.h"
#include "stdarg.h"

/*-----------------------------------------------------------------------------*/
/** @file    iq2_api.h
  * @brief   Header for IQ2 API
*//*---------------------------------------------------------------------------*/

#include "iq2_apitypes.h"
//#include "iq2_apiuser.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/*    jumptable public API                                                    */
/*----------------------------------------------------------------------------*/
//
// These are the raw jumptable wrapper function prototypes
//
 
 // scheduler
typedef int  (*rmTask_t)          (void);
typedef void (*rmTaskSimple_t)    (void);
typedef int  (*rmTaskArg_t)       (void *);

void                  vexDelay( uint32_t timems );

void                  vexTaskAdd( rmTask_t, int interval, char const *label );
void                  vexTaskAddWithPriority( rmTask_t, int interval, char const *label, int priority );
void                  vexTaskAddSimple( rmTaskSimple_t, int interval, char const *label );
void                  vexTaskAddSimpleWithPriority( rmTaskSimple_t, int interval, char const *label, int priority );
void                  vexTaskStop( rmTask_t );
void                  vexTaskSuspend( rmTask_t );
void                  vexTaskResume( rmTask_t );
void                  vexTaskSuspendCurrent( void );
void                  vexTaskResumeCurrent( void );
void                  vexTaskProgramSuspend( void );
void                  vexTaskProgramResume( void );
int32_t               vexTaskPriorityGet( rmTask_t ) ;
void                  vexTaskPrioritySet( rmTask_t, int32_t priority ) ;
int32_t               vexTasksRun( void );
void                  vexTaskYield( void );
void                  vexTaskCheckTimeslice( void );
int32_t               vexTaskGetIndex( void );
int32_t               vexTaskGetTaskIndex( rmTask_t );
void                  vexTaskSleep( uint32_t time );
void                  vexSemaphoreInit( rmSemaphore *pSemaphore );
void                  vexSemaphoreLock( rmSemaphore *pSemaphore, uint32_t time );
void                  vexSemaphoreUnlock( rmSemaphore *pSemaphore );
int                   vexSemaphoreGetOwner( rmSemaphore *pSemaphore );
void                  vexTasksDump( void );
void                 *vexTaskGetCallback( uint32_t index );
void                  vexTaskWaitForExit( rmTask_t );
rmTaskStates          vexTaskStateGet( rmTask_t );
void                  vexCriticalSection( bool value );
void                  vexTaskStopAll( void );
void                  vexTaskStopAllUser( int (* maintask)(void) );
void                  vexTaskRemoveAllUser( int (* maintask)(void) );

// new 1.0.5
int32_t               vexTaskAddWithArg( rmTaskArg_t, int interval, void *arg, char const *label );
int32_t               vexTaskAddWithPriorityWithArg( rmTaskArg_t, int interval, void *arg, char const *label, int priority );
void                  vexTaskStopWithId( rmTaskArg_t, int callback_id );
void                  vexTaskSuspendWithId( rmTaskArg_t, int callback_id );
void                  vexTaskResumeWithId( rmTaskArg_t, int callback_id );
int32_t               vexTaskPriorityGetWithId( rmTaskArg_t, int callback_id );
void                  vexTaskPrioritySetWithId( rmTaskArg_t, int callback_id, int32_t priority );
rmTaskStates          vexTaskStateGetWithId( rmTaskArg_t, int callback_id );
int32_t               vexTaskGetTaskIndexWithId( rmTaskArg_t, int callback_id  );

int32_t               vexTaskHardwareConcurrency( void );
void                  vexTaskCompletionIdSet( int32_t id );

// new 1.0.10
void                  vexTaskWaitForExitWithId( rmTaskArg_t, int callback_id );
void                 *vexTaskGet( uint32_t index );
void                 *vexTaskGetCallbackAndId( uint32_t index, int *callback_id );

// new 1.0.12
int32_t               vexTaskStackSizeGet( void );
int32_t               vexTaskStackDefaultSizeGet( void );
int32_t               vexTaskStackUseGet( uint32_t index );
void                 *vexTaskStackTopGet( uint32_t index );
int32_t               vexTaskFree( uint32_t index );
void                 *vexTaskGetArgs( uint32_t index, uint16_t *type );
void                  vexTaskSetArgs( uint32_t index, void *args );

// Event handler
void                  vexEventBroadcast( uint32_t index );
void                  vexEventBroadcastAndWait( uint32_t index, int32_t timeout );

void                  vexEventAdd( uint32_t index, uint32_t mask, void (* callback)(void) );
int32_t               vexEventUserIndexGet( void );
void                  vexEventAddWithArg( uint32_t index, uint32_t mask, void (* callback)(void *), void *arg );
void                  vexEventsCleanup(void);
void                  vexEventsDump(void);
void                 *vexEventGetArg( void *event );
int32_t               vexEventsGetMax(void);
int32_t               vexEventsGetCount(void);

// Breakpoint
void                  vexBreak(uint32_t filehash, uint32_t tag);
// Breakpoint dev only
void                  vexTaskBreakpointSet( uint32_t filehash, uint32_t tag );
void                  vexTaskBreakpointDump(void);

// Console output
int32_t               vexDebug( char const *fmt, ... );
int32_t               vex_printf( char const *fmt, ... );
int32_t               vex_sprintf ( char *out, const char *format, ... );
int32_t               vex_snprintf( char *out, uint32_t max_len, const char *format, ... );
int32_t               vex_vsprintf( char *out, const char *format, va_list args );
int32_t               vex_vsnprintf( char *out, uint32_t max_len, const char *format, va_list args );

// system
uint32_t              vexSystemTimeGet( void );
void                  vexGettime( struct time *pTime );
void                  vexGetdate( struct date *pDate );
void                  vexSystemMemoryDump( void );
void                  vexSystemDigitalIO( uint32_t pin, uint32_t value );
uint32_t              vexSystemStartupOptions(void);
void                  vexSystemExitRequest(void);
uint64_t              vexSystemHighResTimeGet( void );
uint64_t              vexSystemPowerupTimeGet( void );
uint32_t              vexSystemLinkAddrGet( void );
uint32_t              vexSystemUsbStatus( void );

// Generic device
uint32_t              vexDevicesGetNumber( void );
uint32_t              vexDevicesGetNumberByType( IQ_DeviceType type );
IQ_DeviceT            vexDevicesGet( void );
IQ_DeviceT            vexDeviceGetByIndex( uint32_t index );
int32_t               vexDeviceGetStatus( IQ_DeviceType *buffer );
uint32_t              vexDeviceButtonStateGet( void );

IQ_DeviceType         vexDeviceTypeGetByIndex( uint32_t index );
void                  vexDeviceTypeSetByIndex( uint32_t index, IQ_DeviceType type );
bool                  vexDeviceTimerSet( int32_t index, void (* callback)(void *), uint32_t delay );
bool                  vexDeviceTimerSetWithArg( int32_t index, void (* callback)(void *), uint32_t delay, void *arg );
void                  vexDeviceTimerDump( void );
uint32_t              vexDeviceFlagsGetByIndex( uint32_t index );

// This is used by the port index functions to map an index to the device pointer
#define  VEX_DEVICE_GET(device, index) IQ_DeviceT device = vexDeviceGetByIndex( index )

int32_t               vexTouchledValueGet( uint32_t index );
void                  vexTouchledColorSet( uint32_t index, uint32_t color );
void                  vexTouchledRgbSet( uint32_t index, int32_t red, int32_t green, int32_t blue );
uint32_t              vexTouchledColorGet( uint32_t index );
uint32_t              vexTouchledRgbGet( uint32_t index, int32_t *red, int32_t *green, int32_t *blue );
int32_t               vexTouchledRedGet( uint32_t index );
int32_t               vexTouchledGreenGet( uint32_t index );
int32_t               vexTouchledBlueGet( uint32_t index );
void                  vexTouchledOn( uint32_t index );
void                  vexTouchledOff( uint32_t index );
void                  vexTouchledBrightnessSet( uint32_t index , int32_t brightness );
void                  vexTouchledFadeSet( uint32_t index , int32_t fadeSetting ); 
void                  vexTouchledBlinkTimeSet( uint32_t index , int32_t blinkOnTime, int32_t blinkOffTime );

// bumper switch
int32_t               vexBumperGet( uint32_t index );

int32_t               vexAnalogPinGet( uint32_t index );
int32_t               vexDigitalPinGet( uint32_t index );

// Gyro
void                  vexGyroReset( uint32_t index );
double                vexGyroHeadingGet( uint32_t index );
double                vexGyroDegreesGet( uint32_t index );
int32_t               vexGyroRateGet( uint32_t index );
int32_t               vexGyroRawDataGet( uint32_t index, uint8_t *pBuf );
void                  vexGyroCalibrationStart( uint32_t index, IQGyroCalibrateSamples nCalibrationSetting );
bool                  vexGyroCalibrationFlagGet( uint32_t index );
bool                  vexGyroOverRangeFlagGet( uint32_t index );
void                  vexGyroSensitivitySet( uint32_t index, IQGyroSensitivity nRange);
IQGyroSensitivity     vexGyroSensitivityGet( uint32_t index );
void                  vexGyroModeSet( uint32_t index, uint32_t mode );
uint32_t              vexGyroModeGet( uint32_t index );

void                  vexMotorVelocitySet( uint32_t index, int32_t velocity );
void                  vexMotorVelocityUpdate( uint32_t index, int32_t velocity );
void                  vexMotorVoltageSet( uint32_t index, int32_t value );
int32_t               vexMotorVelocityGet( uint32_t index );
int32_t               vexMotorDirectionGet( uint32_t index );
double                vexMotorActualVelocityGet( uint32_t index );
void                  vexMotorModeSet( uint32_t index, IQMotorControlMode mode );
IQMotorControlMode    vexMotorModeGet( uint32_t index );
void                  vexMotorPwmSet( uint32_t index, int32_t value );
int32_t               vexMotorPwmGet( uint32_t index );
void                  vexMotorCurrentLimitSet( uint32_t index, int32_t value );
int32_t               vexMotorCurrentLimitGet( uint32_t index );
void                  vexMotorVoltageLimitSet( uint32_t index, int32_t value );
int32_t               vexMotorVoltageLimitGet( uint32_t index );
void                  vexMotorPositionPidSet( uint32_t index, void *pid );
void                  vexMotorVelocityPidSet( uint32_t index, void *pid );
int32_t               vexMotorCurrentGet( uint32_t index );
int32_t               vexMotorVoltageGet( uint32_t index );
double                vexMotorPowerGet( uint32_t index );
double                vexMotorTorqueGet( uint32_t index );
double                vexMotorEfficiencyGet( uint32_t index );
double                vexMotorTemperatureGet( uint32_t index );
bool                  vexMotorOverTempFlagGet( uint32_t index );
bool                  vexMotorCurrentLimitFlagGet( uint32_t index );
uint32_t              vexMotorFaultsGet( uint32_t index );
bool                  vexMotorZeroVelocityFlagGet( uint32_t index );
bool                  vexMotorZeroPositionFlagGet( uint32_t index );
uint32_t              vexMotorFlagsGet( uint32_t index );
void                  vexMotorReverseFlagSet( uint32_t index, bool value );
bool                  vexMotorReverseFlagGet( uint32_t index );
void                  vexMotorEncoderUnitsSet( uint32_t index, IQMotorEncoderUnits units );
IQMotorEncoderUnits   vexMotorEncoderUnitsGet( uint32_t index );
void                  vexMotorBrakeModeSet( uint32_t index, IQMotorBrakeMode mode );
IQMotorBrakeMode      vexMotorBrakeModeGet( uint32_t index );
void                  vexMotorPositionSet( uint32_t index, double position );
double                vexMotorPositionGet( uint32_t index );
int32_t               vexMotorPositionRawGet( uint32_t index, uint32_t *timestamp );
void                  vexMotorPositionReset( uint32_t index );
double                vexMotorTargetGet( uint32_t index );
void                  vexMotorServoTargetSet( uint32_t index, double position );
void                  vexMotorAbsoluteTargetSet( uint32_t index, double position, int32_t velocity );
void                  vexMotorRelativeTargetSet( uint32_t index, double position, int32_t velocity );
void                  vexMotorGearingSet( uint32_t index, IQMotorGearset value );
IQMotorGearset        vexMotorGearingGet( uint32_t index );

void                  vexVisionModeSet( uint32_t index, IQVisionMode mode );
IQVisionMode          vexVisionModeGet( uint32_t index );
int32_t               vexVisionObjectCountGet( uint32_t index );
int32_t               vexVisionObjectsGet( uint32_t index, uint32_t signature, uint32_t maxcount, IQ_DeviceVisionObject *pObject );
void                  vexVisionSignatureSet( uint32_t index, IQ_DeviceVisionSignature *pSignature );
bool                  vexVisionSignatureGet( uint32_t index, uint32_t id, IQ_DeviceVisionSignature *pSignature );
void                  vexVisionBrightnessSet( uint32_t index, uint8_t percent );
uint8_t               vexVisionBrightnessGet( uint32_t index );
void                  vexVisionWhiteBalanceModeSet( uint32_t index, IQVisionWBMode mode );
IQVisionWBMode        vexVisionWhiteBalanceModeGet( uint32_t index );
void                  vexVisionWhiteBalanceSet( uint32_t index, IQ_DeviceVisionRgb color );
IQ_DeviceVisionRgb    vexVisionWhiteBalanceGet( uint32_t index );
void                  vexVisionLedModeSet( uint32_t index, IQVisionLedMode mode );
IQVisionLedMode       vexVisionLedModeGet( uint32_t index );
void                  vexVisionLedBrigntnessSet( uint32_t index, uint8_t percent );
uint8_t               vexVisionLedBrigntnessGet( uint32_t index );
void                  vexVisionLedColorSet( uint32_t index, IQ_DeviceVisionRgb color);
IQ_DeviceVisionRgb    vexVisionLedColorGet( uint32_t index );
void                  vexVisionWifiModeSet( uint32_t index, IQVisionWifiMode mode );
IQVisionWifiMode      vexVisionWifiModeGet( uint32_t index );

void                  vexRgbModeSet( uint32_t index, IORgbColorTypes nColorMode );
IORgbColorTypes       vexRgbModeGet( uint32_t index );
void                  vexRgbProximityThresholdSet( uint32_t index, uint16_t value );
void                  vexRgbLedSet( uint32_t index, uint8_t value );
uint32_t              vexRgbValueRawGet( uint32_t index );
int32_t               vexRgbRedChannelGet( uint32_t index );
int32_t               vexRgbGreenChannelGet( uint32_t index );
int32_t               vexRgbBlueChannelGet( uint32_t index );
int32_t               vexRgbGrayscaleGet( uint32_t index );
int32_t               vexRgbSaturationGet( uint32_t index );
int32_t               vexRgbHueGet( uint32_t index );
int32_t               vexRgbProximityGet( uint32_t index );

void                  vexSonarUnits( uint32_t index, bool bRaw );
void                  vexSonarSnrThresholdSet( uint32_t index, uint32_t value );
void                  vexSonarBrightnessThresholdSet( uint32_t index, uint32_t value );
void                  vexSonarFilterFactorSet( uint32_t index, uint32_t value );
void                  vexSonarTransmitPowerSet( uint32_t index, uint32_t value );
void                  vexSonarMinRangeSet( uint32_t index, uint32_t value );
void                  vexSonarMaxRangeSet( uint32_t index, uint32_t value );
int32_t               vexSonarStrongestGet( uint32_t index );
int32_t               vexSonarSecondStrongestGet( uint32_t index );
int32_t               vexSonarMostReflectiveGet( uint32_t index );
int32_t               vexSonarMinRangeGet( uint32_t index );
int32_t               vexSonarMaxRangeGet( uint32_t index );

void                  vexImuReset( uint32_t index );
double                vexImuHeadingGet( uint32_t index );
double                vexImuDegreesGet( uint32_t index );
void                  vexImuQuaternionGet( uint32_t index, IQ_DeviceImuQuaternion *data );
void                  vexImuAttitudeGet( uint32_t index, IQ_DeviceImuAttitude *data );
void                  vexImuRawGyroGet( uint32_t index, IQ_DeviceImuRaw *data );
void                  vexImuRawAccelGet( uint32_t index, IQ_DeviceImuRaw *data );
uint32_t              vexImuStatusGet( uint32_t index );
void                  vexImuModeSet( uint32_t index, uint32_t mode );
uint32_t              vexImuModeGet( uint32_t index );
void                  vexImuDataRateSet( uint32_t index, uint32_t rate );

uint32_t              vexDistanceDistanceGet( uint32_t index );
uint32_t              vexDistanceConfidenceGet( uint32_t index );
int32_t               vexDistanceObjectSizeGet( uint32_t index );
double                vexDistanceObjectVelocityGet( uint32_t index );
uint32_t              vexDistanceStatusGet( uint32_t index );

double                vexOpticalHueGet( uint32_t index );
double                vexOpticalSatGet( uint32_t index );
double                vexOpticalBrightnessGet( uint32_t index );
int32_t               vexOpticalProximityGet( uint32_t index );
void                  vexOpticalRgbGet( uint32_t index, IQ_DeviceOpticalRgb *data );
void                  vexOpticalLedPwmSet( uint32_t index, int32_t value );
int32_t               vexOpticalLedPwmGet( uint32_t index );
uint32_t              vexOpticalStatusGet( uint32_t index );
void                  vexOpticalRawGet( uint32_t index, IQ_DeviceOpticalRaw *data );
void                  vexOpticalModeSet( uint32_t index, uint32_t mode );
uint32_t              vexOpticalModeGet( uint32_t index );
uint32_t              vexOpticalGestureGet( uint32_t index, IQ_DeviceOpticalGesture *pData );
void                  vexOpticalGestureEnable( uint32_t index );
void                  vexOpticalGestureDisable( uint32_t index );
int32_t               vexOpticalProximityThreshold( uint32_t index, int32_t value );
void                  vexOpticalIntegrationTimeSet( uint32_t index, double timeMs );
double                vexOpticalIntegrationTimeGet( uint32_t index );

void                  vexSoundPlay( int32_t slot, uint32_t volume );
void                  vexSoundPlayTone( int32_t note, uint32_t volume, uint32_t duration );

void                  vexPneumaticCompressorSet( uint32_t index, bool bState );
void                  vexPneumaticCylinderSet( uint32_t index, uint32_t id, bool bState );
void                  vexPneumaticCtrlSet( uint32_t index, uint8_t ctrl, uint8_t data1, uint8_t data2 );
uint32_t              vexPneumaticStatusGet( uint32_t index );
void                  vexPneumaticPwmSet( uint32_t index, uint8_t pwm );
uint32_t              vexPneumaticPwmGet( uint32_t index );

// Display/graphics
void                  vexDisplayForegroundColor( uint32_t col );
void                  vexDisplayBackgroundColor( uint32_t col );
uint32_t              vexDisplayForegroundColorGet( void );
uint32_t              vexDisplayBackgroundColorGet( void );
void                  vexDisplayErase(void);
void                  vexDisplayScroll( int32_t nStartLine, int32_t nLines );
void                  vexDisplayScrollRect( int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t nLines );
void                  vexDisplayCopyRect( int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t *pSrc, int32_t srcStride );
void                  vexDisplayPixelSet( uint32_t x, uint32_t y );
void                  vexDisplayPixelClear( uint32_t x, uint32_t y );
void                  vexDisplayLineDraw( int32_t x1, int32_t y1, int32_t x2, int32_t y2 );
void                  vexDisplayLineClear( int32_t x1, int32_t y1, int32_t x2, int32_t y2 );
void                  vexDisplayRectDraw( int32_t x1, int32_t y1, int32_t x2, int32_t y2 );
void                  vexDisplayRectClear( int32_t x1, int32_t y1, int32_t x2, int32_t y2 );
void                  vexDisplayRectFill( int32_t x1, int32_t y1, int32_t x2, int32_t y2 );
void                  vexDisplayCircleDraw( int32_t xc, int32_t yc, int32_t radius );
void                  vexDisplayCircleClear( int32_t xc, int32_t yc, int32_t radius );
void                  vexDisplayCircleFill( int32_t xc, int32_t yc, int32_t radius );

void                  vexDisplayPrintf( int32_t xpos, int32_t ypos, uint32_t bOpaque, const char *format, ... );
void                  vexDisplayString( const int32_t nLineNumber, const char *format, ... );
void                  vexDisplayStringAt( int32_t xpos, int32_t ypos, const char *format, ... );
void                  vexDisplayBigString( const int32_t nLineNumber, const char *format, ... );
void                  vexDisplayBigStringAt( int32_t xpos, int32_t ypos, const char *format, ... );
void                  vexDisplaySmallStringAt( int32_t xpos, int32_t ypos, const char *format, ... );
void                  vexDisplayCenteredString( const int32_t nLineNumber, const char *format, ...);
void                  vexDisplayBigCenteredString( const int32_t nLineNumber, const char *format, ...);

// Not really for user code but we need these for some wrapper functions
void                  vexDisplayVPrintf( int32_t xpos, int32_t ypos, uint32_t bOpaque, const char *format, va_list args );
void                  vexDisplayVString( const int32_t nLineNumber, const char *format, va_list args );
void                  vexDisplayVStringAt( int32_t xpos, int32_t ypos, const char *format, va_list args );
void                  vexDisplayVBigString( const int32_t nLineNumber, const char *format, va_list args);
void                  vexDisplayVBigStringAt( int32_t xpos, int32_t ypos, const char *format, va_list args );
void                  vexDisplayVSmallStringAt( int32_t xpos, int32_t ypos, const char *format, va_list args );
void                  vexDisplayVCenteredString( const int32_t nLineNumber, const char *format, va_list args );
void                  vexDisplayVBigCenteredString( const int32_t nLineNumber, const char *format, va_list args );

void                  vexDisplayFontNamedSet( const char *pFontName );
int32_t               vexDisplayStringWidthGet( const char *pString );
int32_t               vexDisplayStringHeightGet( const char *pString );

void                  vexDisplayTextSmoothing( uint32_t value );
void                  vexDisplayTextReference( uint32_t value );
void                  vexDisplayTextSpacing( uint32_t value );
void                  vexDisplayPenSizeSet( uint32_t value );
uint32_t              vexDisplayPenSizeGet( void );
void                  vexDisplayTextSize( uint32_t n, uint32_t d );

void                  vexDisplayClipRegionSet( int32_t x1, int32_t y1, int32_t x2, int32_t y2 );
void                  vexDisplayClipRegionClear();
void                  vexDisplayClipRegionSetWithIndex( int32_t index, int32_t x1, int32_t y1, int32_t x2, int32_t y2 );

uint32_t              vexImageBmpRead( const uint8_t *ibuf, iq2_image *oBuf, uint32_t maxw, uint32_t maxh );
// special use only ! Talk to James.
int32_t               vexScratchMemoryPtr( void **ptr );
bool                  vexScratchMemoryLock( void );
void                  vexScratchMemoryUnlock( void );

// SD card
FRESULT               vexFileMountSD( void );
FRESULT               vexFileDirectoryGet( const char *path, char *buffer, uint32_t len );
FIL                  *vexFileOpen(const char *filename, const char *mode );
FIL                  *vexFileOpenWrite(const char *filename);
FIL                  *vexFileOpenCreate(const char *filename);
void                  vexFileClose(FIL *fdp);
int32_t               vexFileRead( char *buf, uint32_t size, uint32_t nItems, FIL *fdp );
int32_t               vexFileWrite( char *buf, uint32_t size, uint32_t nItems, FIL *fdp );
int32_t               vexFileSize( FIL *fdp );
FRESULT               vexFileSeek( FIL *fdp, uint32_t offset, int32_t whence );
bool                  vexFileDriveStatus( uint32_t drive );
int32_t               vexFileTell( FIL *fdp );
void                  vexFileSync( FIL *fdp );
uint32_t              vexFileStatus( const char *filename );

// CDC
int32_t               vexSerialWriteChar( uint32_t channel, uint8_t c );
int32_t               vexSerialWriteBuffer( uint32_t channel, uint8_t *data, uint32_t data_len );
int32_t               vexSerialReadChar( uint32_t channel );
int32_t               vexSerialPeekChar( uint32_t channel );
int32_t               vexSerialWriteFree( uint32_t channel );
// private serial
void                  vexSerialEnableRemoteConsole( void );

// system utility
uint32_t              vexSystemVersion( void );
uint32_t              vexStdlibVersion( void );
// get SDK version
uint32_t              vexSdkVersion( void );

// battery
int32_t               vexBatteryVoltageGet( void );
int32_t               vexBatteryCurrentGet( void );
double                vexBatteryTemperatureGet( void );
double                vexBatteryCapacityGet( void );

// device event mask, data direct access
void                  vexEventMaskSet( uint32_t index, uint32_t bits, uint32_t mask );
uint32_t              vexEventMaskGet( uint32_t index );
void                  vexEventDataSet( uint32_t index, uint32_t bits, uint32_t mask );
uint32_t              vexEventDataGet( uint32_t index );
void                  vexEventBitsSet( uint32_t index, uint32_t bits, uint32_t mask );
uint32_t              vexEventBitsGet( uint32_t index );

// Generic serial port comms to any device
void                  vexGenericSerialEnable( uint32_t index, int32_t options );
void                  vexGenericSerialBaudrate( uint32_t index, int32_t baudrate );
int32_t               vexGenericSerialWriteChar( uint32_t index, uint8_t c );
int32_t               vexGenericSerialWriteFree( uint32_t index );
int32_t               vexGenericSerialTransmit( uint32_t index, uint8_t *buffer, int32_t length );
int32_t               vexGenericSerialReadChar( uint32_t index );
int32_t               vexGenericSerialPeekChar( uint32_t index );
int32_t               vexGenericSerialReceiveAvail( uint32_t index );
int32_t               vexGenericSerialReceive( uint32_t index, uint8_t *buffer, int32_t length );
void                  vexGenericSerialFlush( uint32_t index );

// generic i2c
int32_t               vexGenericI2cReadBuffer( uint32_t index, uint8_t addr, uint8_t *pData, uint32_t nLength );
uint8_t               vexGenericI2cReadByte( uint32_t index, uint8_t addr );
int32_t               vexGenericI2cReadRegBuffer( uint32_t index, uint8_t addr, uint8_t reg, uint8_t *pData, uint32_t nLength );
uint8_t               vexGenericI2cReadRegByte( uint32_t index, uint8_t addr, uint8_t reg );
int32_t               vexGenericI2cWriteBuffer( uint32_t index, uint8_t addr, uint8_t *pData, uint32_t nLength );
int32_t               vexGenericI2cWriteByte( uint32_t index, uint8_t addr, uint8_t data );
int32_t               vexGenericI2cWriteRegBuffer( uint32_t index, uint8_t addr, uint8_t reg, uint8_t *pData, uint32_t nLength );
int32_t               vexGenericI2cWriteRegByte( uint32_t index, uint8_t addr, uint8_t reg, uint8_t data );
int32_t               vexGenericI2cWriteReadBuffer( uint32_t index, uint8_t addr, uint8_t *pData, uint32_t nLength, uint8_t *pRxData, uint32_t nRxLength );

// generic digital
bool                  vexGenericDigitalEnable( uint32_t index, uint32_t options );
bool                  vexGenericDigitalOutput( uint32_t index, uint32_t target, uint32_t value );
bool                  vexGenericDigitalInput( uint32_t index, uint32_t target );

// Controller
int32_t               vexControllerGet( IQ_ControllerId id, IQ_ControllerIndex index );
IQ_ControllerStatus   vexControllerConnectionStatusGet( IQ_ControllerId id );

#ifdef __cplusplus
}
#endif
#endif /* IQ_API_H_*/
