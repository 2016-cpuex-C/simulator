%{
 
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
int c;
extern YYSTYPE yylval;
%}
%%

\".*\"  {
            yylval.str = strdup(yytext); 
            return(STRING);
        }
[ ] ;
[\t] ;
, ;
\( ;
\) ;
\n ;   

\.data  {
            return(DATA);
        }
\.asciiz    {
            return(ASCIIZ);
        } 
\.float ;
\.word  {
            return(WORD);
        }

\.globl {
            return (GLOBL);
        }
\.text  {
            return(TEXT);
        } 

$zero     {
            yylval.num = 0;
            return(REGISTER);
        }
$at     {
            yylval.num = 1;
            return(REGISTER);
        }
$v0     {
            yylval.num = 2;
            return(REGISTER);
        }
$v1     {
            yylval.num = 3;
            return(REGISTER);
        }
$a0     {
            yylval.num = 4;
            return(REGISTER);
        }
$a1     {
            yylval.num = 5;
            return(REGISTER);
        }
$a2     {
            yylval.num = 6;
            return(REGISTER);
        }
$a3     {
            yylval.num = 7;
            return(REGISTER);
        }
$t0     {
            yylval.num = 8;
            return(REGISTER);
        }
$t1     {
            yylval.num = 9;
            return(REGISTER);
        }
$t2     {
            yylval.num = 10;
            return(REGISTER);
        }
$t3     {
            yylval.num = 11;
            return(REGISTER);
        }
$t4     {
            yylval.num = 12;
            return(REGISTER);
        }
$t5     {
            yylval.num = 13;
            return(REGISTER);
        }
$t6     {
            yylval.num = 14;
            return(REGISTER);
        }
$t7     {
            yylval.num = 15;
            return(REGISTER);
        }
$s0     {
            yylval.num = 16;
            return(REGISTER);
        }
$s1     {
            yylval.num = 17;
            return(REGISTER);
        }
$s2     {
            yylval.num = 18;
            return(REGISTER);
        }
$s3     {
            yylval.num = 19;
            return(REGISTER);
        }
$s4     {
            yylval.num = 20;
            return(REGISTER);
        }
$s5     {
            yylval.num = 21;
            return(REGISTER);
        }
$s6     {
            yylval.num = 22;
            return(REGISTER);
        }
$s7     {
            yylval.num = 23;
            return(REGISTER);
        }
$t8     {
            yylval.num = 24;
            return(REGISTER);
        }
$t9     {
            yylval.num = 25;
            return(REGISTER);
        }
$k0     {
            yylval.num = 26;
            return(REGISTER);
        }
$k1     {
            yylval.num = 27;
            return(REGISTER);
        }
$gp     {
            yylval.num = 28;
            return(REGISTER);
        }
$sp    {
            yylval.num = 29;
            return(REGISTER);
        }
$fp     {
            yylval.num = 30;
            return(REGISTER);
        }
$ra     {
            yylval.num = 31;
            return(REGISTER);
        }
$f0     {
            yylval.num = 0;
            return(F_REGISTER);
        }
$f1     {
            yylval.num = 1;
            return(F_REGISTER);
        }
$f2     {
            yylval.num = 2;
            return(F_REGISTER);
        }
$f3     {
            yylval.num = 3;
            return(F_REGISTER);
        }
$f4     {
            yylval.num = 4;
            return(F_REGISTER);
        }
$f5     {
            yylval.num = 5;
            return(F_REGISTER);
        }
$f6     {
            yylval.num = 6;
            return(F_REGISTER);
        }
$f7     {
            yylval.num = 7;
            return(F_REGISTER);
        }
$f8     {
            yylval.num = 8;
            return(F_REGISTER);
        }
$f9     {
            yylval.num = 9;
            return(F_REGISTER);
        }
$f10     {
            yylval.num = 10;
            return(F_REGISTER);
        }
$f11     {
            yylval.num = 11;
            return(F_REGISTER);
        }
$f12     {
            yylval.num = 12;
            return(F_REGISTER);
        }
$f13     {
            yylval.num = 13;
            return(F_REGISTER);
        }
$f14     {
            yylval.num = 14;
            return(F_REGISTER);
        }
$f15     {
            yylval.num = 15;
            return(F_REGISTER);
        }
$f16     {
            yylval.num = 16;
            return(F_REGISTER);
        }
$f17     {
            yylval.num = 17;
            return(F_REGISTER);
        }
$f18     {
            yylval.num = 18;
            return(F_REGISTER);
        }
$f19     {
            yylval.num = 19;
            return(F_REGISTER);
        }
$f20     {
            yylval.num = 20;
            return(F_REGISTER);
        }
$f21     {
            yylval.num = 21;
            return(F_REGISTER);
        }
$f22     {
            yylval.num = 22;
            return(F_REGISTER);
        }
$f23     {
            yylval.num = 23;
            return(F_REGISTER);
        }
$f24     {
            yylval.num = 24;
            return(F_REGISTER);
        }
$f25     {
            yylval.num = 25;
            return(F_REGISTER);
        }
$f26     {
            yylval.num = 26;
            return(F_REGISTER);
        }
$f27     {
            yylval.num = 27;
            return(F_REGISTER);
        }
$f28     {
            yylval.num = 28;
            return(F_REGISTER);
        }
$f29     {
            yylval.num = 29;
            return(F_REGISTER);
        }
$f30     {
            yylval.num = 30;
            return(F_REGISTER);
        }
$f31     {
            yylval.num = 31;
            return(F_REGISTER);
        }


[0-9]     {
            c = yytext[0];
            yylval.num = c - '0';
            return(IMMEDIATE);
          }

[-]?[1-9][0-9]* {
                yylval.num = atoi(yytext);
                return IMMEDIATE;
            }
0x([0-9]|[a-fA-F])* {
            yylval.str = strdup(yytext); 
            return(HEX); 
            }


[a-zA-Z0-9_\.]*: { 
            yylval.str = strdup(yytext); 
            return(LABEL); 
            }


add    {
            return(ADD);
        }
addi    {
            return(ADDI);
        }
addu    {
            return(ADDU);
        }
addiu    {
            return(ADDIU);
        }
sub    {
            return(SUB);
        }
subi    {
            return(SUBI);
        }
subu    {
            return(SUBU);
        }
mul    {
            return(MUL);
        }
mult    {
            return(MULT);
        }
div    {
            return(DIV);
        }
mfhi   {
            return(MFHI);
        }
mflo   {
            return(MFLO);
        }
andi   {
            return(ANDI);
        }
li    {
            return(LI);
        }
la    {
            return(LA);
        }
l\.d    {
            return(LD);
        }
s\.d    {
            return(SD);
        }
ld    {
            return(LD);
        }
sd    {
            return(SD);
        }
l\.s    {
            return(LS);
        }
s\.s    {
            return(SS);
        }
lw    {
            return(LW);
        }
sw    {
            return(SW);
        }
b      {
            return(B);
        }
beq    {
            return(BEQ);
        }
bne    {
            return(BNE);
        }
blt    {
            return(BLT);
        }
ble    {
            return(BLE);
        }
bgt    {
            return(BGT);
        }
bge    {
            return(BGE);
        }
beqz    {
            return(BEQZ);
        }
bnez    {
            return(BNEZ);
        }
bltz    {
            return(BLTZ);
        }
blez    {
            return(BLEZ);
        }
bgtz    {
            return(BGTZ);
        }
bgez    {
            return(BGEZ);
        }
exit    {
            return(EXIT);
        }
move    {
            return(MOVE);
        }
mfc1   { 
            return(MFC1);
        }
mtc1   { 
            return(MTC1);
        }
j       {
            return(J);
        }
jr       {
            return(JR);
        }
jal       {
            return(JAL);
        }
jalr       {
            return(JALR);
        }
syscall {
            return(SYSCALL);
        }
slt     {
            return(SLT);
        }
sll     {
            return(SLL);
        }
neg     {
            return(NEG);
        }
add\.s   {
            return(ADDS);
        }
sub\.s   {
            return(SUBS);
        }
mul\.s   {
            return(MULS);
        }
div\.s   { 
            return(DIVS);
        }
abs\.s   { 
            return(ABSS);
        }
neg\.s   { 
            return(NEGS);
        }
mov\.s   { 
            return(MOVS);
        }
cvt\.w\.s   { 
            return(CVTWS);
        }
cvt\.s\.w   { 
            return(CVTSW);
        }
trunc\.w\.s   { 
            return(TRUNCWS);
        }
sub\.d   {
            return(SUBD);
        }
add\.d   {
            return(ADDD);
        }
mul\.d   {
            return(MULD);
        }
div\.d   {
            return(DIVD);
        }
mov\.d   {
            return(MOVD);
        }

[a-zA-Z0-9_\.]* { 
            yylval.str = strdup(yytext); 
            return(LABEL);
                }
#.* {}
