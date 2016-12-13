#include "y.tab.h"
#include "log.c" 
#include "global.h" 
#include "analyze.c" 
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <assert.h>

#define label_cache_size 60

typedef union { int32_t i;
    float f;
    uint32_t ui;
} u;


int label_cache[label_cache_size];

int search_label (char label[MEM_SIZE][MAX_STR], char *str);

void execute( int op[MEM_SIZE][5], char label[2 * MEM_SIZE][MAX_STR], char string[MEM_SIZE][MAX_STR], int32_t word[2 * MEM_SIZE][MAX_STR], char *option)
{
    FILE *f;
    //f = fopen("register.log", "w"); 

    int32_t reg[32];
    reg[28] = MEM_SIZE / 2;
    float f_reg[32];
    int32_t hi, lo;
    int32_t mem[MEM_SIZE];
    int condition_bit = 0;
    int break_bit = 0;
    int i;
    for (i = 0; i < MEM_SIZE; i++) {
        mem[i] = INT_MAX;  //initialilze all memory to int_max. to detect invalid memory access
    }

    long int how_many_times_called[MEM_SIZE];
    for (i = 0; i < MEM_SIZE; i++) {
        how_many_times_called[i] = 0;
    }

    int pc = search_label(label, "main:");

    int op_pc_0;

    // replace label with immediate
    for (i = 0; i < MEM_SIZE; i++) {
        op_pc_0 = op[i][0];
        if (op_pc_0 == LA) {
            //printf("la\n");
            char temp[100];
            strcpy(temp, label[i]);
            strcat(temp, ":");
            op[i][3] = search_label(label, temp);
        } else if (op_pc_0 == LWL) {
            //printf("lwl\n");
            char temp[100];
            strcpy(temp, label[i]);
            op[i][3] = MEM_SIZE + search_label(label, strcat(temp, ":"));
        } else if (op_pc_0 == LSL) {
            //printf("l.sl\n");
            char temp1[100];
            strcpy(temp1, label[i]);
            strcat(temp1, ":");
            op[i][3] = MEM_SIZE + search_label(label, temp1);
        } else if (op_pc_0 == BEQ) {
            //printf("beq\n");
            char temp[100];
            strcpy(temp, label[i]);
            op[i][3] = search_label(label, strcat(temp, ":"));
        } else if (op_pc_0 == BNE) {
            //printf("bne\n");
            char temp[100];
            strcpy(temp, label[i]);
            op[i][3] = search_label(label, strcat(temp, ":"));
        } else if (op_pc_0 == BLT) {
            //printf("blt\n");
            char temp[100];
            strcpy(temp, label[i]);
            op[i][3] = search_label(label, strcat(temp, ":"));
        } else if (op_pc_0 == BGT) {
            //printf("bgt\n");
            char temp[100];
            strcpy(temp, label[i]);
            op[i][3] = search_label(label, strcat(temp, ":"));
        } else if (op_pc_0 == CEQS) {
            //printf("c.eq.s\n");
            char temp[100];
            strcpy(temp, label[i]);
            op[i][3] = search_label(label, strcat(temp, ":"));
        } else if (op_pc_0 == CLES) {
            //printf("c.le.s\n");
            char temp[100];
            strcpy(temp, label[i]);
            op[i][3] = search_label(label, strcat(temp, ":"));
        } else if (op_pc_0 == CLTS) {
            //printf("c.lt.s\n");
            char temp[100];
            strcpy(temp, label[i]);
            op[i][3] = search_label(label, strcat(temp, ":"));
        } else if (op_pc_0 == J) {
            //printf("j\n");
            char temp[100];
            strcpy(temp, label[i]);
            op[i][3] = search_label(label, strcat(temp, ":"));
        } else if (op_pc_0 == JAL) {
            //printf("jal\n");
            char temp[100];
            strcpy(temp, label[i]);
            op[i][3] = search_label(label, strcat(temp, ":"));
        }
    }
    
    int max_stack_dept, used_heap_size;
    max_stack_dept = 0;
    used_heap_size = reg[28];

    while (1){
        if (max_stack_dept < reg[29]) {
            max_stack_dept = reg[29];
        }

        //log_main (f, pc, reg, f_reg, hi, lo, mem, option);

        op_pc_0 = op[pc][0];
        how_many_times_called[pc] += 1;

        
        if (break_bit || op_pc_0 == BREAK) { // This instruction is not in mips!!
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
            printf("\n    t8    t9    k0    k1    gp    sp    fp    ra\n");fflush(stdout); 
            for (i = 24; i < 32; i++) {
                printf("%6d", reg[i]);fflush(stdout); 
            }
            printf("\n");
            printf("mem: \n");
            for (i = 0; i < 9; i++) {
                if (mem[i] == INT_MAX) {
                    printf("     -");
                } else{ 
                     printf("%6d", mem[i]);fflush(stdout); 
                }
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

        //printf("%d ", pc);
        if (op_pc_0 == MOVE) {
            if (break_bit) {
                printf("move\n");
            }
            reg[op[pc][1]] = reg[op[pc][2]];
        } else if (op_pc_0 == NEG) {
            if (break_bit) {
                printf("neg\n");
            }
            reg[op[pc][1]] = - reg[op[pc][2]];
        } else if (op_pc_0 == ADD) {
            if (break_bit) {
                printf("add\n");
            }
            reg[op[pc][1]] = reg[op[pc][2]] + reg[op[pc][3]];
        } else if (op_pc_0 == ADDI) {
            if (break_bit) {
                printf("addi\n");
            }
            reg[op[pc][1]] = reg[op[pc][2]] + op[pc][3];
        } else if (op_pc_0 == SUB) {
            if (break_bit) {
                printf("sub\n");
            }
            reg[op[pc][1]] = reg[op[pc][2]] - reg[op[pc][3]];
        } else if (op_pc_0 == SUBI) {
            if (break_bit) {
                printf("subi\n");
            }
            reg[op[pc][1]] = reg[op[pc][2]] - op[pc][3];
        } else if (op_pc_0 == MULT) {
            if (break_bit) {
                printf("mult\n");
            }
            reg[op[pc][1]] = reg[op[pc][2]] * reg[op[pc][3]];
        } else if (op_pc_0 == MULTI) {
            if (break_bit) {
                printf("mult\n");
            }
            reg[op[pc][1]] = reg[op[pc][2]] * op[pc][3];
        } else if (op_pc_0 == DIV) {
            if (break_bit) {
                printf("div\n");
            }
            reg[op[pc][1]] = reg[op[pc][2]] / reg[op[pc][3]];
        } else if (op_pc_0 == DIVI) {
            if (break_bit) {
                printf("divi\n");
            }
            reg[op[pc][1]] = reg[op[pc][2]] / op[pc][3];
        } else if (op_pc_0 == MOVS) {
            if (break_bit) {
                printf("mov.s\n");
            }
            f_reg[op[pc][1]] =  f_reg[op[pc][2]];
        } else if (op_pc_0 == NEGS) {
            if (break_bit) {
                printf("neg.s\n");
            }
            f_reg[op[pc][1]] =  - f_reg[op[pc][2]];
        } else if (op_pc_0 == ADDS) {
            if (break_bit) {
                printf("add.s\n");
            }
            f_reg[op[pc][1]] =  f_reg[op[pc][2]] + f_reg[op[pc][3]];
        } else if (op_pc_0 == SUBS) {
            if (break_bit) {
                printf("sub.s\n");
            }
            f_reg[op[pc][1]] =  f_reg[op[pc][2]] - f_reg[op[pc][3]];
        } else if (op_pc_0 == MULS) {
            if (break_bit) {
                printf("mul.s\n");
            }
            f_reg[op[pc][1]] =  f_reg[op[pc][2]] * f_reg[op[pc][3]];
        } else if (op_pc_0 == DIVS) {
            if (break_bit) {
                printf("div.s\n");
            }
            f_reg[op[pc][1]] =  f_reg[op[pc][2]] / f_reg[op[pc][3]];
        } else if (op_pc_0 == SRL) {
            if (break_bit) {
                printf("srl\n");
            }
            reg[op[pc][1]] = reg[op[pc][2]] >> op[pc][3];
        } else if (op_pc_0 == SLL) {
            if (break_bit) {
                printf("sll\n");
            }
            reg[op[pc][1]] = reg[op[pc][2]] << op[pc][3];
        } else if (op_pc_0 == LI) {
            if (break_bit) {
                printf("li\n");
            }
            reg[op[pc][1]] = op[pc][2];
        } else if (op_pc_0 == LA) {
            if (break_bit) {
                printf("la\n");
            }
            reg[op[pc][1]] = op[pc][3];
        } else if (op_pc_0 == LWL) {
            if (break_bit) {
                printf("lwl\n");
            }
            reg[op[pc][1]] = op[pc][3];
        } else if (op_pc_0 == LWR) {
            if (break_bit) {
                printf("lwr\n");
            }
            assert (op[pc][2] + reg[op[pc][3]] < MEM_SIZE);
            reg[op[pc][1]] = mem[STACK_DIRECTION * (op[pc][2] + reg[op[pc][3]])];
        } else if (op_pc_0 == LSL) {
            if (break_bit) {
                printf("l.sl\n");
            }
            u temp;
            temp.i = word[op[pc][3]][0];
            f_reg[op[pc][1]] = temp.f;
        } else if (op_pc_0 == LSR) {
            if (break_bit) {
                printf("l.sr\n");
            }
            u temp;
            assert (op[pc][2] + reg[op[pc][3]] < MEM_SIZE);
            temp.i = mem[STACK_DIRECTION * (op[pc][2] + reg[op[pc][3]])];
            f_reg[op[pc][1]] = temp.f;
        } else if (op_pc_0 == SW) {
            if (break_bit) {
                printf("sw\n");
            }
            assert (op[pc][2] + reg[op[pc][3]] < MEM_SIZE);
            mem[STACK_DIRECTION * (op[pc][2] + reg[op[pc][3]])] = reg[op[pc][1]];
        } else if (op_pc_0 == SS) {
            if (break_bit) {
                printf("s.s\n");
            }
            u temp;
            temp.f = f_reg[op[pc][1]]; 
            assert (op[pc][2] + reg[op[pc][3]] < MEM_SIZE);
            mem[STACK_DIRECTION * (op[pc][2] + reg[op[pc][3]])] = temp.i; 
        } else if (op_pc_0 == BEQ) {
            if (break_bit) {
                printf("beq\n");
            }
            if(reg[op[pc][1]] == reg[op[pc][2]]) {
                pc = op[pc][3];
                continue;
            } 
        } else if (op_pc_0 == BNE) {
            if (break_bit) {
                printf("bne\n");
            }
            if(reg[op[pc][1]] != reg[op[pc][2]]) {
                pc = op[pc][3];
                continue;
            } 
        } else if (op_pc_0 == BLT) {
            if (break_bit) {
                printf("blt\n");
            }
            if(reg[op[pc][1]] < reg[op[pc][2]]) {
                pc = op[pc][3];
                continue;
            } 
        } else if (op_pc_0 == BGT) {
            if (break_bit) {
                printf("bgt\n");
            }
            if(reg[op[pc][1]] > reg[op[pc][2]]) {
                pc = op[pc][3];
                continue;
            } 
        } else if (op_pc_0 == CEQS) {
            if (break_bit) {
                printf("c.eq.s\n");
            }
            if(f_reg[op[pc][1]] == f_reg[op[pc][2]]) {
                pc = op[pc][3];
                continue;
            } 
        } else if (op_pc_0 == CLES) {
            if (break_bit) {
                printf("c.le.s\n");
            }
            if(f_reg[op[pc][1]] <= f_reg[op[pc][2]]) {
                pc = op[pc][3];
                continue;
            } 
        } else if (op_pc_0 == CLTS) {
            if (break_bit) {
                printf("c.lt.s\n");
            }
            if(f_reg[op[pc][1]] < f_reg[op[pc][2]]) {
                pc = op[pc][3];
                continue;
            } 
        } else if (op_pc_0 == J) {
            if (break_bit) {
                printf("j\n");
            }
            pc = op[pc][3];
            continue;
        } else if (op_pc_0 == JR) {
            if (break_bit) {
                printf("jr\n");
            }
            pc = reg[op[pc][1]]; 
            continue;
        } else if (op_pc_0 == JAL) {
            if (break_bit) {
                printf("jal\n");
            }
            reg[31] = pc + 1;
            pc = op[pc][3];
            continue;
        } else if (op_pc_0 == JALR) {
            if (break_bit) {
                printf("jalr\n");
            }
            reg[31] = pc + 1; 
            pc = reg[op[pc][1]]; 
            continue;
        } else if (op_pc_0 == PRINTI) {
            if (break_bit) {
                printf("print_i\n");
            }
            printf("%d", reg[op[pc][1]]);
        } else if (op_pc_0 == PRINTF) {
            if (break_bit) {
                printf("print_f\n");
            }
            printf("%f", f_reg[op[pc][1]]);
        } else if (op_pc_0 == PRINTC) {
            if (break_bit) {
                printf("print_c\n");
            }
            printf("%c", reg[op[pc][1]]);
        } else if (op_pc_0 == READI) {
            if (break_bit) {
                printf("read_i\n");
            }
            scanf("%d", &reg[op[pc][1]]);
        } else if (op_pc_0 == READF) {
            if (break_bit) {
                printf("read_f\n");
            }
            scanf("%f", &f_reg[op[pc][1]]);
        } else if (op_pc_0 == SIN) {
            if (break_bit) {
                printf("sin\n");
            }
            f_reg[op[pc][1]] = sin(f_reg[op[pc][2]]);
        } else if (op_pc_0 == COS) {
            if (break_bit) {
                printf("cos\n");
            }
            f_reg[op[pc][1]] = cos(f_reg[op[pc][2]]);
        } else if (op_pc_0 == ATAN) {
            if (break_bit) {
                printf("atan\n");
            }
            f_reg[op[pc][1]] = atan(f_reg[op[pc][2]]);
        } else if (op_pc_0 == FLOOR) {
            if (break_bit) {
                printf("floor\n");
            }
            f_reg[op[pc][1]] = floor(f_reg[op[pc][2]]);
        } else if (op_pc_0 == SQRT) {
            if (break_bit) {
                printf("sqrt\n");
            }
            f_reg[op[pc][1]] = sqrt(f_reg[op[pc][2]]);
        } else if (op_pc_0 == FTOI) {
            if (break_bit) {
                printf("ftoi\n");
            }
            if (f_reg[op[pc][2]] > 0) {
                reg[op[pc][1]] = floor(f_reg[op[pc][2]]);
            } else {
                reg[op[pc][1]] = ceil(f_reg[op[pc][2]]);
            }
        } else if (op_pc_0 == ITOF) {
            if (break_bit) {
                printf("itof\n");
            }
            f_reg[op[pc][1]] = (float) reg[op[pc][2]];
        } else if (op_pc_0 == EXIT) {
            if (break_bit) {
                printf("exit\n");
            }
            break;
        } else if (op_pc_0 == PRINTB) {
            if (break_bit) {
                printf("print_b\n");
            }
            printf("%02hhX", reg[op[pc][1]]);
        } 
       
        pc += 1;
        
    }
    
    //fclose(f);

    used_heap_size = reg[28] - used_heap_size;
   
    analyze_how_many_times_called(op, how_many_times_called, max_stack_dept, used_heap_size, label);

    return;
    
}

int search_label (char label[MEM_SIZE][MAX_STR], char *str)
{
    int i, j;
    for(i = 0; i < label_cache_size; i++) {
        if (strcmp(label[label_cache[i]], str) == 0) {
            return label_cache[i];
        }
    }
    for(i = 0; i < MEM_SIZE; i++) {
        if (strcmp(label[i], str) == 0) {
            for(j = label_cache_size - 1; j > 0; j--) {
                label_cache[j] = label_cache[j - 1];
            }
            label_cache[0] = i;
            return i;
        }
        if (i == 999999) {
            printf("label not found\n");
            printf("%s\n", str);
            exit(0);
        }
    }
    return 0;
}
    
