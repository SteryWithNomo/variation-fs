#include <stdio.h> /* STANDARD INPUT/OUTPUT LIBRARY */

#define VN_FS_IMPLEMENTATION /* DO NOT FORGET THIS */
#define VN_DIRECTORY /* FOR DIRECTORY SECTION */
#include "../../vn_fs.h" /* INCLUDE AFTER DEFINE */

int main()
{
    struct vn_fss vns; /* VARIATION TUI SECURITY */
    vns.fs_security = 0; /* STOP FUNCTION WHEN ERROR RECEIVED */

    printf("\n%s\n", vn_dir("cd", ".", 1024, vns)); /* GET CURRENT DIRECTORY */
    vn_dir("cc", "test", 0, vns); /* CREATE DIRECTORY */

    vn_dir("cd", "test", 0, vns); /* CHANGE DIRECTORY */
    printf("\n%s\n", vn_dir("cd", ".", 1024, vns)); /* GET CURRENT DIRECTORY */
    
    vn_dir("cd", "..", 0, vns); /* CHANGE DIRECTORY */
    printf("\n%s\n", vn_dir("cd", ".", 1024, vns)); /* GET CURRENT DIRECTORY */
    vn_dir("dd", "test", 0, vns); /* DELETE DIRECTORY */

    return 0;
}