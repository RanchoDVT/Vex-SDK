/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2020, All rights reserved.               */
/*                                                                            */
/*    Module:     v5_apigraphics.h                                            */
/*    Author:     James Pearman                                               */
/*    Created:    12 Dec 2020                                                 */
/*                                                                            */
/*    Revisions:  V0.1                                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef V5_APIGRAPHICS_H_
#define V5_APIGRAPHICS_H_

#include "stdint.h"

/*-----------------------------------------------------------------------------*/
/** @file    v5_apigraphics.h
  * @brief   Header for V5 offscreen graphics
*//*---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

// Some offscreen user side drawing functions
typedef struct {
    uint16_t  *pBuf;
    uint32_t   width;
    uint32_t   height;
    uint32_t   bgColor;
} vexOffscreenBuffer;

vexOffscreenBuffer *vexDisplayOffscreenBufferGet( uint32_t width, int32_t height, uint32_t color );
void     vexDisplayOffscreenBufferDestroy( vexOffscreenBuffer *pOsb );
void     vexDisplayOffscreenBufferPixelSet( vexOffscreenBuffer *pOsb, uint32_t x, uint32_t y, uint32_t color );
uint32_t vexDisplayOffscreenBufferPixelGet( vexOffscreenBuffer *pOsb, uint32_t x, uint32_t y);
void     vexDisplayOffscreenBufferRectDraw( vexOffscreenBuffer *pOsb, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color );
void     vexDisplayOffscreenBufferRectFill( vexOffscreenBuffer *pOsb, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color );
void     vexDisplayOffscreenBufferScrollH( vexOffscreenBuffer *pOsb, uint32_t pix );
void     vexDisplayOffscreenBufferBlit( vexOffscreenBuffer *pOsb, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2 );

#ifdef __cplusplus
}
#endif
#endif /* V5_APIGRAPHICS_H_ */