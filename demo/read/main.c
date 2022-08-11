#include <stdio.h> /* STANDARD INPUT/OUTPUT LIBRARY */

#define VN_FS_IMPLEMENTATION /* DO NOT FORGET THIS */
#define VN_READ /* FOR READ SECTION */
#include "../../vn_fs.h" /* INCLUDE AFTER DEFINE */

int main()
{
    struct vn_fss vns; /* VARIATION TUI SECURITY */
    vns.fs_security = 0; /* STOP FUNCTION WHEN ERROR RECEIVED */

    printf("\nWhole File:\n%s\n", vn_read("test.txt", "rw", 0, vns)); /* GET WHOLE FILE */
    printf("\n2. Line of File:\n%s\n", vn_read("test.txt", "rl", 2, vns)); /* GET LINE BY LINE */
    printf("\nSpecific Position of File:\n%s\n", vnl_read("test.txt", 3, 4, 7, vns)); /* GET ADVANCE LINE BY LINE */

    return 0;
}