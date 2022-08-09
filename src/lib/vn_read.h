/* VARIATION FS (READ) */
#ifndef _VN_READ_H
#define _VN_READ_H

    char *vn_read(char *file_name, char *file_perm, int file_line); /* FILE READ FUNCTION */

    char *vnl_read(char *file_name, int file_line, int start_pos, int end_pos); /* FILE ADVANCE LINE READ FUNCTION */

#endif /* MADE BY @hanilr */