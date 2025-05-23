#include <strings.h>
#include "../../include/parser.h"

static SelectStmt *checkClause(SelectStmt *select, Scanner *scanner, Token *token)
{
	scanToken(scanner, token);
	if (token->type != TOKEN_SEMICOLON)
	{
		ERROR_STMT("expected semicolon.", select, free_select)
	}
	return select;
}

static SelectStmt *parseTable(SelectStmt *select, Scanner *scanner, Token *token)
{

	if (token->type != TOKEN_FROM)
	{
		ERROR_STMT("Invalid sql statement.", select, free_select);
	}
	scanToken(scanner, token);
	if (token->type != TOKEN_IDENTIFIER)
	{
		ERROR_STMT("Invalid sql statement.", select, free_select);
	}
	select->from = COPY_STRING(token->literal);

	return checkClause(select, scanner, token);
}

static SelectStmt *parseColumns(SelectStmt *select, Scanner *scanner, Token *token)
{
	scanToken(scanner, token);
	bool comma = false;

	while (token->type == TOKEN_IDENTIFIER)
	{
		comma = false;
		Expression column;
		column.type = LITERAL;
		column.literal = ALLOCATE_MEMORY(Literal, sizeof(Literal));
		column.literal->value = NULL;

		if (select->column_capacity < select->column_count + 1)
		{
			select->column_capacity = GROW_CAPACITY(select->column_capacity);
			select->columns = GROW_ARRAY(Expression, select->columns, select->column_capacity);
		}
		column.literal->value = COPY_STRING((char *)token->literal);
		select->columns[select->column_count++] = column;

		scanToken(scanner, token);
		if (token->type == TOKEN_COMMA)
		{
			comma = true;
			scanToken(scanner, token);
		}
		else
		{
			break;
		}
	}

	if (select->column_count == 0 || comma)
	{
		ERROR_STMT("Unpected identifier", select, free_select);
	}

	return parseTable(select, scanner, token);
}

SelectStmt *select_statement(Scanner *scanner, Token *token)
{
	SelectStmt *select = ALLOCATE_MEMORY(SelectStmt, sizeof(SelectStmt));
	select->column_capacity = 0;
	select->column_count = 0;
	select->columns = NULL;
	select->from = NULL;
	return parseColumns(select, scanner, token);
}

void free_select(SelectStmt *select)
{

	if (select == NULL)
		return;

	if (select->column_count > 0)
	{
		for (int i = 0; i < select->column_count; i++)
		{
			free(select->columns[i].literal->value);
			free(select->columns[i].literal);
		}
		free(select->columns);
		select->column_count = 0;
	}

	if (select->from != NULL)
		free(select->from);
	free(select);
	select = NULL;
}
