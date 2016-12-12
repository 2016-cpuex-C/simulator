#include <stdio.h>
#include <stdint.h>
#define INT_MAX 2147483647
#include <inttypes.h>
#define __STDC_FORMAT_MACROS

void register_log (FILE *f, int pc, int32_t reg[32], int hi, int lo)
{
    int i;

    fprintf(f, "\n"); 
    fprintf(f, "\n"); 
    fprintf(f, "pc: %d ", pc); 
    fprintf(f, "\n"); 

    fprintf(f, "reg: "); 
    fprintf(f, "\n    zr    at    v0    v1    a0    a1    a2    a3\n"); 
    for (i = 0; i < 8; i++) {
        fprintf(f, "%6d", reg[i]); 
    }
    fprintf(f, "\n    t0    t1    t2    t3    t4    t5    t6    t7\n"); 
    for (i = 8; i < 16; i++) {
        fprintf(f, "%6d", reg[i]); 
    }
    fprintf(f, "\n    s0    s1    s2    s3    s4    s5    s6    s7\n"); 
    for (i = 16; i < 24; i++) {
        fprintf(f, "%6d", reg[i]); 
    }
    fprintf(f, "\n    t8    t9    k0    k1    gp    sp    fp    ra    hi    lo\n"); 
    for (i = 24; i < 32; i++) {
        fprintf(f, "%6d", reg[i]); 
    }
    fprintf(f, "%6d", hi); 
    fprintf(f, "%6d", lo); 
    fprintf(f, "\n"); 
    return;
}

void f_register_log (FILE *f, int pc, float f_reg[32])
{
    int i;
    fprintf(f, "f_reg: "); 
    fprintf(f, "\n"); 
    for (i = 0; i < 8; i++) {
        if (f_reg[i] == 0) {
            fprintf(f, "  %2.2f", 0.0); 
        } else {
            fprintf(f, "  %2.2f ", f_reg[i]); 
        }
    }
    fprintf(f, "\n"); 
    for (i = 8; i < 16; i++) {
        if (f_reg[i] == 0) {
            fprintf(f, "  %2.2f", 0.0); 
        } else {
            fprintf(f, "  %2.2f ", f_reg[i]); 
        }
    }
    fprintf(f, "\n"); 
    for (i = 16; i < 24; i++) {
        if (f_reg[i] == 0) {
            fprintf(f, "  %2.2f", 0.0); 
        } else {
            fprintf(f, "  %2.2f ", f_reg[i]); 
        }
    }
    fprintf(f, "\n"); 
    for (i = 24; i < 32; i++) {
        if (f_reg[i] == 0) {
            fprintf(f, "  %2.2f", 0.0); 
        } else {
            fprintf(f, "  %2.2f ", f_reg[i]); 
        }
    }
    fprintf(f, "\n"); 
    return;
}

void memory_log (FILE *f, int32_t mem[100000])
{
    fprintf(f, "mem:\n"); 
    int i;

    for (i = 0; i < 1000; i += 16) {
        if (mem[i] != INT_MAX) {
            fprintf(f, " %5d:%5d", i, mem[i]); 
            fprintf(f, " %5d:%5d", i+4, mem[i+4]); 
            fprintf(f, " %5d:%5d", i+8, mem[i+8]); 
            fprintf(f, " %5d:%5d\n", i+12, mem[i+12]); 
        }
    }

    return;
}

void log_main (FILE *f, int pc, int32_t reg[32], float f_reg[32], int hi, int lo, int32_t mem[100000], char *option)
{
    register_log(f, pc, reg, hi, lo);
    
    if (option == NULL) {
        return;
    }

    if (strcmp(option, "-fm")  == 0) {
        f_register_log(f, pc, f_reg);      
        memory_log(f, mem);
    } else if (strcmp(option, "-mf")  == 0) {
        f_register_log(f, pc, f_reg);      
        memory_log(f, mem);
    } else if (strcmp(option, "-m")  == 0) {
        memory_log(f, mem);
    } else if (strcmp(option, "-f")  == 0) {
        f_register_log(f, pc, f_reg);      
    }
        
    return;
}
