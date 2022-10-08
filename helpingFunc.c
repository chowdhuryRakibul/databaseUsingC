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
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
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
//        free_table();
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

PrepareResult prepare_insert(InputBuffer* input_buffer, Statement* statement)
{
    statement->type = STATEMENT_INSERT;

    //INSERT 1,shimanto chowdhury,shimanto.buet@gmail.com
    char *keyword = strtok(input_buffer->buffer, " ");
    char *id_string = strtok(NULL, ",");
    char *user_name = strtok(NULL, ",");
    char *email = strtok(NULL, ",");

    if (id_string == NULL || user_name == NULL || email == NULL) {
        return PREPARE_SYNTAX_ERROR;
    }

    int id = atoi(id_string);
    if (id < 0) {
        return PREPARE_NEGATIVE_ID;
    }

    if (strlen(user_name) > COLUMN_USR_NAME_SIZE) {
        return PREPARE_STRING_TOO_LONG;
    }

    statement->row_to_insert.id = id;
    strcpy(statement->row_to_insert.username, user_name);
    strcpy(statement->row_to_insert.email, email);

    return PREPARE_SUCCESS;
}


PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement)
{
    if ( isToken(input_buffer->buffer, "SELECT") == STRING_TOKEN_MATCHED ) {
        statement->type = STATEMENT_SELECT;
    } else if ( isToken(input_buffer->buffer, "INSERT") == STRING_TOKEN_MATCHED ) {
        prepare_insert(input_buffer, statement);
    } else {
        return PREPARE_UNRECOGNIZED_STATEMENT;
    }

    return PREPARE_SUCCESS;
}

Table *new_table()
{
    Table *pTable = (Table *)malloc(sizeof(Table));
    pTable->num_rows = 0;
    for(int i = 0; i< TABLE_MAX_PAGES; i++)
    {
        pTable->pages[i] = NULL;
    }
    return pTable;
}

void free_table(Table* pTable)
{
    for(int i = 0; i< TABLE_MAX_PAGES; i++)
    {
        free(pTable->pages[i]);
        pTable->pages[i] = NULL;
    }
    free(pTable);
    pTable = NULL;
}

void serialize_row(Row* source, void *destination)
{
    memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
    memcpy(destination + USERNAME_OFFSET, source->username, USERNAME_SIZE);
    memcpy(destination + EMAIL_OFFSET, source->email, EMAIL_SIZE);
}

void deserialize_row(void *source, Row *destination)
{
    memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
    memcpy(destination->username, source + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(destination->email, source + EMAIL_OFFSET, EMAIL_SIZE);
}

ExecuteResult execute_insert(Statement *statement, Table* table)
{
    if (table->num_rows >= TABLE_MAX_ROWS) {
        return EXECUTE_TABLE_FULL;
    }

    Row *row_to_insert = &(statement->row_to_insert);

    serialize_row(row_to_insert,row_slot(table,table->num_rows));
    table->num_rows += 1;

    return EXECUTE_CMD_SUCCESS;
}

void print_row(Row row)
{
    printf("%d | %s | %s\r\n",row.id,row.username,row.email);
}


void *row_slot(Table* table, uint32_t row_num)
{
    uint32_t page_num = row_num/(ROWS_PER_PAGE);
    void *page = table->pages[page_num];

    if(page == NULL) {
        page = table->pages[page_num] = malloc(PAGE_SIZE);
    }

    uint32_t row_offset = row_num % (ROWS_PER_PAGE);
    uint32_t byte_offset = row_offset * ROW_SIZE;

    return (page + byte_offset);
}


ExecuteResult execute_select(Statement *statement, Table* table)
{
    Row row;
    for(uint32_t i = 0; i< table->num_rows; i++) {
        deserialize_row(row_slot(table, i),&row);
        print_row(row);
    }
    return EXECUTE_CMD_SUCCESS;
}


ExecuteResult execute_statement(Statement *statement, Table* table)
{
    switch (statement->type) {
    case (STATEMENT_INSERT):
        return execute_insert(statement, table);
    case STATEMENT_SELECT:
        return execute_select(statement, table);
    default:
        break;
    }
    return EXECUTE_CMD_FAILURE;
}
