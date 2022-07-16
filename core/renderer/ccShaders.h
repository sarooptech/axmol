/****************************************************************************
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2012 		cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

https://axis-project.github.io/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#pragma once

/// @cond DO_NOT_SHOW

#include "platform/CCPlatformMacros.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_AX_BEGIN

extern AX_DLL const char* positionColor_vert;
extern AX_DLL const char* positionColor_frag;
extern AX_DLL const char* positionTexture_vert;
extern AX_DLL const char* positionTexture_frag;
extern AX_DLL const char* positionTextureColor_vert;
extern AX_DLL const char* positionTextureColor_frag;
extern AX_DLL const char* positionTextureColorAlphaTest_frag;
extern AX_DLL const char* label_normal_frag;
extern AX_DLL const char* label_distanceNormal_frag;
extern AX_DLL const char* labelOutline_frag;
extern AX_DLL const char* labelDistanceFieldGlow_frag;
extern AX_DLL const char* lineColor3D_frag;
extern AX_DLL const char* lineColor3D_vert;
extern AX_DLL const char* positionColorLengthTexture_vert;
extern AX_DLL const char* positionColorLengthTexture_frag;
extern AX_DLL const char* positionColorTextureAsPointsize_vert;
extern AX_DLL const char* position_vert;
extern AX_DLL const char* layer_radialGradient_frag;
extern AX_DLL const char* grayScale_frag;
extern AX_DLL const char* positionUColor_vert;
extern AX_DLL const char* dualSampler_frag;
extern AX_DLL const char* dualSampler_gray_frag;
extern AX_DLL const char* cameraClear_vert;
extern AX_DLL const char* cameraClear_frag;

extern AX_DLL const char* CC3D_color_frag;
extern AX_DLL const char* CC3D_colorNormal_frag;
extern AX_DLL const char* CC3D_colorNormalTexture_frag;
extern AX_DLL const char* CC3D_colorTexture_frag;
extern AX_DLL const char* CC3D_particleTexture_frag;
extern AX_DLL const char* CC3D_particleColor_frag;
extern AX_DLL const char* CC3D_particle_vert;
extern AX_DLL const char* CC3D_positionNormalTexture_vert;
extern AX_DLL const char* CC3D_skinPositionNormalTexture_vert;
extern AX_DLL const char* CC3D_positionTexture_vert;
extern AX_DLL const char* CC3D_skinPositionTexture_vert;
extern AX_DLL const char* CC3D_skybox_frag;
extern AX_DLL const char* CC3D_skybox_vert;
extern AX_DLL const char* CC3D_terrain_frag;
extern AX_DLL const char* CC3D_terrain_vert;

extern AX_DLL const char* CC2D_quadTexture_frag;
extern AX_DLL const char* CC2D_quadColor_frag;
extern AX_DLL const char* CC2D_quad_vert;

extern AX_DLL const char* hsv_frag;
extern AX_DLL const char* dualSampler_hsv_frag;
NS_AX_END
/**
 end of support group
 @}
 */
/// @endcond
