#include <stdio.h> /* STANDARD INPUT/OUTPUT LIBRARY */

#define VN_FS_IMPLEMENTATION /* DO NOT FORGET THIS */
#define VN_DIRECTORY /* FOR DIRECTORY SECTION */
#include "../../vn_fs.h" /* INCLUDE AFTER DEFINE */

int main()
{
    printf("\n%s\n", vn_dir("cd", ".", 1024)); /* GET CURRENT DIRECTORY */
    vn_dir("cc", "test", 0); /* CREATE DIRECTORY */
    vn_dir("cd", "test", 0); /* CHANGE DIRECTORY */
    printf("\n%s\n", vn_dir("cd", ".", 1024)); /* GET CURRENT DIRECTORY */
    vn_dir("cd", "..", 0); /* CHANGE DIRECTORY */
    printf("\n%s\n", vn_dir("cd", ".", 1024)); /* GET CURRENT DIRECTORY */
    vn_dir("dd", "test", 0); /* DELETE DIRECTORY */

    return 0;
}