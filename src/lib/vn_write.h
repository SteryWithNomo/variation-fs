/* VARIATION FS (WRITE) */
#ifndef _VN_WRITE_H
#define _VN_WRITE_H

    void vn_write(char *file_name, char *file_content, char *file_perm, struct vn_fss vns); /* FILE WRITE FUNCTION */

    void vnl_write(char *file_name, char *file_content, int line, struct vn_fss vns); /* FILE ADVANCE LINE WRITE FUNCTION */

#endif /* MADE BY @hanilr */