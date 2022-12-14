/* VARIATION FS (MANIPULATION) */

/* STANDARD LIBRARY */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* DIY LIBRARY */
#include "lib/vn_man.h"
#include "lib/vn_conf.h"
#include "lib/vn_read.h"
#include "lib/vn_write.h"

/* --------- COMMAND LIST -------- *
* 'del' = DELETE AFTER COPY/MOVE   *
* -------------------------------- */

void vn_man(char *file_name, char *file_to, char *file_perm, struct vn_fss vns)
{
    char *file_content = vn_read(file_name, "rw", 0, vns); /* GET WHOLE FILE*/
    if(!strcmp(file_perm, "del")) { remove(file_name); } /* IF USER WANT TO DELETE */
    if(strcmp(file_perm, "del") && vns.fs_security !=2) /* 'file_perm' ERROR */
    {
        fprintf(stderr, "\n[ERROR] In 'vn_man()' function. 'file_perm' not correct!\n");
        if(vns.fs_security == 0) { exit(1); }
    }

    vn_write(file_to, file_content, "ww", vns); /* WRITE TO NEW PATH */
    free(file_content); /* 'vn_read' FUNCTION NEED TO BE FREE AFTER USE */
}

/* MADE BY @hanilr */