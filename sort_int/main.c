// main.c
#include "old_school_sort.h"
#include "new_school_sort.h"
#include "sort_with_ref.h"
#include "sort_int.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("Usage: %s <filein.txt> <fileout.txt>\n", argv[0]);
        return 1;
    }
    printf("infile: %s, outfile: %s\n", __argv[1], __argv[2]);

    int ret;
    // Call old_school_sort function
    //ret = old_school_sort(__argv[1], __argv[2]);
    
    // Call new_school_sort function
    //ret = new_school_sort(__argv[1], __argv[2]);

    // Call sort_int function
    //ret = sort_int(__argv[1], __argv[2]);

    // Call sort_with_ref function
    ret = sort_with_ref(__argv[1], __argv[2]);

    return ret;
}
