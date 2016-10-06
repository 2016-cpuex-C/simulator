#include "y.tab.h"
#include "analyze.c"
#include "log.c"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define INT_MAX 2147483647
#define STACK_DIRECTION 1

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

int search_label (char label[100000][100], char *str);

void execute( int op[100000][5], char label[200000][100], char string[100000][100], int32_t word[200000][100], char *option)
{
    FILE *f;
    f = fopen("register.log", "w"); 

    int32_t reg[32];
    float f_reg[32];
    int32_t hi, lo;
    int32_t mem[100000];
    int i;
    for (i = 0; i < 100000; i++) {
        mem[i] = INT_MAX;  //initialilze all memory to int_max. to detect invalid memory access
    }
    int how_many_times_called[100000];
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
        } else if (op[pc][0] == ADDIU) {
            //printf("addiu\n");
            u temp1, temp2, temp3; 
            temp2.i = reg[op[pc][2]];
            temp3.i = op[pc][3];
            temp1.ui = temp2.ui + temp3.ui;
            reg[op[pc][1]] = temp1.i;
        } else if (op[pc][0] == SUB) {
            //printf("sub\n");
            reg[op[pc][1]] = reg[op[pc][2]] - reg[op[pc][3]];
        } else if (op[pc][0] == SUB) {
            //printf("sub\n");
            reg[op[pc][1]] = reg[op[pc][2]] - op[pc][3];
        } else if (op[pc][0] == SUBU) {
            //printf("subu\n");
            u temp1, temp2, temp3; 
            temp2.i = reg[op[pc][2]];
            temp3.i = reg[op[pc][3]];
            temp1.ui = temp2.ui - temp3.ui;
            reg[op[pc][1]] = temp1.i;
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
            if (word[100000 + search_label(label, temp)][0] != INT_MAX) {
                reg[op[pc][1]] = 100000 + search_label(label, temp);
            } else {
                reg[op[pc][1]] = search_label(label, temp);
            }
        } else if (op[pc][0] == LS) {
            //printf("ls\n");
            u temp;
            if (op[pc][3] == -1) {
                //printf("%d  ", pc);
                //printf("ls %d\n", reg[op[pc][3]]);
                temp.i = mem[STACK_DIRECTION * reg[op[pc][2]]];
                f_reg[op[pc][1]] = temp.f;
            } else if (reg[op[pc][3]] < 100000) {
                //printf("%d  ", pc);
                //printf("ls %d\n", op[pc][2] + reg[op[pc][3]]);
                temp.i = mem[STACK_DIRECTION * (op[pc][2] + reg[op[pc][3]])];
                f_reg[op[pc][1]] = temp.f;
            } else {
                //printf("%d ", pc);
                //printf("ls %d\n", reg[op[pc][3]]);
                temp.i = word[reg[op[pc][3]]][0];
                f_reg[op[pc][1]] = temp.f;
            }
        } else if (op[pc][0] == SS) {
            //printf("ss\n");
            u temp;
            if (op[pc][3] == -1) {
                //printf("%d ", pc);
                //printf("ss %d\n", reg[op[pc][2]]);
                temp.f = f_reg[op[pc][1]];
                mem[STACK_DIRECTION * (reg[op[pc][2]])] = temp.i; 
                //printf("%d\n", reg[24]);
            } else {
                //printf("%d ", pc);
                //printf("ss %d\n", op[pc][2] + reg[op[pc][3]]);
                temp.f = f_reg[op[pc][1]]; 
                //printf("%d\n", reg[op[pc][1]]);
                //printf("aaaa" );
                mem[STACK_DIRECTION * (op[pc][2] + reg[op[pc][3]])] = temp.i; 
                //printf("%d\n", reg[24]);
            }
        } else if (op[pc][0] == LD) {
            //printf("ld\n");
            u temp;
            if (op[pc][3] == -1) {
                //printf("%d  ", pc);
                //printf("ld %d\n", reg[op[pc][3]]);
                temp.i = mem[STACK_DIRECTION * reg[op[pc][2]]];
                f_reg[op[pc][1]] = temp.f;
                temp.i = mem[STACK_DIRECTION * (reg[op[pc][2]] + 4)];
                f_reg[op[pc][1] + 1] = temp.f;
            } else if (reg[op[pc][3]] < 100000) {
                //printf("%d  ", pc);
                //printf("ld %d\n", op[pc][2] + reg[op[pc][3]]);
                temp.i = mem[STACK_DIRECTION * (op[pc][2] + reg[op[pc][3]])];
                f_reg[op[pc][1]] = temp.f;
                temp.i = mem[STACK_DIRECTION * (op[pc][2] + reg[op[pc][3]] + 4)];
                f_reg[op[pc][1] + 1] = temp.f;
            } else {
                //printf("%d ", pc);
                //printf("ld %d\n", reg[op[pc][3]]);
                temp.i = word[reg[op[pc][3]]][0];
                f_reg[op[pc][1]] = temp.f;
                temp.i = word[reg[op[pc][3]]][1];
                f_reg[op[pc][1] + 1] = temp.f;
            }
        } else if (op[pc][0] == SD) {
            //printf("sd\n");
            u temp;
            if (op[pc][3] == -1) {
                //printf("%d ", pc);
                //printf("sd %d\n", reg[op[pc][2]]);
                temp.f = f_reg[op[pc][1]];
                mem[STACK_DIRECTION * (reg[op[pc][2]])] = temp.i; 
                temp.f = f_reg[op[pc][1] + 1];
                mem[STACK_DIRECTION * (reg[op[pc][2]] + 4)] = temp.i; 
            } else {
                //printf("%d ", pc);
                //printf("sd %d\n", op[pc][2] + reg[op[pc][3]]);
                temp.f = f_reg[op[pc][1]]; 
                mem[STACK_DIRECTION * (op[pc][2] + reg[op[pc][3]])] = temp.i; 
                temp.f = f_reg[op[pc][1] + 1];
                mem[STACK_DIRECTION * (op[pc][2] + reg[op[pc][3]] + 4)] = temp.i; 
            }
        } else if (op[pc][0] == LW) {
            //printf("lw\n");
            if (op[pc][3] == -3) {
                char temp[100];
                strcpy(temp, label[pc]);
                reg[op[pc][1]] = 100000 + search_label(label, strcat(temp, ":"));
            } else if (op[pc][3] == -1) {
                reg[op[pc][1]] = mem[STACK_DIRECTION * (reg[op[pc][2]])];
            } else if (reg[op[pc][3]] < 100000) {
                reg[op[pc][1]] = mem[STACK_DIRECTION * (op[pc][2] + reg[op[pc][3]])];
            } else {
                reg[op[pc][1]] = word[reg[op[pc][3]]][0];
            }
        } else if (op[pc][0] == SW) {
            //printf("sw\n");
            if (op[pc][3] == -1) {
                mem[STACK_DIRECTION * (reg[op[pc][2]])] = reg[op[pc][1]];
            } else {
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
        } else if (op[pc][0] == EXIT) {
            //printf("exit\n");
            break;
        } else if (op[pc][0] == MOVE) {
            //printf("move\n");
            reg[op[pc][1]] = reg[op[pc][2]];
        } else if (op[pc][0] == MTC1) {
            //printf("mtc1\n");
            u temp;
            temp.f = reg[op[pc][1]];
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
            //if (strstr(temp, "min_caml") != NULL) {
            //    u temp1, temp2;
            //    dbl temp4, temp5;
            //    if (strcmp(temp, "min_caml_print_int") == 0) {
            //        printf("%d", reg[2]);
            //    } else if (strcmp(temp, "min_caml_read_int") == 0) {
            //        scanf("%d", &reg[2]);
            //    } else if (strcmp(temp, "min_caml_read_float") == 0) {
            //        scanf("%lf", &temp4.d);
            //        temp1.i = temp4.i[0];
            //        temp2.i = temp4.i[1];
            //        f_reg[0] = temp1.f;
            //        f_reg[1] = temp2.f;
            //    } else if (strcmp(temp, "min_caml_print_char") == 0) {
            //        printf("%s", string[reg[2]]);
            //    } else if (strcmp(temp, "min_caml_xor") == 0) {
            //        reg[2] = reg[2] ^ reg[3];
            //    } else if (strcmp(temp, "min_caml_fiszero") == 0) {
            //        temp1.f = f_reg[0];
            //        temp2.f = f_reg[1];
            //        temp4.i[0] = temp1.i;
            //        temp4.i[1] = temp2.i;
            //        if(temp4.d == 0) {
            //            reg[2] = 1;
            //        } else {
            //            reg[2] = 0;
            //        }
            //    } else if (strcmp(temp, "min_caml_fispos") == 0) {
            //        temp1.f = f_reg[0];
            //        temp2.f = f_reg[1];
            //        temp4.i[0] = temp1.i;
            //        temp4.i[1] = temp2.i;
            //        if(temp4.d > 0) {
            //            reg[2] = 1;
            //        } else {
            //            reg[2] = 0;
            //        }
            //    } else if (strcmp(temp, "min_caml_fisneg") == 0) {
            //        temp1.f = f_reg[0];
            //        temp2.f = f_reg[1];
            //        temp4.i[0] = temp1.i;
            //        temp4.i[1] = temp2.i;
            //        if(temp4.d < 0) {
            //            reg[2] = 1;
            //        } else {
            //            reg[2] = 0;
            //        }
            //    } else if (strcmp(temp, "min_caml_fless") == 0) {
            //        temp1.f = f_reg[0];
            //        temp2.f = f_reg[1];
            //        temp4.i[0] = temp1.i;
            //        temp4.i[1] = temp2.i;
            //        temp1.f = f_reg[2];
            //        temp2.f = f_reg[3];
            //        temp5.i[0] = temp1.i;
            //        temp5.i[1] = temp2.i;
            //        if (temp4.d < temp5.d) {
            //            reg[2] = 1;
            //        } else {
            //            reg[2] = 0;
            //        }
            //    } else if (strcmp(temp, "min_caml_fneg") == 0) {
            //        temp1.f = f_reg[0];
            //        temp2.f = f_reg[1];
            //        temp4.i[0] = temp1.i;
            //        temp4.i[1] = temp2.i;
            //        temp4.d = - temp4.d;
            //        temp1.i = temp4.i[0];
            //        temp2.i = temp4.i[1];
            //        f_reg[0] = temp1.f;
            //        f_reg[1] = temp2.f;
            //    } else if (strcmp(temp, "min_caml_fabs") == 0) {
            //        temp1.f = f_reg[0];
            //        temp2.f = f_reg[1];
            //        temp4.i[0] = temp1.i;
            //        temp4.i[1] = temp2.i;
            //        temp4.d = abs(temp4.d);
            //        temp1.i = temp4.i[0];
            //        temp2.i = temp4.i[1];
            //        f_reg[0] = temp1.f;
            //        f_reg[1] = temp2.f;
            //    } else if (strcmp(temp, "min_caml_fsqr") == 0) {
            //        temp1.f = f_reg[0];
            //        temp2.f = f_reg[1];
            //        temp4.i[0] = temp1.i;
            //        temp4.i[1] = temp2.i;
            //        temp4.d = sqrt(temp4.d);
            //        temp1.i = temp4.i[0];
            //        temp2.i = temp4.i[1];
            //        f_reg[0] = temp1.f;
            //        f_reg[1] = temp2.f;
            //    } else if (strcmp(temp, "min_caml_sqrt") == 0) {
            //        temp1.f = f_reg[0];
            //        temp2.f = f_reg[1];
            //        temp4.i[0] = temp1.i;
            //        temp4.i[1] = temp2.i;
            //        temp4.d = sqrt(temp4.d);
            //        temp1.i = temp4.i[0];
            //        temp2.i = temp4.i[1];
            //        f_reg[0] = temp1.f;
            //        f_reg[1] = temp2.f;
            //    } else if (strcmp(temp, "min_caml_fhalf") == 0) {
            //        temp1.f = f_reg[0];
            //        temp2.f = f_reg[1];
            //        temp4.i[0] = temp1.i;
            //        temp4.i[1] = temp2.i;
            //        temp4.d = temp4.d / 2;
            //        temp1.i = temp4.i[0];
            //        temp2.i = temp4.i[1];
            //        f_reg[0] = temp1.f;
            //        f_reg[1] = temp2.f;
            //    } else if (strcmp(temp, "min_caml_floor") == 0) {
            //        temp1.f = f_reg[0];
            //        temp2.f = f_reg[1];
            //        temp4.i[0] = temp1.i;
            //        temp4.i[1] = temp2.i;
            //        temp4.d = floor(temp4.d);
            //        temp1.i = temp4.i[0];
            //        temp2.i = temp4.i[1];
            //        f_reg[0] = temp1.f;
            //        f_reg[1] = temp2.f;
            //    } else if (strcmp(temp, "min_caml_cos") == 0) {
            //        temp1.f = f_reg[0];
            //        temp2.f = f_reg[1];
            //        temp4.i[0] = temp1.i;
            //        temp4.i[1] = temp2.i;
            //        temp4.d = cos(temp4.d);
            //        temp1.i = temp4.i[0];
            //        temp2.i = temp4.i[1];
            //        f_reg[0] = temp1.f;
            //        f_reg[1] = temp2.f;
            //    } else if (strcmp(temp, "min_caml_sin") == 0) {
            //        temp1.f = f_reg[0];
            //        temp2.f = f_reg[1];
            //        temp4.i[0] = temp1.i;
            //        temp4.i[1] = temp2.i;
            //        temp4.d = sin(temp4.d);
            //        temp1.i = temp4.i[0];
            //        temp2.i = temp4.i[1];
            //        f_reg[0] = temp1.f;
            //        f_reg[1] = temp2.f;
            //    } else if (strcmp(temp, "min_caml_atan") == 0) {
            //        temp1.f = f_reg[0];
            //        temp2.f = f_reg[1];
            //        temp4.i[0] = temp1.i;
            //        temp4.i[1] = temp2.i;
            //        temp4.d = atan(temp4.d);
            //        temp1.i = temp4.i[0];
            //        temp2.i = temp4.i[1];
            //        f_reg[0] = temp1.f;
            //        f_reg[1] = temp2.f;
            //    } else if (strcmp(temp, "min_caml_float_of_int") == 0) {
            //        temp1.f = f_reg[0];
            //        temp2.f = f_reg[1];
            //        temp4.i[0] = temp1.i;
            //        temp4.i[1] = temp2.i;
            //        reg[2] = floor(temp4.d);
            //    } else if (strcmp(temp, "min_caml_int_of_float") == 0) {
            //        temp4.d = (double) reg[2];
            //        temp1.i = temp4.i[0];
            //        temp2.i = temp4.i[1];
            //        f_reg[0] = temp1.f;
            //        f_reg[1] = temp2.f;
            //    } else if (strcmp(temp, "min_caml_truncate") == 0) {
            //        reg[2] = (int) f_reg[0];
            //    }
            //} else {
            reg[31] = pc + 1;
            pc = search_label(label, strcat(temp, ":"));
            continue;
            //}
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
                f_reg[4];
                printf("%f", f_reg[12]);
            } else if (reg[2] == 4) {
                char temp[100];
                strcpy(temp, string[reg[4]]);
                temp[strlen(temp) - 1] = 0;
                printf("%s", &temp[1]);
            } else if (reg[2] == 5) {
                if (!freopen("/dev/tty", "r", stdin)) {
                    perror("freopen");
                }
                scanf("%d", &reg[2]);
            } else if (reg[2] == 10) {
                break;
            } else if (reg[2] == 11) {
                printf("%c", reg[4]);
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
            u temp;
            temp.i = (int) f_reg[op[pc][2]];
            f_reg[op[pc][1]] = temp.f; 
        } else if (op[pc][0] == TRUNCWS) {
            //printf("trunc.w.s\n");
            u temp;
            temp.i = (int) f_reg[op[pc][2]];
            f_reg[op[pc][1]] = temp.f; 
        } else if (op[pc][0] == ADDD) {
            //printf("add.d\n");
            u temp1, temp2;
            dbl temp4;
            double d1, d2;
            temp1.f = f_reg[op[pc][2]];
            temp2.f = f_reg[op[pc][2] + 1];
            temp4.i[0] = temp2.i;
            temp4.i[1] = temp1.i;
            d1 = temp4.d;
            temp1.f = f_reg[op[pc][3]];
            temp2.f = f_reg[op[pc][3] + 1];
            temp4.i[0] = temp2.i;
            temp4.i[1] = temp1.i;
            d2 = temp4.d;
            d1 = d1 + d2;
            temp1.i = getlo(d1);
            f_reg[op[pc][1]] = temp1.f; 
            temp1.i = gethi(d1);
            f_reg[op[pc][1] + 1] = temp1.f; 
        } else if (op[pc][0] == SUBD) {
            //printf("sub.d\n");
            u temp1, temp2;
            dbl temp4;
            double d1, d2;
            temp1.f = f_reg[op[pc][2]];
            temp2.f = f_reg[op[pc][2] + 1];
            temp4.i[0] = temp2.i;
            temp4.i[1] = temp1.i;
            d1 = temp4.d;
            temp1.f = f_reg[op[pc][3]];
            temp2.f = f_reg[op[pc][3] + 1];
            temp4.i[0] = temp2.i;
            temp4.i[1] = temp1.i;
            d2 = temp4.d;
            d1 = d1 - d2;
            temp1.i = getlo(d1);
            f_reg[op[pc][1]] = temp1.f; 
            temp1.i = gethi(d1);
            f_reg[op[pc][1] + 1] = temp1.f; 
        } else if (op[pc][0] == MULD) {
            //printf("mul.d\n");
            u temp1, temp2;
            dbl temp4;
            double d1, d2;
            temp1.f = f_reg[op[pc][2]];
            temp2.f = f_reg[op[pc][2] + 1];
            temp4.i[0] = temp2.i;
            temp4.i[1] = temp1.i;
            d1 = temp4.d;
            temp1.f = f_reg[op[pc][3]];
            temp2.f = f_reg[op[pc][3] + 1];
            temp4.i[0] = temp2.i;
            temp4.i[1] = temp1.i;
            d2 = temp4.d;
            d1 = d1 * d2;
            temp1.i = getlo(d1);
            f_reg[op[pc][1]] = temp1.f; 
            temp1.i = gethi(d1);
            f_reg[op[pc][1] + 1] = temp1.f; 
        } else if (op[pc][0] == DIVD) {
            //printf("div.d\n");
            u temp1, temp2;
            dbl temp4;
            double d1, d2;
            temp1.f = f_reg[op[pc][2]];
            temp2.f = f_reg[op[pc][2] + 1];
            temp4.i[0] = temp2.i;
            temp4.i[1] = temp1.i;
            d1 = temp4.d;
            temp1.f = f_reg[op[pc][3]];
            temp2.f = f_reg[op[pc][3] + 1];
            temp4.i[0] = temp2.i;
            temp4.i[1] = temp1.i;
            d2 = temp4.d;
            d1 = d1 / d2;
            temp1.i = getlo(d1);
            f_reg[op[pc][1]] = temp1.f; 
            temp1.i = gethi(d1);
            f_reg[op[pc][1] + 1] = temp1.f; 
        } else if (op[pc][0] == MOVD) {
            //printf("mov.d\n");
            f_reg[op[pc][1]] = f_reg[op[pc][2]];
            f_reg[op[pc][1] + 1] = f_reg[op[pc][1]];
        } 
       
        how_many_times_called[pc] += 1;
        pc += 1;
        
    }
    
    fclose(f);
   
    //analyze_how_many_times_called(label, how_many_times_called);

    return;
    
}

int search_label (char label[100000][100], char *str)
{
    int i = 0;
    for(i = 0; i < 100000; i++) {
        if (strcmp(label[i], str) == 0) {
            break;
        }
        if (i == 99999) {
            printf("label not found\n");
            exit(0);
        }
    }
    return i;
}
    
