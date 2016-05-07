/*
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2005 Blender Foundation.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): Clement Foucault.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

/** \file GPU_luts.h
 *  \ingroup gpu
 */

#ifndef __GPU_LUTS_H__
#define __GPU_LUTS_H__

#ifdef __cplusplus
extern "C" {
#endif

struct GPUTexture;

typedef struct GPUPBR {
	struct GPUTexture *hammersley;
	struct GPUTexture *jitter;
	struct GPUTexture *ltc_mat_ggx;
	struct GPUTexture *ltc_mag_ggx;
} GPUPBR;

struct GPUTexture *create_jitter_texture(void);
struct GPUTexture *create_spiral_sample_texture(int numsamples);

GPUPBR *GPU_pbr_create(void);
void GPU_pbr_free(GPUPBR *pbr);

#ifdef __cplusplus
}
#endif

#endif  /* __GPU_LUTS_H__ */
