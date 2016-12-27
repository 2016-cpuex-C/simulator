#include <locale.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "global.h"

void analyze_how_many_times_called( int op[MEM_SIZE][5],
                                    long int how_many_times_called[MEM_SIZE],
                                    int max_stack_dept,
                                    int used_heap_size,
                                    char label[2 * MEM_SIZE][MAX_STR])
{
    long int i, dynamic_count;
    int op_pc_0;
    dynamic_count = 0;

    FILE *f;
    f = fopen("result.txt", "w");

    long int temp[10000];
    for (i = 0; i < MEM_SIZE; i++) {
        temp[op[i][0]] += how_many_times_called[i];
    }
    for (op_pc_0 = 0; op_pc_0 < 500; op_pc_0++) {
        dynamic_count += temp[op_pc_0];
    }

    setlocale(LC_NUMERIC, "");
    fprintf(f, "%'ld :number of dynamic instructions\n", dynamic_count);
    fprintf(f, "%d :max stack dept\n", max_stack_dept);
    fprintf(f, "%'d :used heap size\n", used_heap_size);
    fprintf(f, "\n");
    for (op_pc_0 = 0; op_pc_0 < 500; op_pc_0++) {
        if (op_pc_0 == MOVE) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "move");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == NEG) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "neg");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == ADD) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "add");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == ADDI) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "addi");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SUB) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "sub");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SUBI) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "subi");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == MULT) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "mult");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == MULTI) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "multi");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == DIV) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "div");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == DIVI) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "divi");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == MOVS) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "movs");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == NEGS) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "negs");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == ADDS) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "add.s");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SUBS) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "sub.s");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == MULS) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "mul.s");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == DIVS) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "div.s");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SRL) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "srl");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SLL) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "sll");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == LI) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "li");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == LA) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "la");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == LWL) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "lwl");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == LWR) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "lwr");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == LSL) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "l.sl");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == LSR) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "l.sr");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SW) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "sw");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SS) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "s.s");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == BEQ) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "beq");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == BNE) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "bne");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == BLT) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "blt");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == BGT) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "bgt");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == CEQS) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "c.eq.s");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == CLES) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "c.le.s");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == CLTS) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "c.lt.s");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == J) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "j");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == JR) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "jr");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == JAL) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "jal");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == JALR) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "jalr");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == PRINTI) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "print_i");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == PRINTF) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "print_f");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == PRINTC) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "print_c");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == READI) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "read_i");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == READF) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "read_f");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SIN) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "sin");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == COS) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "cos");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == ATAN) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "atan");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == FLOOR) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "floor");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SQRT) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "sqrt");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == FTOI) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "ftoi");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == ITOF) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "itof");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == BEQI) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "beqi");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == AND) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "and");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == OR) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "or");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == XOR) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "xor");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == ANDI) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "andi");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == ORI) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "ori");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == XORI) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "xori");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SWAP) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "swap");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SWAPS) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "swap.s");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SELECT) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "select");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SELECTS) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "select.s");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == CMP) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "cmp");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == CMPI) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "cmpi");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == CMPS) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "cmp.s");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == CVTSW) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "cvt.s.w");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == CVTWS) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "cvt.w.s");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SIN) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "sin");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == COS) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "cos");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == ATAN) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "atan");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == FLOOR) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "floor");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SQRT) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "sqrt");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == FTOI) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "ftoi");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == ITOF) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "itof");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == EXIT) {
            if (temp[op_pc_0] != 0) {
                fprintf(f, "%-9s", "exit");
                fprintf(f, "%'ld  \n", temp[op_pc_0]);
            }
        }
    }

    fprintf(f, "\n\n");
    fprintf(f, "label count\n");
    for(i = 0; i < MEM_SIZE; i++) {
        if(strstr(label[i], ":") && strcmp(label[i], "\0") != 0 && how_many_times_called[i] != 0) {
            fprintf(f, "%'12ld  ", how_many_times_called[i]);
            fprintf(f, "%s  \n", label[i]);
        }
    }
    fclose(f);
}
