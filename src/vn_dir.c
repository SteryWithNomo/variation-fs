/* VARIATION FS (DIRECTORY) */

/* STANDARD LIBRARY */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* DIY LIBRARY */
#include "lib/vn_dir.h"

#ifdef _WIN32
    #include <direct.h> /* WINDOWS DIRECTORY MANIPULATION LIBRARY */
    #define getcwd _getcwd
    #define chdir _chdir
    #define rmdir _rmdir
#else
    #include <unistd.h> /* OPERATING SYSTEM API */
    #include <sys/stat.h> /* STRUCTURE OF THE DATA */
    #include <sys/types.h> /* TYPDEF SYMBOLS */
#endif

/* ---------------- COMMAND LIST ---------------- *
* 'cd' = CHANGE DIRECTORY                         *
* 'cd' (WITH '.') = RETURN WITH CURRENT DIRECTORY *
* 'cc' = CREATE DIRECTORY                         *
* 'dd' = DELETE DIRECTORY                         *
* ----------------------------------------------- */

/* SOME COMMANDS NOT SECURE */
char *vn_dir(char *dir_com, char *dir_name, int path_buffer)
{ /* 'dir_com' = DIRECTORY COMMAND */
    if(strcmp(dir_name, "cd") && strcmp(dir_name, "cc") && strcmp(dir_name, "dd")) /* 'dir_com' ERROR */
    {
        fprintf(stderr, "\n[ERROR] In 'vn_dir()' function. 'dir_com' not correct!\n");
        exit(1);
    }
    if(!strcmp(dir_com, "cd") && !strcmp(dir_name, ".") && path_buffer != 0) /* CURRENT DIRECTORY */
    {
        char cd_buffer[path_buffer];
        getcwd(cd_buffer, path_buffer); /* GET CURRENT WORKING DIRECTORY */
        char *current_dir = cd_buffer; /* YOU CAN'T RETURN LOCAL VARIABLES EXCEPT POINTERS */
        return current_dir;
    }
    if(!strcmp(dir_name, "")) /* ERROR WHEN 'dir_name' EMPTY */
    {
        fprintf(stderr, "\n[ERROR] In 'vn_dir()' function. 'dir_name' is empty!\n");
        exit(1);
    }

    if(!strcmp(dir_com, "cd")) { chdir(dir_name); } /* CHANGE DIRECTORY */
    if(!strcmp(dir_com, "cc")) /* CREATE DIRECTORY */
    {
        #ifdef _WIN32
            _mkdir(dir_name);
        #else
            mkdir(dir_name, 0777); /* LINUX DIRECTORY PERMISSION MAKE IT CHANGABLE */
        #endif
    }
    if(!strcmp(dir_com, "dd")) { rmdir(dir_name); } /* DELETE DIRECTORY */
} /* 'path_buffer' IS BUFFER FOR 'current_dir' */

/* MADE BY @hanilr */