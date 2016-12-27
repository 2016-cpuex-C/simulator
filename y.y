%{
#include <stdio.h>
#include <string.h>
#include "execute.c"
#include "global.h"

static int op[MEM_SIZE][5];
static char label[2 * MEM_SIZE][MAX_STR];
static char string[MEM_SIZE][MAX_STR];
static int32_t word[2 * MEM_SIZE][MAX_STR];

int pc = 1;
int lc = 0;
int inner_lc = 0;
FILE *f;
int parse_error_flag = 0;
extern FILE *yyin;
%}

%union {
int num;
char* str;
}


%type <num> MOVE
%type <num> NEG
%type <num> ADD
%type <num> ADDI
%type <num> SUB
%type <num> SUBI
%type <num> MULT
%type <num> MULTI
%type <num> DIV
%type <num> DIVI
%type <num> MOVS
%type <num> NEGS
%type <num> ADDS
%type <num> SUBS
%type <num> MULS
%type <num> DIVS
%type <num> SRL
%type <num> SLL
%type <num> LI
%type <num> LA
%type <num> LWL
%type <num> LWR
%type <num> LSL
%type <num> LSR
%type <num> SW
%type <num> SS
%type <num> BEQ
%type <num> BNE
%type <num> BLT
%type <num> BGT
%type <num> CEQS
%type <num> CLES
%type <num> CLTS
%type <num> J
%type <num> JR
%type <num> JAL
%type <num> JALR
%type <num> PRINTI
%type <num> PRINTF
%type <num> PRINTC
%type <num> READI
%type <num> READF
%type <num> SIN
%type <num> COS
%type <num> ATAN
%type <num> FLOOR
%type <num> SQRT
%type <num> FTOI
%type <num> ITOF
%type <num> EXIT
%type <num> PRINTB
%type <num> BREAK

// 2nd
%type <num> CMPEQ
%type <num> CMPNE
%type <num> CMPLE
%type <num> CMPGE
%type <num> CMPLT
%type <num> CMPGT
%type <num> CMPIEQ
%type <num> CMPINE
%type <num> CMPILE
%type <num> CMPIGE
%type <num> CMPILT
%type <num> CMPIGT
%type <num> CMPEQS
%type <num> CMPNES
%type <num> CMPLES
%type <num> CMPGES
%type <num> CMPLTS
%type <num> CMPGTS
%type <num> BEQI
%type <num> BEQZ
%type <num> SWAP
%type <num> SWAPS
%type <num> SELECT
%type <num> SELECTS
%type <num> AND
%type <num> OR
%type <num> XOR
%type <num> ANDI
%type <num> ORI
%type <num> XORI

//pred
%type <num> CMP
%type <num> CMPI
%type <num> CMPS


%type <num> ENTER
%type <str> LABEL
%type <str> STRING
%type <num> DATA
%type <num> TEXT
%type <num> GLOBL
%type <num> ASCIIZ WORD
%type <str> HEX
%type <num> PREDICATE IMMEDIATE REGISTER F_REGISTER
%start list










%token MOVE
%token NEG
%token ADD
%token ADDI
%token SUB
%token SUBI
%token MULT
%token MULTI
%token DIV
%token DIVI
%token MOVS
%token NEGS
%token ADDS
%token SUBS
%token MULS
%token DIVS
%token SRL
%token SLL
%token LI
%token LA
%token LWL
%token LWR
%token LSL
%token LSR
%token SW
%token SS
%token BEQ
%token BNE
%token BLT
%token BGT
%token CEQS
%token CLES
%token CLTS
%token J
%token JR
%token JAL
%token JALR
%token PRINTI
%token PRINTF
%token PRINTC
%token READI
%token READF
%token SIN
%token COS
%token ATAN
%token FLOOR
%token SQRT
%token FTOI
%token ITOF
%token EXIT
%token PRINTB
%token BREAK
%token CMPEQ
%token CMPNE
%token CMPLE
%token CMPGE
%token CMPLT
%token CMPGT
%token CMPIEQ
%token CMPINE
%token CMPILE
%token CMPIGE
%token CMPILT
%token CMPIGT
%token CMPEQS
%token CMPNES
%token CMPLES
%token CMPGES
%token CMPLTS
%token CMPGTS
%token BEQI
%token BEQZ
%token SWAP
%token SWAPS
%token SELECT
%token SELECTS
%token AND
%token OR
%token XOR
%token ANDI
%token ORI
%token XORI

//pred
%token CMP
%token CMPI
%token CMPS


%token ENTER
%token STRING
%token LABEL
%token DATA
%token TEXT
%token GLOBL
%token ASCIIZ WORD
%token HEX
%token PREDICATE IMMEDIATE REGISTER F_REGISTER


%%

list:
    | list stat {
    }
    | list error {
    }
    ;
stat:
    | ENTER {
        pc += 1;
    }
    | DATA {
    }
    | GLOBL {
    }
    | TEXT {
    }
    | WORD HEX {
        fprintf(f, " word");
        word[lc + MEM_SIZE][inner_lc] = strtol($2, NULL, 16);
        inner_lc++;
    }
    | WORD IMMEDIATE {
        fprintf(f, " word");
        word[lc + MEM_SIZE][inner_lc] = $2;
        inner_lc++;
    }
    | ASCIIZ STRING {
        strcpy(string[lc], $2);
        inner_lc++;
    }
    | LABEL {
        fprintf(f, "\n%s", $1);
        strcpy(label[pc], $1);
        lc = pc;
        inner_lc = 0;
    }

    | MOVE REGISTER REGISTER  {
        fprintf(f, " move");
        op[pc][0] = MOVE; op[pc][1] = $2; op[pc][2] = $3;
    }
    | NEG REGISTER REGISTER {
        fprintf(f, " neg");
        op[pc][0] = NEG; op[pc][1] = $2; op[pc][2] = $3;
    }
    | ADD REGISTER REGISTER REGISTER  {
        fprintf(f, " add");
        op[pc][0] = ADD; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | ADDI REGISTER REGISTER IMMEDIATE  {
        fprintf(f, " addi");
        op[pc][0] = ADDI; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | SUB REGISTER REGISTER REGISTER  {
        fprintf(f, " sub");
        op[pc][0] = SUB; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | SUBI REGISTER REGISTER IMMEDIATE  {
        fprintf(f, " subi");
        op[pc][0] = SUBI; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | MULT REGISTER REGISTER REGISTER {
        fprintf(f, " mult");
        op[pc][0] = MULT; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | MULTI REGISTER REGISTER IMMEDIATE {
        fprintf(f, " multi");
        op[pc][0] = MULTI; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | DIV REGISTER REGISTER REGISTER {
        fprintf(f, " div");
        op[pc][0] = DIV; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | DIVI REGISTER REGISTER IMMEDIATE {
        fprintf(f, " divi");
        op[pc][0] = DIVI; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | MOVS F_REGISTER F_REGISTER {
        fprintf(f, " mov.s");
        op[pc][0] = MOVS; op[pc][1] = $2; op[pc][2] = $3;
    }
    | NEGS F_REGISTER F_REGISTER {
        fprintf(f, " neg.s");
        op[pc][0] = NEGS; op[pc][1] = $2; op[pc][2] = $3;
    }
    | ADDS F_REGISTER F_REGISTER F_REGISTER {
        fprintf(f, " add.s");
        op[pc][0] = ADDS; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | SUBS F_REGISTER F_REGISTER F_REGISTER {
        fprintf(f, " sub.s");
        op[pc][0] = SUBS; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | MULS F_REGISTER F_REGISTER F_REGISTER {
        fprintf(f, " mul.s");
        op[pc][0] = MULS; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | DIVS F_REGISTER F_REGISTER F_REGISTER {
        fprintf(f, " div.s");
        op[pc][0] = DIVS; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | SRL REGISTER REGISTER IMMEDIATE {
        fprintf(f, " srl");
        op[pc][0] = SRL; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | SLL REGISTER REGISTER IMMEDIATE {
        fprintf(f, " sll");
        op[pc][0] = SLL; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | LI REGISTER IMMEDIATE  {
        fprintf(f, " li");
        op[pc][0] = LI; op[pc][1] = $2; op[pc][2] = $3;
    }
    | LA REGISTER LABEL  {
        fprintf(f, " la");
        op[pc][0] = LA; op[pc][1] = $2; strcpy(label[pc], $3);
    }
    | LWL REGISTER LABEL  {
        fprintf(f, " lwl");
        op[pc][0] = LWL; op[pc][1] = $2; strcpy(label[pc], $3);
    }
    | LWR REGISTER IMMEDIATE REGISTER  {
        fprintf(f, " lwr");
        op[pc][0] = LWR; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | LSL F_REGISTER LABEL  {
        fprintf(f, " l.sl");
        op[pc][0] = LSL; op[pc][1] = $2; strcpy(label[pc], $3);
    }
    | LSR F_REGISTER IMMEDIATE REGISTER  {
        fprintf(f, " l.sr");
        op[pc][0] = LSR; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | SW REGISTER IMMEDIATE REGISTER  {
        fprintf(f, " sw");
        op[pc][0] = SW; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | SS F_REGISTER IMMEDIATE REGISTER  {
        fprintf(f, " ss");
        op[pc][0] = SS; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | BEQ REGISTER REGISTER LABEL {
        fprintf(f, " beq");
        op[pc][0] = BEQ; op[pc][1] = $2; op[pc][2] = $3; strcpy(label[pc], $4);
    }
    | BNE REGISTER REGISTER LABEL {
        fprintf(f, " bne");
        op[pc][0] = BNE; op[pc][1] = $2; op[pc][2] = $3; strcpy(label[pc], $4);
    }
    | BLT REGISTER REGISTER LABEL {
        fprintf(f, " blt");
        op[pc][0] = BLT; op[pc][1] = $2; op[pc][2] = $3; strcpy(label[pc], $4);
    }
    | BGT REGISTER REGISTER LABEL {
        fprintf(f, " bgt");
        op[pc][0] = BGT; op[pc][1] = $2; op[pc][2] = $3; strcpy(label[pc], $4);
    }
    | CEQS F_REGISTER F_REGISTER LABEL{
        fprintf(f, " c.eq.s");
        op[pc][0] = CEQS; op[pc][1] = $2; op[pc][2] = $3;strcpy(label[pc], $4);
    }
    | CLES F_REGISTER F_REGISTER LABEL{
        fprintf(f, " c.le.s");
        op[pc][0] = CLES; op[pc][1] = $2; op[pc][2] = $3;strcpy(label[pc], $4);
    }
    | CLTS F_REGISTER F_REGISTER LABEL{
        fprintf(f, " c.lt.s");
        op[pc][0] = CLTS; op[pc][1] = $2; op[pc][2] = $3;strcpy(label[pc], $4);
    }
    | J LABEL  {
        fprintf(f, " j");
        op[pc][0] = J; strcpy(label[pc], $2);
    }
    | JR REGISTER {
        fprintf(f, " jr");
        op[pc][0] = JR; op[pc][1] = $2;
    }
    | JAL LABEL {
        fprintf(f, " jal");
        op[pc][0] = JAL; strcpy(label[pc], $2);
    }
    | JALR REGISTER {
        fprintf(f, " jalr");
        op[pc][0] = JALR; op[pc][1] = $2;
    }
    | PRINTI REGISTER {
        fprintf(f, " print_i");
        op[pc][0] = PRINTI; op[pc][1] = $2;
    }
    | PRINTF F_REGISTER {
        fprintf(f, " print_f");
        op[pc][0] = PRINTF; op[pc][1] = $2;
    }
    | PRINTC REGISTER {
        fprintf(f, " print_c");
        op[pc][0] = PRINTC; op[pc][1] = $2;
    }
    | READI REGISTER {
        fprintf(f, " read_i");
        op[pc][0] = READI; op[pc][1] = $2;
    }
    | READF F_REGISTER {
        fprintf(f, " read_f");
        op[pc][0] = READF; op[pc][1] = $2;
    }
    | SIN F_REGISTER F_REGISTER {
        fprintf(f, " sin");
        op[pc][0] = SIN; op[pc][1] = $2; op[pc][2] = $3;
    }
    | COS F_REGISTER F_REGISTER {
        fprintf(f, " cos");
        op[pc][0] = COS; op[pc][1] = $2; op[pc][2] = $3;
    }
    | ATAN F_REGISTER F_REGISTER {
        fprintf(f, " atan");
        op[pc][0] = ATAN; op[pc][1] = $2; op[pc][2] = $3;
    }
    | FLOOR F_REGISTER F_REGISTER {
        fprintf(f, " floor");
        op[pc][0] = FLOOR; op[pc][1] = $2; op[pc][2] = $3;
    }
    | SQRT F_REGISTER F_REGISTER {
        fprintf(f, " sqrt");
        op[pc][0] = SQRT; op[pc][1] = $2; op[pc][2] = $3;
    }
    | FTOI REGISTER F_REGISTER {
        fprintf(f, " ftoi");
        op[pc][0] = FTOI; op[pc][1] = $2; op[pc][2] = $3;
    }
    | ITOF F_REGISTER REGISTER {
        fprintf(f, " itof");
        op[pc][0] = ITOF; op[pc][1] = $2; op[pc][2] = $3;
    }
    | EXIT  {
        fprintf(f, " exit");
        op[pc][0] = EXIT;
    }
    | BREAK {
        fprintf(f, " break");
        op[pc][0] = BREAK;
    }
    /* cmp系 */

    | CMP PREDICATE REGISTER REGISTER REGISTER {
        fprintf(f, " cmp");
        op[pc][0] = CMP; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4; op[pc][4] = $5;
    }
    | CMPI PREDICATE REGISTER REGISTER IMMEDIATE {
        fprintf(f, " cmpi");
        op[pc][0] = CMPI; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4; op[pc][4] = $5;
    }
    | CMPS PREDICATE REGISTER F_REGISTER F_REGISTER {
        fprintf(f, " cmp.s");
        op[pc][0] = CMPS; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4; op[pc][4] = $5;
    }

        /* cmpi */
    | CMPIEQ REGISTER REGISTER IMMEDIATE {
        fprintf(f, " cmpi.eq");
        op[pc][0] = CMPIEQ; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | CMPINE REGISTER REGISTER IMMEDIATE {
        fprintf(f, " cmpi.ne");
        op[pc][0] = CMPINE; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | CMPILE REGISTER REGISTER IMMEDIATE {
        fprintf(f, " cmpi.le");
        op[pc][0] = CMPILE; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | CMPIGE REGISTER REGISTER IMMEDIATE {
        fprintf(f, " cmpi.ge");
        op[pc][0] = CMPIGE; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | CMPILT REGISTER REGISTER IMMEDIATE {
        fprintf(f, " cmpi.lt");
        op[pc][0] = CMPILT; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | CMPIGT REGISTER REGISTER IMMEDIATE {
        fprintf(f, " cmpi.gt");
        op[pc][0] = CMPIGT; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
        /* cmp */
    | CMPEQ REGISTER REGISTER REGISTER {
        fprintf(f, " cmp.eq");
        op[pc][0] = CMPEQ; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | CMPNE REGISTER REGISTER REGISTER {
        fprintf(f, " cmp.ne");
        op[pc][0] = CMPNE; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | CMPLE REGISTER REGISTER REGISTER {
        fprintf(f, " cmp.le");
        op[pc][0] = CMPLE; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | CMPGE REGISTER REGISTER REGISTER {
        fprintf(f, " cmp.ge");
        op[pc][0] = CMPGE; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | CMPLT REGISTER REGISTER REGISTER {
        fprintf(f, " cmp.lt");
        op[pc][0] = CMPLT; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | CMPGT REGISTER REGISTER REGISTER {
        fprintf(f, " cmp.gt");
        op[pc][0] = CMPGT; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
        /* cmp.s */
    | CMPEQS REGISTER F_REGISTER F_REGISTER {
        fprintf(f, " cmp.eq.s");
        op[pc][0] = CMPEQS; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | CMPNES REGISTER F_REGISTER F_REGISTER {
        fprintf(f, " cmp.ne.s");
        op[pc][0] = CMPNES; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | CMPLES REGISTER F_REGISTER F_REGISTER {
        fprintf(f, " cmp.le.s");
        op[pc][0] = CMPLES; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | CMPGES REGISTER F_REGISTER F_REGISTER {
        fprintf(f, " cmp.ge.s");
        op[pc][0] = CMPGES; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | CMPLTS REGISTER F_REGISTER F_REGISTER {
        fprintf(f, " cmp.lt.s");
        op[pc][0] = CMPLTS; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | CMPGTS REGISTER F_REGISTER F_REGISTER {
        fprintf(f, " cmp.gt.s");
        op[pc][0] = CMPGTS; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    /* beqz */
    | BEQZ REGISTER LABEL {
        fprintf(f, " beqz");
        op[pc][0] = BEQZ; op[pc][1] = $2; strcpy(label[pc], $3);
    }
    | BEQI REGISTER IMMEDIATE LABEL {
        fprintf(f, " beqi");
        op[pc][0] = BEQI; op[pc][1] = $2; op[pc][2] = $3, strcpy(label[pc], $4);
    }
    | SWAP REGISTER REGISTER {
        fprintf(f, " swap");
        op[pc][0] = SWAP; op[pc][1] = $2; op[pc][2] = $3;
    }
    | SWAPS F_REGISTER F_REGISTER {
        fprintf(f, " swap.s");
        op[pc][0] = SWAPS; op[pc][1] = $2; op[pc][2] = $3;
    }
    | SELECT REGISTER REGISTER REGISTER REGISTER {
        fprintf(f, " select");
        op[pc][0] = SELECT; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4; op[pc][4] = $5;
    }
    | SELECTS F_REGISTER REGISTER F_REGISTER F_REGISTER {
        fprintf(f, " select.s");
        op[pc][0] = SELECTS; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4; op[pc][4] = $5;
    }
    | AND REGISTER REGISTER REGISTER {
        fprintf(f, " and");
        op[pc][0] = AND; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | OR REGISTER REGISTER REGISTER {
        fprintf(f, " or");
        op[pc][0] = OR; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | XOR REGISTER REGISTER REGISTER {
        fprintf(f, " xor");
        op[pc][0] = XOR; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }

    | ANDI REGISTER REGISTER IMMEDIATE {
        fprintf(f, " andi");
        op[pc][0] = ANDI; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | ORI REGISTER REGISTER IMMEDIATE {
        fprintf(f, " ori");
        op[pc][0] = ORI; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    | XORI REGISTER REGISTER IMMEDIATE {
        fprintf(f, " xori");
        op[pc][0] = XORI; op[pc][1] = $2; op[pc][2] = $3; op[pc][3] = $4;
    }
    ;
%%
int main(int argc, char *argv[])
{

    FILE *fh;
    if (argc == 2 && (fh = fopen(argv[1], "r"))) {
        yyin = fh;
    }
    if (argc == 3 && (fh = fopen(argv[2], "r"))) {
        yyin = fh;
    }

    f = fopen("parse.log", "w");
    int i;
    for (i = 0; i < 2 * MEM_SIZE; i++) {
        word[i][0] = INT_MAX;
    }
    yyparse();
    fclose(f);

    execute(op, label, string, word, argv[1]);

return 0;
}

void yyerror(s)
char *s;
{
    if (parse_error_flag == 0) {
        printf("parse error. more information in parse.log \n");
        parse_error_flag = 1;
    }
    fprintf(f, "\n%s",s);
}

int yywrap()
{
    return(1);
}
