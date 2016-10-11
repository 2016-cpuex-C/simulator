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

%type <num> ADD ADDI ADDU ADDIU SUB SUBI SUBU MUL MULT DIV MFHI MFLO
%type <num> ANDI
%type <num> LI LA
%type <num> LW SW
%type <num> LS SS
%type <num> LD SD
%type <num> B BEQ BNE BLT BLE BGT BGE BEQZ BNEZ BLTZ BLEZ BGTZ BGEZ
%type <num> EXIT
%type <num> MOVE MTC1 MFC1
%type <num> J JR JAL JALR
%type <num> SYSCALL
%type <num> SLT
%type <num> SLL SRL NEG
%type <num> ADDS SUBS MULS DIVS ABSS NEGS FLOORWS SQRTS
%type <num> MOVS 
%type <num> CVTWS CVTSW TRUNCWS 
%type <num> CEQS CLES CLTS BC1T BC1F
%type <num> BREAK 
%type <num> ADDD SUBD MULD DIVD
%type <num> MOVD

%type <num> ENTER
%type <str> LABEL
%type <str> STRING
%type <num> DATA
%type <num> TEXT
%type <num> GLOBL
%type <num> ASCIIZ WORD
%type <str> HEX
%type <num> IMMEDIATE REGISTER F_REGISTER
%start list

%token ADD ADDI ADDU ADDIU SUB SUBI SUBU MUL MULT DIV MFHI MFLO
%token ANDI
%token LI LA
%token LW SW
%token LS SS
%token LD SD
%token B BEQ BNE BLT BLE BGT BGE BEQZ BNEZ BLTZ BLEZ BGTZ BGEZ
%token EXIT 
%token MOVE MTC1 MFC1
%token J JR JAL JALR
%token SYSCALL
%token SLT
%token SLL SRL NEG
%token ADDS SUBS MULS DIVS ABSS NEGS FLOORWS SQRTS
%token MOVS 
%token CVTWS CVTSW TRUNCWS 
%token CEQS CLES CLTS BC1T BC1F
%token BREAK 
%token ADDD SUBD MULD DIVD
%token MOVD

%token ENTER
%token STRING
%token LABEL
%token DATA
%token TEXT
%token GLOBL
%token ASCIIZ WORD
%token HEX
%token IMMEDIATE REGISTER F_REGISTER


%% 

list:   
        |
        list stat 
        {
        }
        |
        list error
        {
        }
        ;
stat:    
         ENTER
         {
            pc += 1;
         }
         |
         DATA
         {
         }
         |
         GLOBL
         {
         }
         |
         TEXT
         {
         }
         |
         WORD HEX
         {
            fprintf(f, " word");
            word[lc + MEM_SIZE][inner_lc] = strtol($2, NULL, 16);
            inner_lc++;
         }
         |   
         WORD IMMEDIATE
         {
            fprintf(f, " word");
            word[lc + MEM_SIZE][inner_lc] = $2;
            inner_lc++;
         }
         |   
         ASCIIZ STRING
         {
            strcpy(string[lc], $2); 
            inner_lc++;
         }
         |   
         LABEL
         {
            fprintf(f, "\n%s", $1);
            strcpy(label[pc], $1); 
            lc = pc;
            inner_lc = 0;
         }
         |  
         ADD REGISTER REGISTER REGISTER  
         {
            fprintf(f, " add");
            op[pc][0] = ADD;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = $4;
         }
         |
         ADDI REGISTER REGISTER IMMEDIATE  
         {
            fprintf(f, " addi");
            op[pc][0] = ADDI;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = $4;
         }
         |
         ADDU REGISTER REGISTER REGISTER  
         {
            fprintf(f, " addu");
            op[pc][0] = ADDU;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = $4;
         }
         |
         ADDIU REGISTER REGISTER IMMEDIATE  
         {
            fprintf(f, " addiu");
            op[pc][0] = ADDIU;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = $4;
         }
         |
         SUB REGISTER REGISTER REGISTER  
         {
            fprintf(f, " sub");
            op[pc][0] = SUB;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = $4;
         }
         |
         SUBI REGISTER REGISTER IMMEDIATE  
         {
            fprintf(f, " subi");
            op[pc][0] = SUBI;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = $4;
         }
         |
         SUBU REGISTER REGISTER REGISTER  
         {
            fprintf(f, " subu");
            op[pc][0] = SUBU;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = $4;
         }
         |
         MULT REGISTER REGISTER  
         {
            fprintf(f, " mult");
            op[pc][0] = MULT;
            op[pc][1] = $2;
            op[pc][2] = $3;
         }
         |
         DIV REGISTER REGISTER  
         {
            fprintf(f, " div");
            op[pc][0] = DIV;
            op[pc][1] = $2;
            op[pc][2] = $3;
         }
         |
         MUL REGISTER REGISTER REGISTER  
         {
            fprintf(f, " mul");
            op[pc][0] = MUL;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = $4;
         }
         |
         MFLO REGISTER  
         {
            fprintf(f, " mflo");
            op[pc][0] = MFLO;
            op[pc][1] = $2;
         }
         |
         MFHI REGISTER  
         {
            fprintf(f, " mfhi");
            op[pc][0] = MFHI;
            op[pc][1] = $2;
         }
         |
         ANDI REGISTER REGISTER IMMEDIATE
         {
            fprintf(f, " andi");
            op[pc][0] = ANDI;
            op[pc][1] = $2;
            op[pc][2] = $3;
         }
         |
         LI REGISTER IMMEDIATE  
         {
            fprintf(f, " li");
            op[pc][0] = LI;
            op[pc][1] = $2;
            op[pc][2] = $3;
         }
         |
         LA REGISTER LABEL  
         {
            fprintf(f, " la");
            op[pc][0] = LA;
            op[pc][1] = $2;
            strcpy(label[pc], $3); 
         }
         |
         LS F_REGISTER LABEL  
         {
            fprintf(f, " ls");
            op[pc][0] = LS;
            op[pc][1] = $2;
            strcpy(label[pc], $3); 
            op[pc][3] = -3;
         }
         |
         LS F_REGISTER REGISTER  
         {
            fprintf(f, " ls");
            op[pc][0] = LS;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = -1;
         }
         |
         LS F_REGISTER IMMEDIATE REGISTER  
         {
            fprintf(f, " ls");
            op[pc][0] = LS;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = $4;
         }
         |
         SS F_REGISTER REGISTER  
         {
            fprintf(f, " ss");
            op[pc][0] = SS;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = -1;
         }
         |
         SS F_REGISTER IMMEDIATE REGISTER  
         {
            fprintf(f, " ss");
            op[pc][0] = SS;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = $4;
         }
         |
         LD F_REGISTER REGISTER  
         {
            fprintf(f, " ld");
            op[pc][0] = LD;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = -1;
         }
         |
         LD F_REGISTER IMMEDIATE REGISTER  
         {
            fprintf(f, " ld");
            op[pc][0] = LD;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = $4;
         }
         |
         SD F_REGISTER REGISTER  
         {
            fprintf(f, " sw");
            op[pc][0] = SD;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = -1;
         }
         |
         SD F_REGISTER IMMEDIATE REGISTER  
         {
            fprintf(f, " sd");
            op[pc][0] = SD;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = $4;
         }
         |
         LW REGISTER LABEL  
         {
            fprintf(f, " lw");
            op[pc][0] = LW;
            op[pc][1] = $2;
            strcpy(label[pc], $3); 
            op[pc][3] = -3;
         }
         |
         LW REGISTER REGISTER  
         {
            fprintf(f, " lw");
            op[pc][0] = LW;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = -1;
         }
         |
         LW REGISTER IMMEDIATE REGISTER  
         {
            fprintf(f, " lw");
            op[pc][0] = LW;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = $4;
         }
         |
         SW REGISTER REGISTER  
         {
            fprintf(f, " sw");
            op[pc][0] = SW;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = -1;
         }
         |
         SW REGISTER IMMEDIATE REGISTER  
         {
            fprintf(f, " sw");
            op[pc][0] = SW;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = $4;
         }
         |
         B LABEL  
         {
            fprintf(f, " b");
            op[pc][0] = B;
            strcpy(label[pc], $2); 
         }
         |
         BEQ REGISTER REGISTER LABEL
         {
            fprintf(f, " beq");
            op[pc][0] = BEQ;
            op[pc][1] = $2;
            op[pc][2] = $3;
            strcpy(label[pc], $4); 
            
         }
         |
         BNE REGISTER REGISTER LABEL
         {
            fprintf(f, " bne");
            op[pc][0] = BNE;
            op[pc][1] = $2;
            op[pc][2] = $3;
            strcpy(label[pc], $4); 
            
         }
         |
         BLT REGISTER REGISTER LABEL
         {
            fprintf(f, " blt");
            op[pc][0] = BLT;
            op[pc][1] = $2;
            op[pc][2] = $3;
            strcpy(label[pc], $4); 
            
         }
         |
         BLE REGISTER REGISTER LABEL
         {
            fprintf(f, " ble");
            op[pc][0] = BLE;
            op[pc][1] = $2;
            op[pc][2] = $3;
            strcpy(label[pc], $4); 
            
         }
         |
         BGT REGISTER REGISTER LABEL
         {
            fprintf(f, " bgt");
            op[pc][0] = BGT;
            op[pc][1] = $2;
            op[pc][2] = $3;
            strcpy(label[pc], $4); 
            
         }
         |
         BGE REGISTER REGISTER LABEL
         {
            fprintf(f, " bge");
            op[pc][0] = BGE;
            op[pc][1] = $2;
            op[pc][2] = $3;
            strcpy(label[pc], $4); 
            
         }
         |
         BEQZ REGISTER LABEL
         {
            fprintf(f, " beqz");
            op[pc][0] = BEQZ;
            op[pc][1] = $2;
            strcpy(label[pc], $3); 
            
         }
         |
         BNEZ REGISTER LABEL
         {
            fprintf(f, " bnez");
            op[pc][0] = BNEZ;
            op[pc][1] = $2;
            strcpy(label[pc], $3); 
            
         }
         |
         BGEZ REGISTER LABEL
         {
            fprintf(f, " bgez");
            op[pc][0] = BGEZ;
            op[pc][1] = $2;
            strcpy(label[pc], $3); 
            
         }
         |
         BGTZ REGISTER LABEL
         {
            fprintf(f, " bgtz");
            op[pc][0] = BGTZ;
            op[pc][1] = $2;
            strcpy(label[pc], $3); 
            
         }
         |
         BLEZ REGISTER LABEL
         {
            fprintf(f, " blez");
            op[pc][0] = BLEZ;
            op[pc][1] = $2;
            strcpy(label[pc], $3); 
            
         }
         |
         BLTZ REGISTER LABEL
         {
            fprintf(f, " bltz");
            op[pc][0] = BLTZ;
            op[pc][1] = $2;
            strcpy(label[pc], $3); 
            
         }
         |
         EXIT  
         {
            fprintf(f, " exit");
            op[pc][0] = EXIT;
         }
         |
         MOVE REGISTER REGISTER  
         {
            fprintf(f, " move");
            op[pc][0] = MOVE;
            op[pc][1] = $2;
            op[pc][2] = $3;
         }
         |
         MTC1 REGISTER F_REGISTER
         {
            fprintf(f, " mtc1");
            op[pc][0] = MTC1;
            op[pc][1] = $2;
            op[pc][2] = $3;
         }
         |
         MFC1 REGISTER F_REGISTER
         {
            fprintf(f, " mfc1");
            op[pc][0] = MFC1;
            op[pc][1] = $2;
            op[pc][2] = $3;
         }
         |
         J LABEL  
         {
            fprintf(f, " j");
            op[pc][0] = J;
            strcpy(label[pc], $2); 
         }
         |
         JR REGISTER 
         {
            fprintf(f, " jr");
            op[pc][0] = JR;
            op[pc][1] = $2;
         }
         |
         JAL LABEL 
         {
            fprintf(f, " jal");
            op[pc][0] = JAL;
            strcpy(label[pc], $2); 
         }
         |
         JALR REGISTER 
         {
            fprintf(f, " jalr");
            op[pc][0] = JALR;
            op[pc][1] = $2;
         }
         |
         SYSCALL
         {
            fprintf(f, " syscall");
            op[pc][0] = SYSCALL;
         }
         |
         SLT REGISTER REGISTER REGISTER 
         {
            fprintf(f, " slt");
            op[pc][0] = SLT;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = $4;
         }
         |
         SLL REGISTER REGISTER IMMEDIATE 
         {
            fprintf(f, " sll");
            op[pc][0] = SLL;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = $4;
         }
         |
         SRL REGISTER REGISTER IMMEDIATE 
         {
            fprintf(f, " srl");
            op[pc][0] = SRL;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = $4;
         }
         |
         NEG REGISTER REGISTER 
         {
            fprintf(f, " neg");
            op[pc][0] = NEG;
            op[pc][1] = $2;
            op[pc][2] = $3;
         }
         |
         ADDS F_REGISTER F_REGISTER F_REGISTER
         {
            fprintf(f, " add.s");
            op[pc][0] = ADDS;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = $4;
         }
         |
         SUBS F_REGISTER F_REGISTER F_REGISTER
         {
            fprintf(f, " sub.s");
            op[pc][0] = SUBS;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = $4;
         }
         |
         MULS F_REGISTER F_REGISTER F_REGISTER
         {
            fprintf(f, " mul.s");
            op[pc][0] = MULS;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = $4;
         }
         | 
         DIVS F_REGISTER F_REGISTER F_REGISTER
         {
            fprintf(f, " div.s");
            op[pc][0] = DIVS;
            op[pc][1] = $2;
            op[pc][2] = $3;
            op[pc][3] = $4;
         }
         | 
         ABSS F_REGISTER F_REGISTER
         {
            fprintf(f, " abs.s");
            op[pc][0] = ABSS;
            op[pc][1] = $2;
            op[pc][2] = $3;
         }
         |
         NEGS F_REGISTER F_REGISTER
         {
            fprintf(f, " neg.s");
            op[pc][0] = NEGS;
            op[pc][1] = $2;
            op[pc][2] = $3;
         }
         |
         FLOORWS F_REGISTER F_REGISTER
         {
            fprintf(f, " floor.w.s");
            op[pc][0] = FLOORWS;
            op[pc][1] = $2;
            op[pc][2] = $3;
         }
         |
         SQRTS F_REGISTER F_REGISTER
         {
            fprintf(f, " sqrt.s");
            op[pc][0] = SQRTS;
            op[pc][1] = $2;
            op[pc][2] = $3;
         }
         |
         MOVS F_REGISTER F_REGISTER
         {
            fprintf(f, " mov.s");
            op[pc][0] = MOVS;
            op[pc][1] = $2;
            op[pc][2] = $3;
         }
         |
         CVTWS F_REGISTER F_REGISTER
         {
            fprintf(f, " cvt.w.s");
            op[pc][0] = CVTWS;
            op[pc][1] = $2;
            op[pc][2] = $3;
         }
         |
         CVTSW F_REGISTER F_REGISTER
         {
            fprintf(f, " cvt.s.w");
            op[pc][0] = CVTSW;
            op[pc][1] = $2;
            op[pc][2] = $3;
         }
         |
         TRUNCWS F_REGISTER F_REGISTER
         {
            fprintf(f, " trunc.w.s");
            op[pc][0] = TRUNCWS;
            op[pc][1] = $2;
            op[pc][2] = $3;
         }
         |
         CEQS F_REGISTER F_REGISTER
         {
            fprintf(f, " c.eq.s");
            op[pc][0] = CEQS;
            op[pc][1] = $2;
            op[pc][2] = $3;
         }
         |
         CLES F_REGISTER F_REGISTER
         {
            fprintf(f, " c.le.s");
            op[pc][0] = CLES;
            op[pc][1] = $2;
            op[pc][2] = $3;
         }
         |
         CLTS F_REGISTER F_REGISTER
         {
            fprintf(f, " c.lt.s");
            op[pc][0] = CLTS;
            op[pc][1] = $2;
            op[pc][2] = $3;
         }
         |
         BC1T LABEL
         {
            fprintf(f, " bc1t");
            op[pc][0] = BC1T;
            strcpy(label[pc], $2); 
         }
         |
         BC1F LABEL
         {
            fprintf(f, " bc1f");
            op[pc][0] = BC1F;
            strcpy(label[pc], $2); 
         }
         |
         BREAK 
         {
            fprintf(f, " break");
            op[pc][0] = BREAK;
         }
         ;
%%
main(int argc, char *argv[])
{

////    int (* op)[5];
//    op = malloc(sizeof(int) * MEM_SIZE * 5);
//    
//  //      char (* label)[MAX_STR];
//    label = malloc(sizeof(char) * 2 * MEM_SIZE * MAX_STR);
//
//   //     char (* string)[MAX_STR];
//    string = malloc(sizeof(char) * MEM_SIZE * MAX_STR);
//
//    //    int32_t (* word)[MAX_STR];
//    word = malloc(sizeof(int32_t) * 2 * MEM_SIZE * MAX_STR);

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
}

yyerror(s)
char *s;
{
    if (parse_error_flag == 0) { 
        printf("parse error. more information in parse.log \n");
        parse_error_flag = 1;
    }
    fprintf(f, "\n%s",s);
}

yywrap()
{
    return(1);
}
