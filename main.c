#include <stdio.h>
#include <stdlib.h>

#include "helpingFunc.h"
#include "main.h"

int main()
{
    print_starting_cmd();
    InputBuffer* input_buffer = new_input_buffer();
    Table *table = new_table();
    while(1) {
            print_prompt();
            // read from cmd line
            read_input(input_buffer);

            // check if it is meta cmd and if it is then execute
            if(input_buffer->buffer[0] == '.') {
                switch(execute_meta_cmd(input_buffer)) {
                    case META_CMD_SUCCESS:
                        continue;
                    case META_CMD_UNRECOGNIZED_CMD:
                        printf("Not a valid cmd\n");
                        continue;
                    default:
                        break;
                }
                printf("Execute Meta command\n");

                continue;
            }

            // otherwise, for statement, parse the statement and execute

            Statement statement;
            switch(prepare_statement(input_buffer, &statement))
            {
                case PREPARE_SUCCESS:
                    printf("preparation successful\n");
                    break;
                case PREPARE_UNRECOGNIZED_STATEMENT:
                    printf("Statement not recognized\n");
                    continue;
                default:
                    break;
            }

            switch(execute_statement(&statement,table)) {
                case EXECUTE_CMD_SUCCESS:
                    break;
                case EXECUTE_CMD_FAILURE:
                    printf("Cmd failed\r\n");
                    break;
                case EXECUTE_TABLE_FULL:
                    printf("Table is full\r\n");
                    break;
                default:
                    break;
            }
            printf("Executed\r\n");
    }
    return 0;
}
