/* VARIATION FS (WRITE) */

/* STANDARD LIBRARY */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* DIY LIBRARY */
#include "lib/vn_write.h"
#include "lib/vn_conf.h"
#include "lib/vn_read.h"

/* ----- COMMAND LIST ----- *
* 'wc' = CREATE A FILE      *
* 'ww' = WRITE WHOLE FILE   *
* 'wa' = WRITE AS APPEND    *
* ------------------------- */

void vn_write(char *file_name, char *file_content, char *file_perm, struct vn_fss vns)
{ /* IF YOU DON'T USE 'file_content' YOU MIGHT NEED TO INSERT '""' IN IT */
    char *file_form = "w";
    if(!strcmp(file_perm, "wa")) { file_form = "a"; }

    FILE *vnw = fopen(file_name, file_form);
    if(vnw == 0 && strcmp(file_perm, "wc") && vns.fs_security !=2) /* FILE ERROR */
    {
        fprintf(stderr, "\n[ERROR] In 'vn_write()' function. File didn't find!\n");
        exit(1);    
    }

    if(strcmp(file_perm, "wc") && strcmp(file_perm, "ww") && strcmp(file_perm, "wa") && vns.fs_security !=2) /* 'file_perm' ERROR */
    {
        fprintf(stderr, "\n[ERROR] In 'vn_write()' function. 'file_perm' not correct!\n");
        exit(1);    
    }
    if(!strcmp(file_perm, "wc")) { fwrite("\0", 1, 1, vnw); } /* CREATE */
    if(!strcmp(file_perm, "ww") || !strcmp(file_perm, "wa")) { fwrite(file_content, 1, strlen(file_content), vnw); } /* WHOLE AND APPEND */

    fclose(vnw);
} /* IF YOU DON'T USE 'file_line' VARIABLE YOU MIGHT NEED TO INSERT '0' IN IT */

void vnl_write(char *file_name, char *file_content, int line, struct vn_fss vns)
{ /* VN LINE WRITE FUNCTION */
    char *file_temp = vn_read(file_name, "rw", 0, vns); /* GET WHOLE FILE */
    char *line_temp = vn_read(file_name, "rl", line, vns); /* GET CERTAIN LINE OF FILE */

    int i = 0, file_line = 1;
    while(strlen(file_temp)+1 > i) /* GET FILE NEW LINE COUNT */
    {
        if(file_temp[i] == '\n') { file_line+=1; }
        i+=1;
    }
    if(line > file_line && vns.fs_security !=2) /* ERROR WHEN ENTERED LINE INVAILD */
    {
        fprintf(stderr, "\n[ERROR] In 'vnl_write()' function. 'line' value greater than file line!\n");
        exit(1);
    }

    char *wstart_temp = strstr(file_temp, line_temp); /* WITHOUT START */
    int start_len = strlen(file_temp) - strlen(wstart_temp); /* START SUBSTRING LENGTH */
    int line_len = strlen(line_temp); /* OLD LINE LENGTH */
    int end_len = strlen(file_temp) - (start_len+line_len); /* END SUBSTRING LENGTH */
    
    char *start_temp = (char*) malloc(start_len); /* START BUFFER */
    char *end_temp = (char*) malloc(end_len); /* END BUFFER */

    i=0;
    while(start_len > i) /* GET START BUFFER */
    {
        start_temp[i] = file_temp[i];
        i+=1;
    }
    start_temp[start_len-1] = '\0'; /* ADD END OF LINE TO START BUFFER */
    i=0;

    vn_write(file_name, start_temp, "ww", vns); /* WRITE START BUFFER TO FILE AS 'ww' (WRITE WHOLE) */
    vn_write(file_name, "\n", "wa", vns); /* ADD NEW LINE */
    vn_write(file_name, file_content, "wa", vns); /* WRITE NEW LINE TO FILE AS 'wa' (APPEND) */
    if(line != file_line) /* IF LAST LINE OF FILE */
    {
        while(end_len > i) /* GET END BUFFER */
        {
            end_temp[i] = file_temp[start_len+line_len+i];
            i+=1;
        }
        end_temp[i] = '\0'; /* ADD END OF LINE TO END BUFFER */

        vn_write(file_name, "\n", "wa", vns); /* ADD NEW LINE */
        vn_write(file_name, end_temp, "wa", vns); /* WRITE END BUFFER TO FILE AS 'wa' (APPEND) */
    }

    free(file_temp);
    free(line_temp);
    free(start_temp);
    free(end_temp);    
} /* ALGORITHM OF THIS FUNCTION: GET START AND END SUBSTRINGS AND THEN WRITE BUFFER BY BUFFER */

/* MADE BY @hanilr */