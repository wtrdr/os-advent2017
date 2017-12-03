/* Generated automatically by the program 'build/genpreds'
   from the machine description file '../../gcc-7.2.0/gcc/config/h8300/h8300.md'.  */

#ifndef GCC_TM_PREDS_H
#define GCC_TM_PREDS_H

#ifdef HAVE_MACHINE_MODES
extern int general_operand (rtx, machine_mode);
extern int address_operand (rtx, machine_mode);
extern int register_operand (rtx, machine_mode);
extern int pmode_register_operand (rtx, machine_mode);
extern int scratch_operand (rtx, machine_mode);
extern int immediate_operand (rtx, machine_mode);
extern int const_int_operand (rtx, machine_mode);
extern int const_double_operand (rtx, machine_mode);
extern int nonimmediate_operand (rtx, machine_mode);
extern int nonmemory_operand (rtx, machine_mode);
extern int push_operand (rtx, machine_mode);
extern int pop_operand (rtx, machine_mode);
extern int memory_operand (rtx, machine_mode);
extern int indirect_operand (rtx, machine_mode);
extern int ordered_comparison_operator (rtx, machine_mode);
extern int comparison_operator (rtx, machine_mode);
extern int general_operand_src (rtx, machine_mode);
extern int general_operand_dst (rtx, machine_mode);
extern int h8300_src_operand (rtx, machine_mode);
extern int h8300_dst_operand (rtx, machine_mode);
extern int nibble_operand (rtx, machine_mode);
extern int reg_or_nibble_operand (rtx, machine_mode);
extern int h8sx_unary_shift_operator (rtx, machine_mode);
extern int h8sx_binary_shift_operator (rtx, machine_mode);
extern int h8sx_binary_memory_operator (rtx, machine_mode);
extern int h8sx_unary_memory_operator (rtx, machine_mode);
extern int h8300_ldm_parallel (rtx, machine_mode);
extern int h8300_stm_parallel (rtx, machine_mode);
extern int h8300_return_parallel (rtx, machine_mode);
extern int single_one_operand (rtx, machine_mode);
extern int single_zero_operand (rtx, machine_mode);
extern int call_insn_operand (rtx, machine_mode);
extern int small_call_insn_operand (rtx, machine_mode);
extern int jump_address_operand (rtx, machine_mode);
extern int two_insn_adds_subs_operand (rtx, machine_mode);
extern int bit_operand (rtx, machine_mode);
extern int bit_memory_operand (rtx, machine_mode);
extern int bit_register_indirect_operand (rtx, machine_mode);
extern int stack_pointer_operand (rtx, machine_mode);
extern int register_no_sp_elim_operand (rtx, machine_mode);
extern int const_int_gt_2_operand (rtx, machine_mode);
extern int const_int_ge_8_operand (rtx, machine_mode);
extern int const_int_qi_operand (rtx, machine_mode);
extern int const_int_hi_operand (rtx, machine_mode);
extern int incdec_operand (rtx, machine_mode);
extern int bit_operator (rtx, machine_mode);
extern int nshift_operator (rtx, machine_mode);
extern int eqne_operator (rtx, machine_mode);
extern int gtle_operator (rtx, machine_mode);
extern int gtuleu_operator (rtx, machine_mode);
extern int iorxor_operator (rtx, machine_mode);
#endif /* HAVE_MACHINE_MODES */

#define CONSTRAINT_NUM_DEFINED_P 1
enum constraint_num
{
  CONSTRAINT__UNKNOWN = 0,
  CONSTRAINT_r,
  CONSTRAINT_a,
  CONSTRAINT_c,
  CONSTRAINT_d,
  CONSTRAINT_D,
  CONSTRAINT_f,
  CONSTRAINT_I,
  CONSTRAINT_J,
  CONSTRAINT_L,
  CONSTRAINT_M,
  CONSTRAINT_N,
  CONSTRAINT_O,
  CONSTRAINT_P1_gX,
  CONSTRAINT_P3_gX,
  CONSTRAINT_P4_gX,
  CONSTRAINT_P5_gX,
  CONSTRAINT_P8_gX,
  CONSTRAINT_P3_lX,
  CONSTRAINT_m,
  CONSTRAINT_o,
  CONSTRAINT_WU,
  CONSTRAINT_p,
  CONSTRAINT_G,
  CONSTRAINT_R,
  CONSTRAINT_S,
  CONSTRAINT_T,
  CONSTRAINT_Y0,
  CONSTRAINT_Y2,
  CONSTRAINT_V,
  CONSTRAINT__l,
  CONSTRAINT__g,
  CONSTRAINT_Z,
  CONSTRAINT_i,
  CONSTRAINT_s,
  CONSTRAINT_n,
  CONSTRAINT_E,
  CONSTRAINT_F,
  CONSTRAINT_X,
  CONSTRAINT_Q,
  CONSTRAINT_U,
  CONSTRAINT__LIMIT
};

extern enum constraint_num lookup_constraint_1 (const char *);
extern const unsigned char lookup_constraint_array[];

/* Return the constraint at the beginning of P, or CONSTRAINT__UNKNOWN if it
   isn't recognized.  */

static inline enum constraint_num
lookup_constraint (const char *p)
{
  unsigned int index = lookup_constraint_array[(unsigned char) *p];
  return (index == UCHAR_MAX
          ? lookup_constraint_1 (p)
          : (enum constraint_num) index);
}

extern bool (*constraint_satisfied_p_array[]) (rtx);

/* Return true if X satisfies constraint C.  */

static inline bool
constraint_satisfied_p (rtx x, enum constraint_num c)
{
  int i = (int) c - (int) CONSTRAINT_I;
  return i >= 0 && constraint_satisfied_p_array[i] (x);
}

static inline bool
insn_extra_register_constraint (enum constraint_num c)
{
  return c >= CONSTRAINT_r && c <= CONSTRAINT_f;
}

static inline bool
insn_extra_memory_constraint (enum constraint_num c)
{
  return c >= CONSTRAINT_m && c <= CONSTRAINT_WU;
}

static inline bool
insn_extra_special_memory_constraint (enum constraint_num)
{
  return false;
}

static inline bool
insn_extra_address_constraint (enum constraint_num c)
{
  return c >= CONSTRAINT_p && c <= CONSTRAINT_p;
}

static inline void
insn_extra_constraint_allows_reg_mem (enum constraint_num c,
				      bool *allows_reg, bool *allows_mem)
{
  if (c >= CONSTRAINT_G && c <= CONSTRAINT_Y2)
    return;
  if (c >= CONSTRAINT_V && c <= CONSTRAINT_Z)
    {
      *allows_mem = true;
      return;
    }
  (void) c;
  *allows_reg = true;
  *allows_mem = true;
}

static inline size_t
insn_constraint_len (char fc, const char *str ATTRIBUTE_UNUSED)
{
  switch (fc)
    {
    case 'P': return 4;
    case 'W': return 2;
    case 'Y': return 2;
    default: break;
    }
  return 1;
}

#define CONSTRAINT_LEN(c_,s_) insn_constraint_len (c_,s_)

extern enum reg_class reg_class_for_constraint_1 (enum constraint_num);

static inline enum reg_class
reg_class_for_constraint (enum constraint_num c)
{
  if (insn_extra_register_constraint (c))
    return reg_class_for_constraint_1 (c);
  return NO_REGS;
}

extern bool insn_const_int_ok_for_constraint (HOST_WIDE_INT, enum constraint_num);
#define CONST_OK_FOR_CONSTRAINT_P(v_,c_,s_) \
    insn_const_int_ok_for_constraint (v_, lookup_constraint (s_))

enum constraint_type
{
  CT_REGISTER,
  CT_CONST_INT,
  CT_MEMORY,
  CT_SPECIAL_MEMORY,
  CT_ADDRESS,
  CT_FIXED_FORM
};

static inline enum constraint_type
get_constraint_type (enum constraint_num c)
{
  if (c >= CONSTRAINT_p)
    {
      if (c >= CONSTRAINT_G)
        return CT_FIXED_FORM;
      return CT_ADDRESS;
    }
  if (c >= CONSTRAINT_m)
    return CT_MEMORY;
  if (c >= CONSTRAINT_I)
    return CT_CONST_INT;
  return CT_REGISTER;
}
#endif /* tm-preds.h */
