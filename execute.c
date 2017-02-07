#include "y.tab.h"
#include "log.c"
#include "global.h"
#include "analyze.c"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <assert.h>
#include <limits.h>

#define label_cache_size 60
#define CASE    break;case
#define DEFAULT break;default
#define swap(x, y, T) \
    do {\
        T _tmp_swap = x; \
        x = y; \
        y = _tmp_swap; \
    } while (0)
#define I2F(intVal,floatVar) \
    do {\
        u _tmp_u; \
        _tmp_u.i = intVal; \
        floatVar = _tmp_u.f; \
    } while (0)
#define F2I(floatVal,intVar) \
    do {\
        u _tmp_u; \
        _tmp_u.f = floatVal; \
        intVar = _tmp_u.i; \
    } while (0)
#define OP(x) op[pc][x]

typedef union { int32_t i;
    float f;
    uint32_t ui;
} u;


int label_cache[label_cache_size];

int search_label (char label[MEM_SIZE][MAX_STR], char *str);

void execute(FILE *input, char *option)
{
    /*FILE *f;*/
    //f = fopen("register.log", "w");

    int32_t reg[32];
    float f_reg[32];
    int32_t mem[MEM_SIZE];
    int break_bit = 0;
    int i;

    //initialilze all memory to int_max to detect invalid memory access
    for (i = 0; i < MEM_SIZE; i++) mem[i] = INT_MAX;

    long int how_many_times_called[MEM_SIZE];
    for (i = 0; i < MEM_SIZE; i++) how_many_times_called[i] = 0;

    int pc = search_label(label, "main:");

    int op_pc_0;

    // replace label with immediate
    for (i = 0; i < MEM_SIZE; i++) {
        char temp[100];
        switch (op[i][0]) {
            CASE LA:
                strcpy(temp, label[i]);
                strcat(temp, ":");
                op[i][3] = search_label(label, temp);
            CASE LWL:
                /*printf("lwl\n");*/
                strcpy(temp, label[i]);
                op[i][3] = MEM_SIZE + search_label(label, strcat(temp, ":"));
            CASE LSL:
                /*printf("l.sl\n");*/
                strcpy(temp, label[i]);
                strcat(temp, ":");
                op[i][3] = MEM_SIZE + search_label(label, temp);
            CASE BEQ:
                /*printf("beq\n");*/
                strcpy(temp, label[i]);
                op[i][3] = search_label(label, strcat(temp, ":"));
            CASE BNE:
                /*printf("bne\n");*/
                strcpy(temp, label[i]);
                op[i][3] = search_label(label, strcat(temp, ":"));
            CASE BLT:
                /*printf("blt\n");*/
                strcpy(temp, label[i]);
                op[i][3] = search_label(label, strcat(temp, ":"));
            CASE BGT:
                /*printf("bgt\n");*/
                strcpy(temp, label[i]);
                op[i][3] = search_label(label, strcat(temp, ":"));
            CASE BEQI:
                /*printf("beqi\n");*/
                strcpy(temp, label[i]);
                op[i][3] = search_label(label, strcat(temp, ":"));
            CASE BNEI:
                /*printf("bne\n");*/
                strcpy(temp, label[i]);
                op[i][3] = search_label(label, strcat(temp, ":"));
            CASE BLTI:
                /*printf("blt\n");*/
                strcpy(temp, label[i]);
                op[i][3] = search_label(label, strcat(temp, ":"));
            CASE BGTI:
                /*printf("bgt\n");*/
                strcpy(temp, label[i]);
                op[i][3] = search_label(label, strcat(temp, ":"));
            CASE CEQS:
                /*printf("c.eq.s\n");*/
                strcpy(temp, label[i]);
                op[i][3] = search_label(label, strcat(temp, ":"));
            CASE CLES:
                /*printf("c.le.s\n");*/
                strcpy(temp, label[i]);
                op[i][3] = search_label(label, strcat(temp, ":"));
            CASE CLTS:
                /*printf("c.lt.s\n");*/
                strcpy(temp, label[i]);
                op[i][3] = search_label(label, strcat(temp, ":"));
            CASE J:
                /*printf("j\n");*/
                strcpy(temp, label[i]);
                op[i][3] = search_label(label, strcat(temp, ":"));
            CASE JAL:
                /*printf("jal\n");*/
                strcpy(temp, label[i]);
                op[i][3] = search_label(label, strcat(temp, ":"));
            DEFAULT:
                ;
        }
    }

    int max_stack_dept, used_heap_size;
    max_stack_dept = 0;
    used_heap_size = reg[28];

    //int cnt=0;

    while (1){
        if (max_stack_dept < reg[29]) {
            max_stack_dept = reg[29];
        }

        //log_main (f, pc, reg, f_reg, mem, option);

        op_pc_0 = OP(0);
        how_many_times_called[pc] += 1; //各pcに何回来たか
        //fprintf(stderr, "pc=%6d $sp = %d\n",pc,reg[29]);

        if (break_bit || op_pc_0 == BREAK) { // This instruction is not in mips!!
            //printf("break\n");
            int temp;
            break_bit = 1;
            printf("pc: %d\n", pc);
            printf("op[0]: %d\n", OP(0));
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
            printf("\n");fflush(stdout);

            printf("stack: \n");
            for (i = 0; i < 9; i++) {
                if (mem[i] == INT_MAX) {
                    printf("     -");
                } else{
                     printf("%6d", mem[i]);fflush(stdout);
                }
            }
            printf("\nheap: \n");
            for (i = 10000; i < 10009; i++) {
                if (mem[i] == INT_MAX) {
                    printf("     -");
                } else{
                    printf("%6d", mem[i]);fflush(stdout);
                }
            }
            printf("\n");fflush(stdout);
            //printf("Press f to show floating point registers. Enter to continue\n");
            temp = getchar();

            if (temp == 'f') {
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
                /*temp = getchar();*/
                printf("Press enter to continue.\n");
                if (getchar() == 'b') {
                    break_bit = 0;
                }
            } else if (temp == 'b') {
                break_bit = 0;
            }

        }

        int tmp_addr;
        switch (op_pc_0) {
            CASE MOVE:
                if (break_bit) printf("move\n");
                reg[OP(1)] = reg[OP(2)];
            CASE NEG:
                if (break_bit) printf("neg\n");
                reg[OP(1)] = - reg[OP(2)];
            CASE ADD:
                if (break_bit) printf("add\n");
                reg[OP(1)] = reg[OP(2)] + reg[OP(3)];
            CASE ADDI:
                if (break_bit) printf("addi\n");
                reg[OP(1)] = reg[OP(2)] + OP(3);
            CASE SUB:
                if (break_bit) printf("sub\n");
                reg[OP(1)] = reg[OP(2)] - reg[OP(3)];
            CASE SUBI:
                if (break_bit) printf("subi\n");
                reg[OP(1)] = reg[OP(2)] - OP(3);
            CASE MULT:
                if (break_bit) printf("mult\n");
                reg[OP(1)] = reg[OP(2)] * reg[OP(3)];
            CASE MULTI:
                if (break_bit) printf("mult\n");
                reg[OP(1)] = reg[OP(2)] * OP(3);
            CASE DIV:
                if (break_bit) printf("div\n");
                reg[OP(1)] = reg[OP(2)] / reg[OP(3)];
            CASE DIVI:
                if (break_bit) printf("divi\n");
                reg[OP(1)] = reg[OP(2)] / OP(3);
            CASE MOVS:
                if (break_bit) printf("mov.s\n");
                f_reg[OP(1)] =  f_reg[OP(2)];
            CASE NEGS:
                if (break_bit) printf("neg.s\n");
                f_reg[OP(1)] =  - f_reg[OP(2)];
            CASE ADDS:
                if (break_bit) printf("add.s\n");
                f_reg[OP(1)] =  f_reg[OP(2)] + f_reg[OP(3)];
            CASE SUBS:
                if (break_bit) printf("sub.s\n");
                f_reg[OP(1)] =  f_reg[OP(2)] - f_reg[OP(3)];
            CASE MULS:
                if (break_bit) printf("mul.s\n");
                f_reg[OP(1)] =  f_reg[OP(2)] * f_reg[OP(3)];
            CASE DIVS:
                if (break_bit) printf("div.s\n");
                f_reg[OP(1)] =  f_reg[OP(2)] / f_reg[OP(3)];
            CASE SRL:
                if (break_bit) printf("srl\n");
                reg[OP(1)] = reg[OP(2)] >> reg[OP(3)];
            CASE SLL:
                if (break_bit) printf("sll\n");
                reg[OP(1)] = reg[OP(2)] << reg[OP(3)];
            CASE SRLI:
                if (break_bit) printf("srli\n");
                reg[OP(1)] = reg[OP(2)] >> OP(3);
            CASE SLLI:
                if (break_bit) printf("slli\n");
                reg[OP(1)] = reg[OP(2)] << OP(3);
            CASE LI:
                if (break_bit) printf("li\n");
                reg[OP(1)] = OP(2);
            CASE LA:
                if (break_bit) printf("la\n");
                reg[OP(1)] = OP(3);
            CASE LWL:
                if (break_bit) printf("lwl\n");
                reg[OP(1)] = OP(3);
            CASE LWR:
                if (break_bit) printf("lwr\n");
                tmp_addr = OP(2) + reg[OP(3)];
                if (tmp_addr < 0 || tmp_addr > MEM_SIZE) {
                    fprintf(stderr, "memory access out of range at pc %d\n", pc);
                    fprintf(stderr, "%d($%d) = %d+%d\n", OP(2),OP(3),OP(2),reg[OP(3)]);
                    assert(0);
                }
                reg[OP(1)] = mem[tmp_addr];
            CASE LSL:
                if (break_bit) printf("l.sl\n");
                I2F(word[OP(3)][0], f_reg[OP(1)]);
            CASE LSR:
                if (break_bit) printf("l.sr\n");
                if (OP(2) + reg[OP(3)] > MEM_SIZE) {
                    fprintf(stderr, "memory access out of range at pc %d\n", pc);
                    fprintf(stderr, "%d($%d) = %d+%d\n", OP(2),OP(3),OP(2),reg[OP(3)]);
                    assert(0);
                }
                I2F(mem[OP(2) + reg[OP(3)]], f_reg[OP(1)]);
            CASE SW:
                if (break_bit) printf("sw\n");
                //assert (OP(2) + reg[OP(3)] < MEM_SIZE);
                if (OP(2) + reg[OP(3)] > MEM_SIZE) {
                    fprintf(stderr, "memory access out of range at pc %d\n", pc);
                    fprintf(stderr, "%d($%d) = %d+%d\n", OP(2),OP(3),OP(2),reg[OP(3)]);
                    assert(0);
                }
                mem[OP(2) + reg[OP(3)]] = reg[OP(1)];
            CASE SS:
                if (break_bit) printf("s.s\n");
                assert (OP(2) + reg[OP(3)] < MEM_SIZE);
                F2I(f_reg[OP(1)], mem[OP(2) + reg[OP(3)]]);
            CASE BEQ:
                if (break_bit) printf("beq\n");
                if (reg[OP(1)] == reg[OP(2)]) {
                    pc = OP(3);
                    continue;
                }
            CASE BNE:
                if (break_bit) printf("bne\n");
                if (reg[OP(1)] != reg[OP(2)]) {
                    pc = OP(3);
                    continue;
                }
            CASE BLT:
                if (break_bit) printf("blt\n");
                if (reg[OP(1)] < reg[OP(2)]) {
                    pc = OP(3);
                    continue;
                }
            CASE BGT:
                if (break_bit) printf("bgt\n");
                if (reg[OP(1)] > reg[OP(2)]) {
                    pc = OP(3);
                    continue;
                }
            CASE CEQS:
                if (break_bit) printf("c.eq.s\n");
                if (f_reg[OP(1)] == f_reg[OP(2)]) {
                    pc = OP(3);
                    continue;
                }
            CASE CLES:
                if (break_bit) printf("c.le.s\n");
                if (f_reg[OP(1)] <= f_reg[OP(2)]) {
                    pc = OP(3);
                    continue;
                }
            CASE CLTS:
                if (break_bit) printf("c.lt.s\n");
                if (f_reg[OP(1)] < f_reg[OP(2)]) {
                    pc = OP(3);
                    continue;
                }
            CASE J:
                if (break_bit) printf("j\n");
                pc = OP(3);
                continue;
            CASE JR:
                if (break_bit) printf("jr\n");
                pc = reg[OP(1)];
                continue;
            CASE JAL:
                if (break_bit) printf("jal\n");
                reg[31] = pc + 1;
                pc = OP(3);
                continue;
            CASE JALR:
                if (break_bit) printf("jalr\n");
                reg[31] = pc + 1;
                pc = reg[OP(1)];
                continue;
            CASE PRINTI:
                if (break_bit) printf("print_i\n");
                printf("%d", reg[OP(1)]);
            CASE PRINTF:
                if (break_bit) printf("print_f\n");
                printf("%.10f", f_reg[OP(1)]);
            CASE PRINTC:
                if (break_bit) printf("print_c\n");
                printf("%c", reg[OP(1)]);
            CASE READI:
                if (break_bit) printf("read_i\n");
                assert(fscanf(input, "%d", &reg[OP(1)])==1);
            CASE READF:
                if (break_bit) printf("read_f\n");
                assert(fscanf(input, "%f", &f_reg[OP(1)])==1);
            CASE SIN:
                if (break_bit) printf("sin\n");
                f_reg[OP(1)] = sin(f_reg[OP(2)]);
            CASE COS:
                if (break_bit) printf("cos\n");
                f_reg[OP(1)] = cos(f_reg[OP(2)]);
            CASE ATAN:
                if (break_bit) printf("atan\n");
                f_reg[OP(1)] = atan(f_reg[OP(2)]);
            CASE FLOOR:
                if (break_bit) printf("floor\n");
                f_reg[OP(1)] = floor(f_reg[OP(2)]);
            CASE SQRT:
                if (break_bit) printf("sqrt\n");
                f_reg[OP(1)] = sqrt(f_reg[OP(2)]);
            CASE FTOI:
                if (break_bit) printf("ftoi\n");
                if (f_reg[OP(2)] > 0)
                    reg[OP(1)] = floor(f_reg[OP(2)]);
                else
                    reg[OP(1)] = ceil(f_reg[OP(2)]);
            CASE ITOF:
                if (break_bit) printf("itof\n");
                f_reg[OP(1)] = (float) reg[OP(2)];
            CASE EXIT:
                if (break_bit) printf("exit\n");
                goto END_LOOP;
            CASE CMP:
                if (break_bit) printf("cmp\n");
                switch (OP(1)) {
                    CASE EQ: reg[OP(2)] = reg[OP(3)] == reg[OP(4)];
                    CASE NE: reg[OP(2)] = reg[OP(3)] != reg[OP(4)];
                    CASE LE: reg[OP(2)] = reg[OP(3)] <= reg[OP(4)];
                    CASE GE: reg[OP(2)] = reg[OP(3)] >= reg[OP(4)];
                    CASE LT: reg[OP(2)] = reg[OP(3)] <  reg[OP(4)];
                    CASE GT: reg[OP(2)] = reg[OP(3)] >  reg[OP(4)];
                    DEFAULT: assert(0);
                }
            CASE CMPI:
                if (break_bit) printf("cmpi\n");
                switch (OP(1)) {
                    CASE EQ: reg[OP(2)] = reg[OP(3)] == OP(4);
                    CASE NE: reg[OP(2)] = reg[OP(3)] != OP(4);
                    CASE LE: reg[OP(2)] = reg[OP(3)] <= OP(4);
                    CASE GE: reg[OP(2)] = reg[OP(3)] >= OP(4);
                    CASE LT: reg[OP(2)] = reg[OP(3)] <  OP(4);
                    CASE GT: reg[OP(2)] = reg[OP(3)] >  OP(4);
                    DEFAULT: assert(0);
                }
            CASE CMPS:
                if (break_bit) printf("cmpi\n");
                switch (OP(1)) {
                    CASE EQ: reg[OP(2)] = f_reg[OP(3)] == f_reg[OP(4)];
                    CASE NE: reg[OP(2)] = f_reg[OP(3)] != f_reg[OP(4)];
                    CASE LE: reg[OP(2)] = f_reg[OP(3)] <= f_reg[OP(4)];
                    CASE GE: reg[OP(2)] = f_reg[OP(3)] >= f_reg[OP(4)];
                    CASE LT: reg[OP(2)] = f_reg[OP(3)] <  f_reg[OP(4)];
                    CASE GT: reg[OP(2)] = f_reg[OP(3)] >  f_reg[OP(4)];
                    DEFAULT: assert(0);
                }
            CASE SWAP:
                if (break_bit) printf("swap\n");
                swap(reg[OP(1)], reg[OP(2)], int32_t);
            CASE SWAPS:
                if (break_bit) printf("swap.s\n");
                swap(f_reg[OP(1)], f_reg[OP(2)], float);
            CASE SELECT:
                if (break_bit) printf("select\n");
                reg[OP(1)] = reg[OP(2)] ? reg[OP(3)] : reg[OP(4)];
            CASE SELECTS:
                if (break_bit) printf("select.s\n");
                f_reg[OP(1)] = reg[OP(2)] ? f_reg[OP(3)] : f_reg[OP(4)];
            CASE BEQI:
                if (break_bit) printf("beqi\n");
                if (reg[OP(1)] == OP(2)) {
                    pc = OP(3);
                    continue;
                }
            CASE BNEI:
                if (break_bit) printf("bnei\n");
                if (reg[OP(1)] != OP(2)) {
                    pc = OP(3);
                    continue;
                }
            CASE BLTI:
                if (break_bit) printf("blti\n");
                if (reg[OP(1)] < OP(2)) {
                    pc = OP(3);
                    continue;
                }
            CASE BGTI:
                if (break_bit) printf("bgti\n");
                if (reg[OP(1)] > OP(2)) {
                    pc = OP(3);
                    continue;
                }
            CASE PRINTB:
                if (break_bit) printf("print_b\n");
                printf("%02hhX", reg[OP(1)]);
            CASE AND:
                if (break_bit) printf("and\n");
                reg[OP(1)] = reg[OP(2)] & reg[OP(3)];
            CASE OR:
                if (break_bit) printf("or\n");
                reg[OP(1)] = reg[OP(2)] | reg[OP(3)];
            CASE XOR:
                if (break_bit) printf("xor\n");
                reg[OP(1)] = reg[OP(2)] ^ reg[OP(3)];
            CASE ANDI:
                if (break_bit) printf("andi\n");
                reg[OP(1)] = reg[OP(2)] & OP(3);
            CASE ORI:
                if (break_bit) printf("ori\n");
                reg[OP(1)] = reg[OP(2)] | OP(3);
            CASE XORI:
                if (break_bit) printf("xori\n");
                reg[OP(1)] = reg[OP(2)] ^ OP(3);
            CASE CVTSW:
                if (break_bit) printf("cvt.s.w\n");
                I2F(reg[OP(2)],f_reg[(OP(1))]);
            CASE CVTWS:
                if (break_bit) printf("cvt.w.s\n");
                F2I(f_reg[OP(2)],reg[(OP(1))]);
            CASE BREAK:
                if (break_bit) printf("break\n");

            // 実験
            CASE ABSS:
                if (break_bit) printf("abs.s\n");
                f_reg[OP(1)] = fabsf(f_reg[OP(2)]);
            CASE MADDS:
                if (break_bit) printf("madd.s %d, %d, %d\n", OP(1),OP(2),OP(3));
                f_reg[OP(1)] = f_reg[OP(2)] + f_reg[OP(3)] * f_reg[OP(4)];
            CASE RESTORE:
                if (break_bit) printf("restore\n");
                tmp_addr = OP(2) + reg[OP(3)];
                if (tmp_addr < 0 || tmp_addr > MEM_SIZE) {
                    fprintf(stderr, "memory access out of range at pc %d\n", pc);
                    fprintf(stderr, "%d($%d) = %d+%d\n", OP(2),OP(3),OP(2),reg[OP(3)]);
                    assert(0);
                }
                reg[OP(1)] = mem[tmp_addr];
            CASE RESTORES:
                if (break_bit) printf("restore.s\n");
                if (OP(2) + reg[OP(3)] > MEM_SIZE) {
                    fprintf(stderr, "memory access out of range at pc %d\n", pc);
                    fprintf(stderr, "%d($%d) = %d+%d\n", OP(2),OP(3),OP(2),reg[OP(3)]);
                    assert(0);
                }
                I2F(mem[OP(2) + reg[OP(3)]], f_reg[OP(1)]);

            CASE SAVE:
                if (break_bit) printf("save\n");
                //assert (OP(2) + reg[OP(3)] < MEM_SIZE);
                if (OP(2) + reg[OP(3)] > MEM_SIZE) {
                    fprintf(stderr, "memory access out of range at pc %d\n", pc);
                    fprintf(stderr, "%d($%d) = %d+%d\n", OP(2),OP(3),OP(2),reg[OP(3)]);
                    assert(0);
                }
                mem[OP(2) + reg[OP(3)]] = reg[OP(1)];
            CASE SAVES:
                if (break_bit) printf("save.s\n");
                assert (OP(2) + reg[OP(3)] < MEM_SIZE);
                F2I(f_reg[OP(1)], mem[OP(2) + reg[OP(3)]]);

            CASE 0:
                ;
            DEFAULT:
                fprintf(stderr, "unknown command %d\n", op_pc_0);
        }

        pc += 1;

    }
    END_LOOP:

    //fclose(f);

    used_heap_size = reg[28] - used_heap_size;

    analyze_how_many_times_called(op, how_many_times_called, max_stack_dept, used_heap_size, label);

    return;
}

// labelのpc(何行目にあるか)を返す
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
            printf("label `%s` not found\n", str);
            exit(0);
        }
    }
    assert(0);
}

