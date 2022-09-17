#include <stdio.h>
#include <stdlib.h>

#include "helpingFunc.h"
#include "main.h"

int main()
{
    print_starting_cmd();
    InputBuffer* input_buffer = new_input_buffer();

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

//            execute_statement(statement);
            printf("Executed\r\n");
    }
    return 0;
}
