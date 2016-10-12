#include <string.h>
#include "global.h" 

analyze_how_many_times_called(int op[MEM_SIZE][5], int how_many_times_called[MEM_SIZE]) {
    
    int i;
    int op_pc_0;

    int temp[10000];
    for (i = 0; i < MEM_SIZE; i++) {
        temp[op[i][0]] += how_many_times_called[i];
    }
    for (op_pc_0 = 0; op_pc_0 < 500; op_pc_0++) {
        if (op_pc_0 == ADD) {
            if (temp[op_pc_0] != 0) {
                printf("add ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == ADDI) {
            if (temp[op_pc_0] != 0) {
                printf("addi ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SUB) {
            if (temp[op_pc_0] != 0) {
                printf("sub ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == MULT) {
            if (temp[op_pc_0] != 0) {
                printf("mult ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == DIV) {
            if (temp[op_pc_0] != 0) {
                printf("div ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == MFHI) {
            if (temp[op_pc_0] != 0) {
                printf("mfhi ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == MFLO) {
            if (temp[op_pc_0] != 0) {
                printf("mflo ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == LI) {
            if (temp[op_pc_0] != 0) {
                printf("li ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == LA) {
            if (temp[op_pc_0] != 0) {
                printf("la ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == LS) {
            if (temp[op_pc_0] != 0) {
                printf("l.s ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SS) {
            if (temp[op_pc_0] != 0) {
                printf("s.s ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == LW) {
            if (temp[op_pc_0] != 0) {
                printf("lw ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SW) {
            if (temp[op_pc_0] != 0) {
                printf("sw ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == B) {
            if (temp[op_pc_0] != 0) {
                printf("b ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == BEQ) {
            if (temp[op_pc_0] != 0) {
                printf("beq ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == BNE) {
            if (temp[op_pc_0] != 0) {
                printf("bne ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == BLT) {
            if (temp[op_pc_0] != 0) {
                printf("blt ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == BLE) {
            if (temp[op_pc_0] != 0) {
                printf("ble ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == BGT) {
            if (temp[op_pc_0] != 0) {
                printf("bgt ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == BGE) {
            if (temp[op_pc_0] != 0) {
                printf("bge ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == MOVE) {
            if (temp[op_pc_0] != 0) {
                printf("move ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == MTC1) {
            if (temp[op_pc_0] != 0) {
                printf("mtc1 ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == MFC1) {
            if (temp[op_pc_0] != 0) {
                printf("mfc1 ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == J) {
            if (temp[op_pc_0] != 0) {
                printf("j ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == JR) {
            if (temp[op_pc_0] != 0) {
                printf("jr ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == JAL) {
            if (temp[op_pc_0] != 0) {
                printf("jal ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == JALR) {
            if (temp[op_pc_0] != 0) {
                printf("jalr ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SYSCALL) {
            if (temp[op_pc_0] != 0) {
                printf("syscall ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SLT) {
            if (temp[op_pc_0] != 0) {
                printf("slt ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SLL) {
            if (temp[op_pc_0] != 0) {
                printf("sll ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SRL) {
            if (temp[op_pc_0] != 0) {
                printf("srl ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == NEG) {
            if (temp[op_pc_0] != 0) {
                printf("neg ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == ADDS) {
            if (temp[op_pc_0] != 0) {
                printf("add.s ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SUBS) {
            if (temp[op_pc_0] != 0) {
                printf("sub.s ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == MULS) {
            if (temp[op_pc_0] != 0) {
                printf("mul.s ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == DIVS) {
            if (temp[op_pc_0] != 0) {
                printf("div.s ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == ABSS) {
            if (temp[op_pc_0] != 0) {
                printf("abs.s ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == NEGS) {
            if (temp[op_pc_0] != 0) {
                printf("neg.s ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == FLOORWS) {
            if (temp[op_pc_0] != 0) {
                printf("floor.w.s ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == SQRTS) {
            if (temp[op_pc_0] != 0) {
                printf("sqrt.s ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == MOVS) {
            if (temp[op_pc_0] != 0) {
                printf("mov.s ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == CVTSW) {
            if (temp[op_pc_0] != 0) {
                printf("cvt.s.w ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == CVTWS) {
            if (temp[op_pc_0] != 0) {
                printf("cvt.w.s ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == TRUNCWS) {
            if (temp[op_pc_0] != 0) {
                printf("trunc.w.s ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == CEQS) {
            if (temp[op_pc_0] != 0) {
                printf("c.eq.s ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == CLES) {
            if (temp[op_pc_0] != 0) {
                printf("c.le.s ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == CLTS) {
            if (temp[op_pc_0] != 0) {
                printf("c.lt.s ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == BC1T) {
            if (temp[op_pc_0] != 0) {
                printf("bc1t ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } else if (op_pc_0 == BC1F) {
            if (temp[op_pc_0] != 0) {
                printf("bc1f ");
                printf("%d  \n", temp[op_pc_0]);
            }
        } 
    }
}
