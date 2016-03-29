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

#ifndef __BVM_INSTRUCTION_LIST_H__
#define __BVM_INSTRUCTION_LIST_H__

/** \file bvm_instruction_list.h
 *  \ingroup bvm
 */

#include <vector>
#include <stdint.h>

#include "MEM_guardedalloc.h"

#include "util_opcode.h"
#include "util_data_ptr.h"
#include "util_math.h"
#include "util_string.h"
#include "util_thread.h"

namespace blenvm {

typedef uint32_t Instruction;
typedef Instruction StackIndex;
#define BVM_STACK_INVALID 0xFFFFFFFF
#define BVM_JMP_INVALID 0xFFFFFFFF

static inline Instruction float_to_instruction(float f)
{
	union { uint32_t i; float f; } u;
	u.f = f;
	return u.i;
}

static inline Instruction int_to_instruction(int v)
{
	union { uint32_t i; int v; } u;
	u.v = v;
	return u.i;
}

static inline float instruction_to_float(Instruction i)
{
	union { uint32_t i; float f; } u;
	u.i = i;
	return u.f;
}

static inline int instruction_to_int(Instruction i)
{
	union { uint32_t i; int v; } u;
	u.i = i;
	return u.v;
}

struct InstructionList {
	typedef std::vector<Instruction> Instructions;
	
	InstructionList();
	~InstructionList();
	
	OpCode read_opcode(int *instr) const
	{
		OpCode op = (OpCode)m_instructions[*instr];
		++(*instr);
		return op;
	}
	
	StackIndex read_stack_index(int *instr) const
	{
		StackIndex index = m_instructions[*instr];
		++(*instr);
		return index;
	}
	
	int read_jump_address(int *instr) const
	{
		int address = m_instructions[*instr];
		++(*instr);
		return address;
	}
	
	float read_float(int *instr) const
	{
		float f = instruction_to_float(m_instructions[*instr]);
		++(*instr);
		return f;
	}
	
	float3 read_float3(int *instr) const
	{
		float3 f;
		f.x = instruction_to_float(m_instructions[*instr + 0]);
		f.y = instruction_to_float(m_instructions[*instr + 1]);
		f.z = instruction_to_float(m_instructions[*instr + 2]);
		(*instr) += 3;
		return f;
	}
	
	float4 read_float4(int *instr) const
	{
		float4 f;
		f.x = instruction_to_float(m_instructions[*instr + 0]);
		f.y = instruction_to_float(m_instructions[*instr + 1]);
		f.z = instruction_to_float(m_instructions[*instr + 2]);
		f.w = instruction_to_float(m_instructions[*instr + 3]);
		(*instr) += 4;
		return f;
	}
	
	int read_int(int *instr) const
	{
		int i = instruction_to_int(m_instructions[*instr]);
		++(*instr);
		return i;
	}
	
	matrix44 read_matrix44(int *instr) const
	{
		matrix44 m;
		m.data[0][0] = instruction_to_float(m_instructions[*instr + 0]);
		m.data[0][1] = instruction_to_float(m_instructions[*instr + 1]);
		m.data[0][2] = instruction_to_float(m_instructions[*instr + 2]);
		m.data[0][3] = instruction_to_float(m_instructions[*instr + 3]);
		m.data[1][0] = instruction_to_float(m_instructions[*instr + 4]);
		m.data[1][1] = instruction_to_float(m_instructions[*instr + 5]);
		m.data[1][2] = instruction_to_float(m_instructions[*instr + 6]);
		m.data[1][3] = instruction_to_float(m_instructions[*instr + 7]);
		m.data[2][0] = instruction_to_float(m_instructions[*instr + 8]);
		m.data[2][1] = instruction_to_float(m_instructions[*instr + 9]);
		m.data[2][2] = instruction_to_float(m_instructions[*instr + 10]);
		m.data[2][3] = instruction_to_float(m_instructions[*instr + 11]);
		m.data[3][0] = instruction_to_float(m_instructions[*instr + 12]);
		m.data[3][1] = instruction_to_float(m_instructions[*instr + 13]);
		m.data[3][2] = instruction_to_float(m_instructions[*instr + 14]);
		m.data[3][3] = instruction_to_float(m_instructions[*instr + 15]);
		(*instr) += 16;
		return m;
	}
	
	const char *read_string(int *instr) const
	{
		const char *s = (const char *)(&m_instructions[*instr]);
		const char *c = s;
		while (true) {
			++(*instr);
			if (c[0]=='\0' || c[1]=='\0' || c[2]=='\0' || c[3]=='\0')
				break;
			c += 4;
		}
		return s;
	}
	
	void add_instruction(Instruction v);
	int get_instruction_count() const { return m_instructions.size(); }
	
	int entry_point() const { return m_entry_point; }
	void set_entry_point(int entry_point);
	
protected:
	Instructions m_instructions;
	int m_entry_point;
	
	MEM_CXX_CLASS_ALLOC_FUNCS("BVM:InstructionList")
};

} /* namespace bvm */

#endif /* __BVM_INSTRUCTION_LIST_H__ */
