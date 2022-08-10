#include <stdio.h> /* STANDARD INPUT/OUTPUT LIBRARY */

#define VN_FS_IMPLEMENTATION /* DO NOT FORGET THIS */
#define VN_READ /* FOR READ SECTION */
#include "../../vn_fs.h" /* INCLUDE AFTER DEFINE */

int main()
{
    printf("\nWhole File:\n%s\n", vn_read("test.txt", "rw", 0)); /* GET WHOLE FILE */
    printf("\n2. Line of File:\n%s\n", vn_read("test.txt", "rl", 2)); /* GET LINE BY LINE */
    printf("\nSpecific Position of File:\n%s\n", vnl_read("test.txt", 3, 4, 7)); /* GET ADVANCE LINE BY LINE */

    return 0;
}