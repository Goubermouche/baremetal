#pragma once
#include "assembler/block.h"

namespace baremetal {
	struct assembler {
		assembler();

#define INST(index, name, op1, op2)                                 \
  void name(op1 destination, op2 source) {                          \
    emit_instruction(index, destination, source); \
  }

#include "assembler_database.inc"

		[[nodiscard]] auto get_bytes() const -> const utility::dynamic_array<utility::byte>&;
	private:
		static auto find_rex_pair(const operand* operands) -> std::pair<u8, u8>;

		static auto get_instruction_info(u32 index, operand op_1, operand op_2) -> const instruction_info*;

		void emit_instruction_prefix(const instruction_info* inst);
		void emit_instruction_opcode(const instruction_info* inst, operand op_1, operand op_2);
		void emit_instruction_modrm(const instruction_info* inst, operand op_1, operand op_2);
		void emit_instruction_sib(const instruction_info* inst, operand op_1, operand op_2);
		void emit_immediate_operand(u64 imm, enum operand::type type);

		void emit_instruction(u32 index, operand op_1, operand op_2);

		static auto has_sib_byte(const instruction_info* inst, operand op_1, operand op_2) -> bool;

		enum mod_mode {
			INDIRECT,
			INDIRECT_DISP8,
			INDIRECT_DISP32,
			DIRECT
		};

		static auto sib(u8 scale, u8 index, u8 base) -> u8;

		/**
		 * \brief Computes the REX opcode byte.
		 * \param w REX.W bit (64 bit mode)
		 * \param rx Register register extension
		 * \param base Base register extension
		 * \param index Index register extension
		 * \return Computed REX opcode byte.
		 */
		static auto rex(bool w, u8 rx, u8 base, u8 index) -> u8;

		/**
		 * \brief Computes the mod R/M byte
		 * \param mod Addressing mode (INDIRECT, INDIRECT_DISP8, INDIRECT_DISP32, DIRECT)
		 * \param rx Opcode or register extension
		 * \param rm Register operand / displacement
		 * \return Computed mod R/M byte
		 */
		static auto mod_rx_rm(u8 mod, u8 rx, u8 rm) -> u8;

		static auto direct(u8 rx, u8 reg) -> u8;
		static auto indirect(u8 rx, u8 base) -> u8;
		static auto indirect_disp_8(u8 rx, u8 base) -> u8;
		static auto indirect_disp_32(u8 rx, u8 base) -> u8;

		void instruction_begin();
		auto get_current_inst_size() const -> u8;
	private:
		utility::dynamic_array<utility::byte> m_bytes;
		u64 m_current_inst_begin;
	};

	static constexpr rax rax;
	static constexpr rcx rcx;
	static constexpr rdx rdx;
	static constexpr rbx rbx;
	static constexpr rsp rsp;
	static constexpr rbp rbp;
	static constexpr rsi rsi;
	static constexpr rdi rdi;
	static constexpr r8  r8 ;
	static constexpr r9  r9 ;
	static constexpr r10 r10;
	static constexpr r11 r11;
	static constexpr r12 r12;
	static constexpr r13 r13;
	static constexpr r14 r14;
	static constexpr r15 r15;

	static constexpr eax eax;
	static constexpr ecx ecx;
	static constexpr edx edx;
	static constexpr ebx ebx;
	static constexpr esp esp;
	static constexpr ebp ebp;
	static constexpr esi esi;
	static constexpr edi edi;
	static constexpr r8d r8d;
	static constexpr r9d r9d;
	static constexpr r10d r10d;
	static constexpr r11d r11d;
	static constexpr r12d r12d;
	static constexpr r13d r13d;
	static constexpr r14d r14d;
	static constexpr r15d r15d;

	static constexpr ax ax;
	static constexpr cx cx;
	static constexpr dx dx;
	static constexpr bx bx;
	static constexpr sp sp;
	static constexpr bp bp;
	static constexpr si si;
	static constexpr di di;
	static constexpr r8w r8w;
	static constexpr r9w r9w;
	static constexpr r10w r10w;
	static constexpr r11w r11w;
	static constexpr r12w r12w;
	static constexpr r13w r13w;
	static constexpr r14w r14w;
	static constexpr r15w r15w;

	static constexpr al al;
	static constexpr cl cl;
	static constexpr dl dl;
	static constexpr bl bl;
	static constexpr ah ah;
	static constexpr ch ch;
	static constexpr dh dh;
	static constexpr bh bh;

	static constexpr rip rip;

	static inline auto is_stack_pointer(reg r) -> bool {
		// TODO: spl
		return r.index == rsp.index; // rsp, esp, sp
	}
} // namespace baremetal
