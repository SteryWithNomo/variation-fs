#include <stdio.h> /* STANDARD INPUT/OUTPUT LIBRARY */

#define VN_FS_IMPLEMENTATION /* DO NOT FORGET THIS */
#define VN_READ /* FOR 'vnl_write' FUNCTION */
#define VN_WRITE /* FOR WRITE SECTION */
#include "../../vn_fs.h" /* INCLUDE AFTER DEFINE */

int main()
{
    vn_write("test.txt", "", "wc"); /* CREATE A FILE */
    vn_write("test.txt", "Hey,\nhow are you?\nAre you good?", "ww"); /* WRITE WHOLE FILE */
    vn_write("test.txt", "\nFoo and Bar. This is the way!", "wa"); /* WRITE AS APPEND */
    vnl_write("test.txt", "?ouy era woh", 2);  /* CHANGE CERTAIN LINE */

    return 0;
}