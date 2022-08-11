#include <stdio.h> /* STANDARD INPUT/OUTPUT LIBRARY */

#define VN_FS_IMPLEMENTATION /* DO NOT FORGET THIS */
#define VN_READ /* FOR 'vnl_write' FUNCTION */
#define VN_WRITE /* FOR WRITE SECTION */
#include "../../vn_fs.h" /* INCLUDE AFTER DEFINE */

int main()
{
    struct vn_fss vns; /* VARIATION TUI SECURITY */
    vns.fs_security = 0; /* STOP FUNCTION WHEN ERROR RECEIVED */

    vn_write("test.txt", "", "wc", vns); /* CREATE A FILE */
    vn_write("test.txt", "Hey,\nhow are you?\nAre you good?", "ww", vns); /* WRITE WHOLE FILE */
    vn_write("test.txt", "\nFoo and Bar. This is the way!", "wa", vns); /* WRITE AS APPEND */
    vnl_write("test.txt", "?ouy era woh", 2, vns);  /* CHANGE CERTAIN LINE */

    return 0;
}