#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include "helpingFunc.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define COLUMN_USR_NAME_SIZE    (32UL)
#define COLUMN_EMAIL_SIZE       (255UL)

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

#define TABLE_MAX_PAGES (100UL)  // number of pages in the table
#define PAGE_SIZE       (4096UL) // per page size in bytes

typedef struct _row {
    uint32_t id;
    char username[COLUMN_USR_NAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
}Row;

typedef struct _table {
    uint32_t num_rows;
    void *pages[TABLE_MAX_PAGES];
}Table;


typedef struct _inputBuffer_t {
    char *buffer;
    size_t buffer_length;
}InputBuffer;

typedef enum {
    STATEMENT_SELECT,
    STATEMENT_INSERT
} StatementType;

typedef struct _statement_t {
    StatementType type;
    Row row_to_insert;
} Statement;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT,
    PREPARE_SYNTAX_ERROR,
    PREPARE_NEGATIVE_ID,
    PREPARE_STRING_TOO_LONG
}PrepareResult;

typedef enum {
    STRING_TOKEN_MATCHED,
    STRING_TOKEN_UNMATCHED
}StringTokenResult;

typedef enum {
    META_CMD_SUCCESS,
    META_CMD_UNRECOGNIZED_CMD
}MetaCmdExecuteResult;

typedef enum {
    EXECUTE_CMD_SUCCESS,
    EXECUTE_CMD_FAILURE,
    EXECUTE_TABLE_FULL
} ExecuteResult;

#define ID_SIZE         size_of_attribute(Row, id)
#define USERNAME_SIZE   size_of_attribute(Row, username)
#define EMAIL_SIZE      size_of_attribute(Row, email)
#define ROW_SIZE        ID_SIZE+USERNAME_SIZE+EMAIL_SIZE

//#define ID_SIZE         32UL
//#define USERNAME_SIZE   32UL
//#define EMAIL_SIZE      255UL
//#define ROW_SIZE        ID_SIZE+USERNAME_SIZE+EMAIL_SIZE


#define ID_OFFSET       0UL
#define USERNAME_OFFSET  ID_OFFSET+USERNAME_SIZE
#define EMAIL_OFFSET    USERNAME_OFFSET+EMAIL_SIZE

#define ROWS_PER_PAGE   (PAGE_SIZE/ROW_SIZE)

#define TABLE_MAX_ROWS  (TABLE_MAX_PAGES*ROWS_PER_PAGE)

#endif // MAIN_H_INCLUDED
