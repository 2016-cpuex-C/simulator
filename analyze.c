#include <string.h>

analyze_how_many_times_called(char label[10000][100], int how_many_times_called[10000]) {
    
    printf("\nANALYZE START\n");
    int i;
    for (i = 0; i < 10000; i++) {
        if (how_many_times_called[i] != 0) {
            printf("%d  ", i);
            printf("%d\n", how_many_times_called[i]);
            
        }
    }
    printf("ANALYZE FINISHED\n");
}
