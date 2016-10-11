#include "y.tab.h"
#include "analyze.c" 
#include "log.c" 
#include "global.h" 
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <assert.h>

typedef union {
    int32_t i;
    float f;
    uint32_t ui;
} u;
typedef union {
    int32_t    i[2];
    double d;
} dbl;

int gethi(double f) {
    dbl x;
    x.d = f;
    return x.i[0];
}
int getlo(double f) {
    dbl x;
    x.d = f;
    return x.i[1];
}

int search_label (char label[MEM_SIZE][MAX_STR], char *str);

void execute( int op[MEM_SIZE][5], char label[2 * MEM_SIZE][MAX_STR], char string[MEM_SIZE][MAX_STR], int32_t word[2 * MEM_SIZE][MAX_STR], char *option)
{
    FILE *f;
    f = fopen("register.log", "w"); 

    int32_t reg[32];
    reg[29] = MEM_SIZE / 2;
    float f_reg[32];
    int32_t hi, lo;
    int32_t mem[MEM_SIZE];
    int condition_bit = 0;
    int break_bit = 0;
    int i;
    for (i = 0; i < MEM_SIZE; i++) {
        mem[i] = INT_MAX;  //initialilze all memory to int_max. to detect invalid memory access
    }
    int how_many_times_called[MEM_SIZE];
    int pc = search_label(label, "main:");

    while (1){

        log_main (f, pc, reg, f_reg, hi, lo, mem, option);

        //printf("%d ", pc);
        if (op[pc][0] == ADD) {
            //printf("add\n");
            reg[op[pc][1]] = reg[op[pc][2]] + reg[op[pc][3]];
        } else if (op[pc][0] == ADDI) {
            //printf("addi\n");
            reg[op[pc][1]] = reg[op[pc][2]] + op[pc][3];
        } else if (op[pc][0] == ADDU) {
            //printf("addu\n");
            u temp1, temp2, temp3; 
            temp2.i = reg[op[pc][2]];
            temp3.i = reg[op[pc][3]];
            temp1.ui = temp2.ui + temp3.ui;
            reg[op[pc][1]] = temp1.i;
        } else if (op[pc][0] == SUB) {
            //printf("sub\n");
            reg[op[pc][1]] = reg[op[pc][2]] - reg[op[pc][3]];
        } else if (op[pc][0] == SUBI) {
            //printf("subi\n");
            reg[op[pc][1]] = reg[op[pc][2]] - op[pc][3];
        } else if (op[pc][0] == MUL) {
            //printf("mul\n");
            reg[op[pc][1]] = reg[op[pc][2]] * reg[op[pc][3]];
        } else if (op[pc][0] == MULT) {
            //printf("mult\n");
            int64_t temp  = (int64_t) reg[op[pc][1]] * reg[op[pc][2]];
            lo = (int32_t) temp;
            hi = (int32_t) (temp >> 32);
        } else if (op[pc][0] == DIV) {
            //printf("div\n");
            hi = reg[op[pc][1]] % reg[op[pc][2]];
            lo = reg[op[pc][1]] / reg[op[pc][2]];
        } else if (op[pc][0] == MFHI) {
            //printf("mfhi\n");
            reg[op[pc][1]] = hi;
        } else if (op[pc][0] == MFLO) {
            //printf("mflo\n");
            reg[op[pc][1]] = lo;
        } else if (op[pc][0] == ANDI) {
            //printf("andi\n");
            reg[op[pc][1]] = reg[op[pc][2]] && op[pc][3];
        } else if (op[pc][0] == LI) {
            //printf("li\n");
            reg[op[pc][1]] = op[pc][2];
        } else if (op[pc][0] == LA) {
            //printf("la\n");
            char temp[100];
            strcpy(temp, label[pc]);
            strcat(temp, ":");
            if (word[MEM_SIZE + search_label(label, temp)][0] != INT_MAX) {
                //if (MEM_SIZE + search_label(label, temp) != 1500077) printf("la %d\n", MEM_SIZE + search_label(label, temp));
                reg[op[pc][1]] = MEM_SIZE + search_label(label, temp);
            } else {
                reg[op[pc][1]] = search_label(label, temp);
            }
        } else if (op[pc][0] == LS) {
            //printf("l.s\n");
            u temp;
            if (op[pc][3] == -3) {
                char temp1[100];
                strcpy(temp1, label[pc]);
                strcat(temp1, ":");
                //printf("l.s %d\n", MEM_SIZE + search_label(label, temp1));
                temp.i = word[MEM_SIZE + search_label(label, temp1)][0];
                f_reg[op[pc][1]] = temp.f;
            } else if (op[pc][3] == -1) {
                //printf("%d  ", pc);
                //printf("l.s %d\n", reg[op[pc][3]]);
                temp.i = mem[STACK_DIRECTION * reg[op[pc][2]]];
                f_reg[op[pc][1]] = temp.f;
            } else if (reg[op[pc][3]] < MEM_SIZE) {
                //printf("%d  ", pc);
                //printf("l.s %d\n", op[pc][2] + reg[op[pc][3]]);
                temp.i = mem[STACK_DIRECTION * (op[pc][2] + reg[op[pc][3]])];
                f_reg[op[pc][1]] = temp.f;
            } else {
                //printf("%d ", pc);
                //if (reg[op[pc][3]] != 1500077) printf("l.s %d\n", reg[op[pc][3]]);
                temp.i = word[reg[op[pc][3]]][0];
                f_reg[op[pc][1]] = temp.f;
            }
        } else if (op[pc][0] == SS) {
            //printf("s.s\n");
            u temp;
            if (op[pc][3] == -1) {
                //printf("%d ", pc);
                //printf("s.s %d\n", reg[op[pc][2]]);
                temp.f = f_reg[op[pc][1]];
                mem[STACK_DIRECTION * (reg[op[pc][2]])] = temp.i; 
            } else {
                //printf("%d ", pc);
                //printf("s.s %d\n", op[pc][2] + reg[op[pc][3]]);
                temp.f = f_reg[op[pc][1]]; 
                mem[STACK_DIRECTION * (op[pc][2] + reg[op[pc][3]])] = temp.i; 
            }
        } else if (op[pc][0] == LW) {
            //printf("lw\n");
            if (op[pc][3] == -3) {
                char temp[100];
                strcpy(temp, label[pc]);
                reg[op[pc][1]] = MEM_SIZE + search_label(label, strcat(temp, ":"));
            } else if (op[pc][3] == -1) {
                reg[op[pc][1]] = mem[STACK_DIRECTION * (reg[op[pc][2]])];
            } else if (reg[op[pc][3]] < MEM_SIZE) {
                reg[op[pc][1]] = mem[STACK_DIRECTION * (op[pc][2] + reg[op[pc][3]])];
            } else {
                reg[op[pc][1]] = word[reg[op[pc][3]]][0];
            }
        } else if (op[pc][0] == SW) {
            //printf("sw\n");
            if (op[pc][3] == -1) {
                mem[STACK_DIRECTION * (reg[op[pc][2]])] = reg[op[pc][1]];
            } else {
                //printf("%d ", pc);
                //if(op[pc][2] + reg[op[pc][3]] > 1000000) printf("s.w %d\n", op[pc][2] + reg[op[pc][3]]);
                mem[STACK_DIRECTION * (op[pc][2] + reg[op[pc][3]])] = reg[op[pc][1]];
            }
        } else if (op[pc][0] == B) {
            //printf("b\n");
            char temp[100];
            strcpy(temp, label[pc]);
            pc = search_label(label, strcat(temp, ":"));
            continue;
        } else if (op[pc][0] == BEQZ) {
            //printf("beqz\n");
            if(reg[op[pc][1]] == 0) {
                char temp[100];
                strcpy(temp, label[pc]);
                pc = search_label(label, strcat(temp, ":"));
                continue;
            } 
        } else if (op[pc][0] == BNEZ) {
            //printf("bnez\n");
            if(reg[op[pc][1]] != 0) {
                char temp[100];
                strcpy(temp, label[pc]);
                pc = search_label(label, strcat(temp, ":"));
                continue;
            } 
        } else if (op[pc][0] == BLTZ) {
            //printf("bltz\n");
            if(reg[op[pc][1]] < 0) {
                char temp[100];
                strcpy(temp, label[pc]);
                pc = search_label(label, strcat(temp, ":"));
                continue;
            } 
        } else if (op[pc][0] == BLEZ) {
            //printf("blez\n");
            if(reg[op[pc][1]] <= 0) {
                char temp[100];
                strcpy(temp, label[pc]);
                pc = search_label(label, strcat(temp, ":"));
                continue;
            } 
        } else if (op[pc][0] == BGTZ) {
            //printf("bgtz\n");
            if(reg[op[pc][1]] > 0) {
                char temp[100];
                strcpy(temp, label[pc]);
                pc = search_label(label, strcat(temp, ":"));
                continue;
            } 
        } else if (op[pc][0] == BGEZ) {
            //printf("bgez\n");
            if(reg[op[pc][1]] >= 0) {
                char temp[100];
                strcpy(temp, label[pc]);
                pc = search_label(label, strcat(temp, ":"));
                continue;
            } 
        } else if (op[pc][0] == BEQ) {
            //printf("beq\n");
            if(reg[op[pc][1]] == reg[op[pc][2]]) {
                char temp[100];
                strcpy(temp, label[pc]);
                pc = search_label(label, strcat(temp, ":"));
                continue;
            } 
        } else if (op[pc][0] == BNE) {
            //printf("bne\n");
            //if (reg[op[pc][1]] == reg[op[pc][2]]) printf("%d\n", reg[op[pc][1]]);
            if(reg[op[pc][1]] != reg[op[pc][2]]) {
                char temp[100];
                strcpy(temp, label[pc]);
                pc = search_label(label, strcat(temp, ":"));
                continue;
            } 
        } else if (op[pc][0] == BLT) {
            //printf("blt\n");
            if(reg[op[pc][1]] < reg[op[pc][2]]) {
                char temp[100];
                strcpy(temp, label[pc]);
                pc = search_label(label, strcat(temp, ":"));
                continue;
            } 
        } else if (op[pc][0] == BLE) {
            //printf("ble\n");
            if(reg[op[pc][1]] <= reg[op[pc][2]]) {
                char temp[100];
                strcpy(temp, label[pc]);
                pc = search_label(label, strcat(temp, ":"));
                continue;
            } 
        } else if (op[pc][0] == BGT) {
            //printf("bgt\n");
            if(reg[op[pc][1]] > reg[op[pc][2]]) {
                char temp[100];
                strcpy(temp, label[pc]);
                pc = search_label(label, strcat(temp, ":"));
                continue;
            } 
        } else if (op[pc][0] == BGE) {
            //printf("bge\n");
            if(reg[op[pc][1]] >= reg[op[pc][2]]) {
                char temp[100];
                strcpy(temp, label[pc]);
                pc = search_label(label, strcat(temp, ":"));
                continue;
            } 
        } else if (op[pc][0] == MOVE) {
            //printf("move\n");
            reg[op[pc][1]] = reg[op[pc][2]];
        } else if (op[pc][0] == MTC1) {
            //printf("mtc1\n");
            u temp;
            temp.i = reg[op[pc][1]];
            f_reg[op[pc][2]] = temp.f;
        } else if (op[pc][0] == MFC1) {
            //printf("mfc1\n");
            u temp;
            temp.f = f_reg[op[pc][2]];
            reg[op[pc][1]] = temp.i;
        } else if (op[pc][0] == J) {
            //printf("j\n");
            char temp[100];
            strcpy(temp, label[pc]);
            pc = search_label(label, strcat(temp, ":"));
            continue;
        } else if (op[pc][0] == JR) {
            //printf("jr\n");
            pc = reg[op[pc][1]]; 
            continue;
        } else if (op[pc][0] == JAL) {
            //printf("jal\n");
            char temp[100];
            strcpy(temp, label[pc]);
            reg[31] = pc + 1;
            pc = search_label(label, strcat(temp, ":"));
            continue;
        } else if (op[pc][0] == JALR) {
            //printf("jalr\n");
            reg[31] = pc + 1; 
            pc = reg[op[pc][1]]; 
            continue;
        } else if (op[pc][0] == SYSCALL) {
            //printf("syscall\n");
            if (reg[2] == 1) {
                printf("%d", reg[4]);
            } else if (reg[2] == 2) {
                printf("%f", f_reg[12]);
            } else if (reg[2] == 4) {
                char temp[100];
                strcpy(temp, string[reg[4]]);
                temp[strlen(temp) - 1] = 0;
                printf("%s", &temp[1]);
            } else if (reg[2] == 5) {
                //printf("5syscall\n");
                scanf("%d", &reg[2]);
            } else if (reg[2] == 6) {
                //printf("6syscall\n");
                scanf("%f", &f_reg[0]);
            } else if (reg[2] == 10) {
                break;
            } else if (reg[2] == 11) {
                printf("%c", reg[4]);
            } else if (reg[0] == 30) {
                printf("sin\n");
                f_reg[0] = sin(f_reg[0]);
            } else if (reg[0] == 31) {
                printf("cos\n");
                f_reg[0] = cos(f_reg[0]);
            } else if (reg[0] == 32) {
                printf("atan\n");
                f_reg[0] = atan(f_reg[0]);
            }
        } else if (op[pc][0] == SLT) {
            //printf("slt\n");
            if(reg[op[pc][2]] < reg[op[pc][3]]) {
                reg[op[pc][1]] = 1;
            } else { 
                reg[op[pc][1]] = 0;
            }
        } else if (op[pc][0] == SLL) {
            //printf("sll\n");
            reg[op[pc][1]] = reg[op[pc][2]] << op[pc][3];
        } else if (op[pc][0] == SRL) {
            //printf("srl\n");
            reg[op[pc][1]] = reg[op[pc][2]] >> op[pc][3];
        } else if (op[pc][0] == NEG) {
            //printf("neg\n");
            reg[op[pc][1]] = - reg[op[pc][2]];
        } else if (op[pc][0] == ADDS) {
            //printf("add.s\n");
            f_reg[op[pc][1]] =  f_reg[op[pc][2]] + f_reg[op[pc][3]];
        } else if (op[pc][0] == SUBS) {
            //printf("sub.s\n");
            f_reg[op[pc][1]] =  f_reg[op[pc][2]] - f_reg[op[pc][3]];
        } else if (op[pc][0] == MULS) {
            //printf("mul.s\n");
            f_reg[op[pc][1]] =  f_reg[op[pc][2]] * f_reg[op[pc][3]];
        } else if (op[pc][0] == DIVS) {
            //printf("div.s\n");
            f_reg[op[pc][1]] =  f_reg[op[pc][2]] / f_reg[op[pc][3]];
        } else if (op[pc][0] == ABSS) {
            //printf("abs.s\n");
            f_reg[op[pc][1]] =  abs(f_reg[op[pc][2]]);
        } else if (op[pc][0] == NEGS) {
            //printf("neg.s\n");
            f_reg[op[pc][1]] =  - f_reg[op[pc][2]];
        } else if (op[pc][0] == FLOORWS) {
            //printf("floor.w.s\n");
            f_reg[op[pc][1]] =  floor(f_reg[op[pc][2]]);
        } else if (op[pc][0] == SQRTS) {
            //printf("sqrt.s\n");
            f_reg[op[pc][1]] =  sqrt(f_reg[op[pc][2]]);
        } else if (op[pc][0] == MOVS) {
            //printf("mov.s\n");
            f_reg[op[pc][1]] =  f_reg[op[pc][2]];
        } else if (op[pc][0] == CVTSW) {
            //printf("cvt.s.w\n");
            u temp;
            temp.f = f_reg[op[pc][2]];
            f_reg[op[pc][1]] = (float) temp.i; 
        } else if (op[pc][0] == CVTWS) {
            //printf("cvt.w.s\n");
            //printf("%f\n", f_reg[op[pc][2]]);
            u temp;
            temp.i = (int) f_reg[op[pc][2]];
            f_reg[op[pc][1]] = temp.f; 
        } else if (op[pc][0] == TRUNCWS) {
            //printf("trunc.w.s\n");
            u temp;
            temp.i = (int) f_reg[op[pc][2]];
            f_reg[op[pc][1]] = temp.f; 
        } else if (op[pc][0] == CEQS) {
            //printf("c.eq.s\n");
            condition_bit = (f_reg[op[pc][1]] == f_reg[op[pc][2]]);
        } else if (op[pc][0] == CLES) {
            //printf("c.le.s\n");
            condition_bit = (f_reg[op[pc][1]] < f_reg[op[pc][2]]);
        } else if (op[pc][0] == CLTS) {
            //printf("c.lt.s\n");
            condition_bit = (f_reg[op[pc][1]] <= f_reg[op[pc][2]]);
        } else if (op[pc][0] == BC1T) {
            //printf("bc1t\n");
            if (condition_bit == 1) {
                char temp[100];
                strcpy(temp, label[pc]);
                pc = search_label(label, strcat(temp, ":")); 
                continue;
            }
        } else if (op[pc][0] == BC1F) {
            //printf("bc1f\n");
            if (condition_bit == 0) {
                char temp[100];
                strcpy(temp, label[pc]);
                continue;
            }
        } 
        if (break_bit || op[pc][0] == BREAK) { // This instruction is not in mips!!
            //printf("break\n");
            int temp;
            break_bit = 1;
            printf("pc: %d\n", pc);
            printf("reg: ");fflush(stdout); 
            printf("\n    zr    at    v0    v1    a0    a1    a2    a3\n");fflush(stdout); 
            for (i = 0; i < 8; i++) {
                printf("%6d", reg[i]);fflush(stdout); 
            }
            printf("\n    t0    t1    t2    t3    t4    t5    t6    t7\n");fflush(stdout); 
            for (i = 8; i < 16; i++) {
                printf("%6d", reg[i]);fflush(stdout); 
            }
            printf("\n    s0    s1    s2    s3    s4    s5    s6    s7\n");fflush(stdout); 
            for (i = 16; i < 24; i++) {
                printf("%6d", reg[i]);fflush(stdout); 
            }
            printf("\n    t8    t9    k0    k1    gp    sp    fp    ra    hi    lo\n");fflush(stdout); 
            for (i = 24; i < 32; i++) {
                printf("%6d", reg[i]);fflush(stdout); 
            }
            printf("%6d", hi);fflush(stdout); 
            printf("%6d", lo);fflush(stdout); 
            printf("\n");fflush(stdout); 
            printf("Press f to show floating point registers. Enter to continue\n");  
            temp = getchar();  

            if (temp == 102) {
                int i;
                printf("f_reg: ");fflush(stdout); 
                printf("\n");fflush(stdout); 
                for (i = 0; i < 8; i++) {
                    if (f_reg[i] == 0) {
                        printf("  %2.2f", 0.0);fflush(stdout); 
                    } else {
                        printf("  %2.2f ", f_reg[i]);fflush(stdout); 
                    }
                }
                printf("\n");fflush(stdout); 
                for (i = 8; i < 16; i++) {
                    if (f_reg[i] == 0) {
                        printf("  %2.2f", 0.0);fflush(stdout); 
                    } else {
                        printf("  %2.2f ", f_reg[i]);fflush(stdout); 
                    }
                }
                printf("\n");fflush(stdout); 
                for (i = 16; i < 24; i++) {
                    if (f_reg[i] == 0) {
                        printf("  %2.2f", 0.0);fflush(stdout); 
                    } else {
                        printf("  %2.2f ", f_reg[i]);fflush(stdout); 
                    }
                }
                printf("\n");fflush(stdout); 
                for (i = 24; i < 32; i++) {
                    if (f_reg[i] == 0) {
                        printf("  %2.2f", 0.0);fflush(stdout); 
                    } else {
                        printf("  %2.2f ", f_reg[i]);fflush(stdout); 
                    }
                }
                printf("\n");fflush(stdout); 
                temp = getchar();  
                printf("Press enter to continue.\n");
                temp = getchar();  
            }
                
        } 
       
        how_many_times_called[pc] += 1;
        pc += 1;
        
    }
    
    fclose(f);
   
    //analyze_how_many_times_called(label, how_many_times_called);

    return;
    
}

int search_label (char label[MEM_SIZE][MAX_STR], char *str)
{
    int i = 0;
    for(i = 0; i < MEM_SIZE; i++) {
        if (strcmp(label[i], str) == 0) {
            break;
        }
        if (i == 999999) {
            printf("label not found\n");
            exit(0);
        }
    }
    return i;
}
    
