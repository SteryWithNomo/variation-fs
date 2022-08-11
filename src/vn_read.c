/* VARIATION FS (READ) */

/* STANDARD LIBRARY */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* DIY LIBRARY */
#include "lib/vn_read.h"
#include "lib/vn_conf.h"

/* ----- COMMAND LIST ---- *
* 'rw' = READ WHOLE FILE   *
* 'rl' = READ LINE BY LINE *
* ------------------------ */

/* 'file_line' ERROR HANDLING MISSING IN 'vn_read' FUNCTION IN 'rl' SECTION */
char *vn_read(char *file_name, char *file_perm, int file_line, struct vn_fss vns)
{ /* IF YOU DON'T USE 'file_line' VARIABLE YOU MIGHT NEED TO INSERT '0' IN IT */
    FILE *vnr = fopen(file_name, "r"); /* OPEN FILE AS READ OPERATION */
    if(vnr == 0 && vns.fs_security !=2) /* FILE ERROR */
    {
        fprintf(stderr, "\n[ERROR] In 'vn_read()' function. File didn't find!\n");
        if(vns.fs_security == 0) { exit(1); }
    } 

    long file_size;
    fseek(vnr, 0, SEEK_END);
    file_size = ftell(vnr); /* GET FILE SIZE */
    fseek(vnr, 0, SEEK_SET);

    char *file_content = (char*) malloc(file_size+1); /* ALLOCATE 'file_content' */
    memset(file_content, '\0', file_size+1);

    if(strcmp(file_perm, "rw") && strcmp(file_perm, "rl") && vns.fs_security !=2) /* 'file_perm' ERROR */
    {
        fprintf(stderr, "\n[ERROR] In 'vn_read()' function. 'file_perm' not correct!\n");
        if(vns.fs_security == 0) { exit(1); }
    }
    if(!strcmp(file_perm, "rw") && file_line == 0) { fread(file_content, file_size+1, 1, vnr); } /* READ WHOLE FILE */
    if(!strcmp(file_perm, "rl")) /* READ LINE BY LINE */
    {
        int current_line = 0;
        while(file_line > current_line)
        {
            fgets(file_content, file_size+1, vnr); /* GET FILE LINE BY LINE */
            current_line+=1;
        }
        file_content[strlen(file_content)+1] = '\0'; /* REPLACE WITH NEW LINES TO END OF THE LINES */
    }

    fclose(vnr); /* CLOSE FILE */
    return file_content;
} /* NEED TO BE 'free()' AFTER USE */

char *vnl_read(char *file_name, int file_line, int start_pos, int end_pos, struct vn_fss vns)
{
    if(start_pos > end_pos && vns.fs_security !=2)
    {
        fprintf(stderr, "\n[ERROR] In 'vnl_read()' function. 'start_pos' greater than 'end_pos'\n");
        if(vns.fs_security == 0) { exit(1); }
    }

    char *line_temp = vn_read(file_name, "rl", file_line, vns); /* GET CERTAIN LINE OF FILE */
    char *line_content = (char*) malloc(end_pos-start_pos+1); /* ALLOCATE 'line_content' */

    int i = 0;
    while(end_pos-start_pos > i) /* GET CERTAIN POSITION WITH LENGTH */
    {
        line_content[i] = line_temp[start_pos+i];
        i+=1;
    }
    line_content[i] = '\0';

    free(line_temp);
    return line_content;
}

/* MADE BY @hanilr */