#ifndef HELPINGFUNC_H_INCLUDED
#define HELPINGFUNC_H_INCLUDED
#include "main.h"

#define MAJOR_VERSION 0
#define MINOR_VERSION 1

void print_starting_cmd();
void print_prompt();
InputBuffer* new_input_buffer();
void read_input(InputBuffer* input_buffer);
PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);
MetaCmdExecuteResult execute_meta_cmd(InputBuffer* input_buffer);
void free_input_buffer(InputBuffer* input_buffer);

#endif // HELPINGFUNC_H_INCLUDED
