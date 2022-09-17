#include "helpingFunc.h"
#include "main.h"
#include <string.h>

void print_starting_cmd()
{
    printf("amar sqlite %d.%d a apnake shagotom\r\n", MAJOR_VERSION, MINOR_VERSION);
}

void print_prompt()
{
    printf("mySqlite>");
}

InputBuffer* new_input_buffer()
{
    InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;

    return input_buffer;
}

void read_input(InputBuffer* input_buffer)
{
    size_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
    if (bytes_read <= 0)
    {
        printf("Error Reading\r\n");
        exit(EXIT_FAILURE);
    }

}


StringTokenResult isToken(char* buffer, char* token)
{
    if (strncmp(buffer, token, strlen(token)) == 0) {
        return STRING_TOKEN_MATCHED;
    }
    return STRING_TOKEN_UNMATCHED;
}

MetaCmdExecuteResult execute_meta_cmd(InputBuffer* input_buffer)
{
    if(isToken(&(input_buffer->buffer[1]), "exit") == STRING_TOKEN_MATCHED) {
        free_input_buffer(input_buffer);
        exit(EXIT_SUCCESS);
    } else if (0) {
        printf("will do later");
    } else {
        return META_CMD_UNRECOGNIZED_CMD;
    }

    return META_CMD_SUCCESS;
}

void free_input_buffer(InputBuffer* input_buffer)
{
    free(input_buffer->buffer);
    input_buffer->buffer = NULL;
    free(input_buffer);
    input_buffer = NULL;
}


PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement)
{
    if ( isToken(input_buffer->buffer, "SELECT") == STRING_TOKEN_MATCHED ) {
        statement->type = STATEMENT_SELECT;
    } else if ( isToken(input_buffer->buffer, "INSERT") == STRING_TOKEN_MATCHED ) {
        statement->type = STATEMENT_INSERT;
    } else {
        return PREPARE_UNRECOGNIZED_STATEMENT;
    }

    return PREPARE_SUCCESS;

}
