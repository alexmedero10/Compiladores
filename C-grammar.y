%{
	#include <stdio.h>	
%}

%token IDENTIFIER CONSTANT
%token INC_OP DEC_OP LE_OP GE_OP EQ_OP NE_OP
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN

%token CHAR INT VOID

%token IF WHILE RETURN

%start function_definition
%%

primary_expression
	: IDENTIFIER
	| CONSTANT
	;

postfix_expression
	: primary_expression
	| postfix_expression INC_OP									{printf("Sumar 1 a la variable");}	
	| postfix_expression DEC_OP 								{printf("Restar 1 a la variable");}
	;

unary_expression
	: postfix_expression
	| INC_OP unary_expression
	| DEC_OP unary_expression
	;

multiplicative_expression
	: unary_expression
	| multiplicative_expression '*' unary_expression 				{printf("Multiplicar IDENTIFIER O CONSTANT");}
	| multiplicative_expression '/' unary_expression 				{printf("Dividir IDENTIFIER O CONSTANT");}
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression 			{printf("Sumar IDENTIFIER O CONSTANT");}
	| additive_expression '-' multiplicative_expression 			{printf("Restar IDENTIFIER O CONSTANT");}
	;

relational_expression
	: additive_expression
	| relational_expression '<' additive_expression 				{printf("Comparar si IDENTIFIER O CONSTANT son menor a IDENTIFIER O CONSTANT y regresar 1 o 0");}
	| relational_expression '>' additive_expression 				{printf("Comparar si IDENTIFIER O CONSTANT son mayor a IDENTIFIER O CONSTANT y regresar 1 o 0");}
	| relational_expression LE_OP additive_expression 				{printf("Comparar si IDENTIFIER O CONSTANT son menor o igual a IDENTIFIER O CONSTANT y regresar 1 o 0");}
	| relational_expression GE_OP additive_expression 				{printf("Comparar si IDENTIFIER O CONSTANT son mayor a IDENTIFIER O CONSTANT y regresar 1 o 0");}
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression 	 			{printf("Comparar si IDENTIFIER O CONSTANT son igual a IDENTIFIER O CONSTANT y regresar 1 o 0");}
	| equality_expression NE_OP relational_expression  				{printf("Comparar si IDENTIFIER O CONSTANT son diferente a IDENTIFIER O CONSTANT y regresar 1 o 0");}
	;

expression
	: equality_expression
	| unary_expression '=' expression      					{printf("Asignar valor a variable previamente inicializada");}
	;

declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator ';'			{printf("Variable inicializada");}
	;

declaration_specifiers
	: type_specifier
	| type_specifier declaration_specifiers
	;

init_declarator
	: declarator
	| declarator '=' expression 							{printf("Inicializar variable");}
	;

declarator
	: IDENTIFIER
	| declarator '(' ')'
	;

type_specifier
	: VOID
	| CHAR
	| INT
	;

statement
	: compound_statement
	| expression_statement
	| IF '(' expression ')' statement 						{printf("Si expression devuelve 1 entrar al IF");}
	| WHILE '(' expression ')' statement 					{printf("Si expression devuelve 1 entrar al WHILE");}
	| jump_statement
	;

compound_statement
	: '{' '}'
	| '{' statement_list '}'
	| '{' declaration '}'
	| '{' declaration statement_list '}'
	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
	: ';'
	| expression ';'
	;

jump_statement
	: RETURN ';'
	| RETURN expression ';'
	;

function_definition
	: declaration_specifiers declarator compound_statement	
	;

%%
extern char yytext[];
extern int column;

main(){
	if(yyparse()==0)
    	printf("Análisis completado sin errores\n");
}

yyerror(char *s){
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}

/*
yyerror(char *msg){
    printf("%s\n", msg);
}
*/