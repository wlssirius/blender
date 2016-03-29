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
 * The Original Code is Copyright (C) Blender Foundation.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): Lukas Toenne
 *
 * ***** END GPL LICENSE BLOCK *****
 */

#ifndef __BVM_EVAL_COMMON_H__
#define __BVM_EVAL_COMMON_H__

/** \file bvm_eval_common.h
 *  \ingroup bvm
 */

#include "bvm_eval.h"
#include "bvm_instruction_list.h"

namespace blenvm {

struct EvalContext;

struct EvalKernelData {
	const EvalContext *context;
	const InstructionList *function;
};

inline static float stack_load_float(const EvalStack *stack, StackIndex offset)
{
	return *(float *)(&stack[offset]);
}

inline static float3 stack_load_float3(const EvalStack *stack, StackIndex offset)
{
	return *(float3 *)(&stack[offset]);
}

inline static float4 stack_load_float4(const EvalStack *stack, StackIndex offset)
{
	return *(float4 *)(&stack[offset]);
}

inline static int stack_load_int(const EvalStack *stack, StackIndex offset)
{
	return *(int *)(&stack[offset]);
}

inline static matrix44 stack_load_matrix44(const EvalStack *stack, StackIndex offset)
{
	return *(matrix44 *)(&stack[offset]);
}

/* convenience function */
inline static SpaceTransform stack_load_space_transform(const EvalStack *stack,
                                                        StackIndex offset_transform,
                                                        StackIndex offset_invtransform)
{
	SpaceTransform transform;
	copy_m4_m4(transform.local2target, stack_load_matrix44(stack, offset_transform).data);
	copy_m4_m4(transform.target2local, stack_load_matrix44(stack, offset_invtransform).data);
	return transform;
}

inline static const char *stack_load_string(const EvalStack *stack, StackIndex offset)
{
	return *(const char **)(&stack[offset]);
}

inline static PointerRNA stack_load_rnapointer(const EvalStack *stack, StackIndex offset)
{
	return *(PointerRNA *)(&stack[offset]);
}

inline static mesh_ptr stack_load_mesh_ptr(const EvalStack *stack, StackIndex offset)
{
	return *(mesh_ptr *)(&stack[offset]);
}

inline static DerivedMesh *stack_load_mesh(const EvalStack *stack, StackIndex offset)
{
	return ((mesh_ptr *)(&stack[offset]))->get();
}

inline static duplis_ptr stack_load_duplis_ptr(const EvalStack *stack, StackIndex offset)
{
	return *(duplis_ptr *)(&stack[offset]);
}

inline static const DupliList *stack_load_duplis(const EvalStack *stack, StackIndex offset)
{
	return ((duplis_ptr *)(&stack[offset]))->get();
}

/* ------------------------------------------------------------------------- */

inline static void stack_store_float(EvalStack *stack, StackIndex offset, float f)
{
	*(float *)(&stack[offset]) = f;
}

inline static void stack_store_float3(EvalStack *stack, StackIndex offset, float3 f)
{
	*(float3 *)(&stack[offset]) = f;
}

inline static void stack_store_float4(EvalStack *stack, StackIndex offset, float4 f)
{
	*(float4 *)(&stack[offset]) = f;
}

inline static void stack_store_int(EvalStack *stack, StackIndex offset, int i)
{
	*(int *)(&stack[offset]) = i;
}

inline static void stack_store_matrix44(EvalStack *stack, StackIndex offset, matrix44 m)
{
	*(matrix44 *)(&stack[offset]) = m;
}

/* convenience function */
inline static void stack_store_space_transform(EvalStack *stack,
                                               StackIndex offset_transform,
                                               StackIndex offset_invtransform,
                                               SpaceTransform transform)
{
	stack_store_matrix44(stack, offset_transform, matrix44::from_data(&transform.local2target[0][0]));
	stack_store_matrix44(stack, offset_invtransform, matrix44::from_data(&transform.target2local[0][0]));
}

inline static void stack_store_string(EvalStack *stack, StackIndex offset, const char *s)
{
	*(const char **)(&stack[offset]) = s;
}

inline static void stack_store_rnapointer(EvalStack *stack, StackIndex offset, PointerRNA p)
{
	*(PointerRNA *)(&stack[offset]) = p;
}

inline static void stack_store_mesh_ptr(EvalStack *stack, StackIndex offset, mesh_ptr p)
{
	*(mesh_ptr *)(&stack[offset]) = p;
}

inline static void stack_store_mesh(EvalStack *stack, StackIndex offset, DerivedMesh *dm)
{
	((mesh_ptr *)(&stack[offset]))->set(dm);
}

inline static void stack_store_duplis_ptr(EvalStack *stack, StackIndex offset, duplis_ptr p)
{
	*(duplis_ptr *)(&stack[offset]) = p;
}

inline static void stack_store_duplis(EvalStack *stack, StackIndex offset, DupliList *lb)
{
	((duplis_ptr *)(&stack[offset]))->set(lb);
}

} /* namespace bvm */

#endif /* __BVM_EVAL_COMMON_H__ */
