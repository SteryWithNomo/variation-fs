/* VARIATION FS (LIBRARY) */
/*     MADE BY @hanilr    */
#ifdef _VN_FS_H
#define _VN_FS_H
    #ifdef VN_READ
        char *vn_read(char *file_name, char *file_perm, int file_line); /* FILE READ FUNCTION */

        char *vnl_read(char *file_name, int file_line, int start_pos, int end_pos); /* FILE ADVANCE LINE READ FUNCTION */
    #endif /* VN_READ */

    #ifdef VN_WRITE
        void vn_write(char *file_name, char *file_content, char *file_perm); /* FILE WRITE FUNCTION */

        void vnl_write(char *file_name, char *file_content, int line); /* FILE ADVANCE LINE WRITE FUNCTION */
    #endif /* VN_WRITE */

    #ifdef VN_MANIPULATION
        void vn_man(char *file_name, char *file_to, char *file_perm); /* FILE MANIPULATION FUNCTION */
    #endif /* VN_MANIPULATION */

    #ifdef VN_DIRECTORY
        char *vn_dir(char *dir_com, char *dir_name, int path_buffer); /* DIRECTORY MANIPULATION FUNCTION */
    #endif /* VN_DIRECTORY */
#endif /* SUMMARY SECTION */

#ifdef VN_FS_IMPLEMENTATION
    /* STANDARD LIBRARY */
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #ifdef _WIN32 /* WINDOWS SPECIFIC LIBRARY AND DEFINATION */
        #include <direct.h> /* WINDOWS DIRECTORY MANIPULATION LIBRARY */
        #define getcwd _getcwd
        #define chdir _chdir
        #define rmdir _rmdir
    #else /* COMMONLY UNIX SPECIFIC LIBRARY */
        #include <unistd.h> /* OPERATING SYSTEM API */
        #include <sys/stat.h> /* STRUCTURE OF THE DATA */
        #include <sys/types.h> /* TYPDEF SYMBOLS */
    #endif /* OPERATING SYSTEM SPECIFIC LIBRARY */

    #ifdef VN_READ
        /* ----- COMMAND LIST ---- *
        * 'rw' = READ WHOLE FILE   *
        * 'rl' = READ LINE BY LINE *
        * ------------------------ */

        /* 'file_line' ERROR HANDLING MISSING IN 'vn_read' FUNCTION IN 'rl' SECTION */
        char *vn_read(char *file_name, char *file_perm, int file_line)
        { /* IF YOU DON'T USE 'file_line' VARIABLE YOU MIGHT NEED TO INSERT '0' IN IT */
            FILE *vnr = fopen(file_name, "r"); /* OPEN FILE AS READ OPERATION */
            if(vnr == 0) /* FILE ERROR */
            {
                fprintf(stderr, "\n[ERROR] In 'vn_read()' function. File didn't find!\n");
                exit(1);
            } 

            long file_size;
            fseek(vnr, 0, SEEK_END);
            file_size = ftell(vnr); /* GET FILE SIZE */
            fseek(vnr, 0, SEEK_SET);

            char *file_content = (char*) malloc(file_size+1); /* ALLOCATE 'file_content' */
            memset(file_content, '\0', file_size+1);

            if(strcmp(file_perm, "rw") && strcmp(file_perm, "rl")) /* 'file_perm' ERROR */
            {
                fprintf(stderr, "\n[ERROR] In 'vn_read()' function. 'file_perm' not correct!\n");
                exit(1);
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

        char *vnl_read(char *file_name, int file_line, int start_pos, int end_pos)
        {
            if(start_pos > end_pos)
            {
                fprintf(stderr, "\n[ERROR] In 'vnl_read()' function. 'start_pos' greater than 'end_pos'\n");
                exit(1);
            }

            char *line_temp = vn_read(file_name, "rl", file_line); /* GET CERTAIN LINE OF FILE */
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
    #endif /* VN_READ */

    #ifdef VN_WRITE
        /* ----- COMMAND LIST ----- *
        * 'wc' = CREATE A FILE      *
        * 'ww' = WRITE WHOLE FILE   *
        * 'wa' = WRITE AS APPEND    *
        * ------------------------- */

        void vn_write(char *file_name, char *file_content, char *file_perm)
        { /* IF YOU DON'T USE 'file_content' YOU MIGHT NEED TO INSERT '""' IN IT */
            char *file_form = "w";
            if(!strcmp(file_perm, "wa")) { file_form = "a"; }

            FILE *vnw = fopen(file_name, file_form);
            if(vnw == 0 && strcmp(file_perm, "wc")) /* FILE ERROR */
            {
                fprintf(stderr, "\n[ERROR] In 'vn_write()' function. File didn't find!\n");
                exit(1);    
            }

            if(strcmp(file_perm, "wc") && strcmp(file_perm, "ww") && strcmp(file_perm, "wa")) /* 'file_perm' ERROR */
            {
                fprintf(stderr, "\n[ERROR] In 'vn_write()' function. 'file_perm' not correct!\n");
                exit(1);    
            }
            if(!strcmp(file_perm, "wc")) { fwrite("\0", 1, 1, vnw); } /* CREATE */
            if(!strcmp(file_perm, "ww") || !strcmp(file_perm, "wa")) { fwrite(file_content, 1, strlen(file_content), vnw); } /* WHOLE AND APPEND */

            fclose(vnw);
        } /* IF YOU DON'T USE 'file_line' VARIABLE YOU MIGHT NEED TO INSERT '0' IN IT */

        void vnl_write(char *file_name, char *file_content, int line)
        { /* VN LINE WRITE FUNCTION */
            char *file_temp = vn_read(file_name, "rw", 0); /* GET WHOLE FILE */
            char *line_temp = vn_read(file_name, "rl", line); /* GET CERTAIN LINE OF FILE */

            int i = 0, file_line = 1;
            while(strlen(file_temp)+1 > i) /* GET FILE NEW LINE COUNT */
            {
                if(file_temp[i] == '\n') { file_line+=1; }
                i+=1;
            }
            if(line > file_line) /* ERROR WHEN ENTERED LINE INVAILD */
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

            vn_write(file_name, start_temp, "ww"); /* WRITE START BUFFER TO FILE AS 'ww' (WRITE WHOLE) */
            vn_write(file_name, "\n", "wa"); /* ADD NEW LINE */
            vn_write(file_name, file_content, "wa"); /* WRITE NEW LINE TO FILE AS 'wa' (APPEND) */
            if(line != file_line) /* IF LAST LINE OF FILE */
            {
                while(end_len > i) /* GET END BUFFER */
                {
                    end_temp[i] = file_temp[start_len+line_len+i];
                    i+=1;
                }
                end_temp[i] = '\0'; /* ADD END OF LINE TO END BUFFER */

                vn_write(file_name, "\n", "wa"); /* ADD NEW LINE */
                vn_write(file_name, end_temp, "wa"); /* WRITE END BUFFER TO FILE AS 'wa' (APPEND) */
            }

            free(file_temp);
            free(line_temp);
            free(start_temp);
            free(end_temp);    
        } /* ALGORITHM OF THIS FUNCTION: GET START AND END SUBSTRINGS AND THEN WRITE BUFFER BY BUFFER */
    #endif /* VN_WRITE */

    #ifdef VN_MANIPULATION
        /* --------- COMMAND LIST -------- *
        * 'del' = DELETE AFTER COPY/MOVE   *
        * -------------------------------- */

        void vn_man(char *file_name, char *file_to, char *file_perm)
        {
            char *file_content = vn_read(file_name, "rw", 0); /* GET WHOLE FILE*/
            if(!strcmp(file_perm, "del")) { remove(file_name); } /* IF USER WANT TO DELETE */
            if(strcmp(file_perm, "del")) /* 'file_perm' ERROR */
            {
                fprintf(stderr, "\n[ERROR] In 'vn_man()' function. 'file_perm' not correct!\n");
                exit(1);
            }

            vn_write(file_to, file_content, "ww"); /* WRITE TO NEW PATH */
            free(file_content); /* 'vn_read' FUNCTION NEED TO BE FREE AFTER USE */
        }
    #endif /* VN_MANIPULATION */

    #ifdef VN_DIRECTORY
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
    #endif /* VN_DIRECTORY */
#endif /* VN_FS_IMPLEMENTATION */