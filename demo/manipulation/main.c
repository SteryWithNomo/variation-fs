#include <stdio.h> /* STANDARD INPUT/OUTPUT LIBRARY */

#define VN_FS_IMPLEMENTATION /* DO NOT FORGET THIS */
#define VN_READ /* FOR 'vn_man' FUNCTION */
#define VN_WRITE /* FOR 'vn_man' FUNCTION */
#define VN_MANIPULATION /* FOR MANIPULATION SECTION */
#include "../../vn_fs.h" /* INCLUDE AFTER DEFINE */

int main()
{
    vn_man("test_1.txt", "test_1_renamed.txt", "del"); /* NAME CHANGE */
    vn_man("test_2.txt", "test_2/test_2_move.txt", "del"); /* MOVE */
    vn_man("test_3.txt", "test_3/test_3_copy.txt", "del"); /* COPY */

    return 0;
}