
#ifndef __PARSER_RUN_H
#define __PARSER_RUN_H

@begin
include "parser_code.h"
@end

/*
 * definition of generated structures
 */

// -- parser_run_s --
@begin
struct
    <
    pointer:parser_ptr
    lalr_stack_s:lalr_stack
    >
    additions
{
  bool create_from_parser(parser_s &a_parser);
  bool parse_source_string(string_s &a_source_string);
}
parser_run_s;
@end

/*
 * inline methods of generated structures
 */

// -- parser_run_s --
@begin
inlines parser_run_s
@end

#endif



