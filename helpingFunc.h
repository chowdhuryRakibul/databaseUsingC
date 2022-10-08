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
PrepareResult prepare_insert(InputBuffer* input_buffer, Statement* statement);
Table *new_table();
void free_table(Table* pTable);
PrepareResult prepare_select(Statement* statement, Table* table);

void serialize_row(Row* source, void *destination);
void deserialize_row(void *source, Row *destination);

ExecuteResult execute_statement(Statement *statement, Table* table);
ExecuteResult execute_select(Statement *statement, Table* table);
void *row_slot(Table* table, uint32_t row_num);
void print_row(Row row);
ExecuteResult execute_insert(Statement *statement, Table* table);

#endif // HELPINGFUNC_H_INCLUDED
