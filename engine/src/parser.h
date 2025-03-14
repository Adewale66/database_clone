#ifndef __PARSER_H
#define __PARSER_H

#include <stdarg.h>
#include "lexer.h"
#include "stmt.h"

typedef struct
{
	TokenList tokenlist;
	int current;

} Parser;

void intiParser(TokenList tokens);

#endif
