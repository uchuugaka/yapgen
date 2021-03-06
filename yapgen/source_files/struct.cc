
@begin
include "struct.h"
@end

/*
 * methods of generated structures
 */

// -- bc_array_s --
@begin
methods bc_array_s
@end

void bc_array_s::replace(string_s &a_src,string_s &a_old_str,string_s &a_new_str)
{/*{{{*/
  clear();

  unsigned idx = 0;
  do
  {
    unsigned old_idx = idx;
    idx = a_src.get_idx(idx,a_old_str.size - 1,a_old_str.data);

    if (idx == c_idx_not_exist)
    {
      idx = a_src.size - 1;
    }

    // - append part of original string to buffer -
    append(idx - old_idx,a_src.data + old_idx);

    if (idx >= a_src.size - 1)
    {
      break;
    }

    // - append new string to buffer -
    append(a_new_str.size - 1,a_new_str.data);

    // - jump over substring -
    idx += a_old_str.size - 1;
  }
  while(true);
}/*}}}*/

// -- bi_array_s --
@begin
methods bi_array_s
@end

// -- ui_array_s --
@begin
methods ui_array_s
@end

// -- lli_array_s --
@begin
methods lli_array_s
@end

// -- uli_array_s --
@begin
   methods uli_array_s
@end

// -- lli_rb_tree_s --
@begin
methods lli_rb_tree_s
@end

// -- ui_queue_s --
@begin
methods ui_queue_s
@end

// -- pointer_array_s --
@begin
methods pointer_array_s
@end

// -- ui_arrays_s --
@begin
methods ui_arrays_s
@end

// -- bf_array_s --
@begin
methods bf_array_s
@end

// -- bd_array_s --
@begin
methods bd_array_s
@end

// -- bd_rb_tree_s --
@begin
methods bd_rb_tree_s
@end

// -- ui_arrays_array_s --
@begin
methods ui_arrays_array_s
@end

// -- string_array_s --
@begin
methods string_array_s
@end

unsigned string_array_s::get_idx_char_ptr(unsigned a_length,const char *a_data)
{/*{{{*/
  if (used == 0) return c_idx_not_exist;

  string_s *ptr = data;
  string_s *ptr_end = ptr + used;

  do
  {
    if (ptr->compare_char_ptr(a_length,a_data))
    {
      return ptr - data;
    }
  }
  while(++ptr < ptr_end);

  return c_idx_not_exist;
}/*}}}*/

void string_array_s::join(string_s &a_string)
{/*{{{*/
  a_string.clear();

  if (used != 0)
  {
    unsigned string_length = 0;

    // - compute target string length -
    string_s *s_ptr = data;
    string_s *s_ptr_end = s_ptr + used;
    do {
      string_length += s_ptr->size - 1;
    } while(++s_ptr < s_ptr_end);

    // - create target string -
    a_string.create(string_length);

    // - join strings to target string -
    s_ptr = data;
    s_ptr_end = s_ptr + used;
    char *ptr = a_string.data;
    do {
      memcpy(ptr,s_ptr->data,s_ptr->size - 1);
      ptr += s_ptr->size - 1;
    } while(++s_ptr < s_ptr_end);
  }
}/*}}}*/

void string_array_s::split(string_s &a_string,unsigned a_length,const char *a_data)
{/*{{{*/
  clear();

  unsigned idx = 0;
  do
  {
    unsigned old_idx = idx;
    idx = a_string.get_idx(idx,a_length,a_data);

    if (idx == c_idx_not_exist)
    {
      idx = a_string.size - 1;
    }

    // - push string to array -
    push_blank();
    data[used - 1].set(idx - old_idx,a_string.data + old_idx);

    if (idx >= a_string.size - 1)
    {
      break;
    }

    // - jump over substring -
    idx += a_length;
  }
  while(true);
}/*}}}*/

// -- string_rb_tree_s --
@begin
methods string_rb_tree_s
@end

// -- name_pos_s --
// -- ri_ep_s --
// -- idx_size_s --
@begin
methods name_pos_s
@end

// -- lalr_stack_element_s --
@begin
methods lalr_stack_element_s
@end

// -- lalr_stack_s --
@begin
methods lalr_stack_s
@end

// -- source_s --
@begin
methods source_s
@end

// -- source_array_s --
@begin
methods source_array_s
@end

