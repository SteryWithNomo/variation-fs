<!-- ![vn](img/vn.png) -->
<!-- ![vn_info](img/vn_info.png) -->
<!-- ![vn_warn](img/vn_warn.png) -->
<!-- ![vn_example](img/vn_example.png) -->
<!-- ![vn_wiki](img/vn_wiki.png) -->

# ![vn](img/vn.png) VARIATION FS ![vn](img/vn.png)
Variation-fs is single-header file system library. Written in ansi-c. Simple to use, easy to learn and has small codebase. Also updatable thanks to MIT license (Just fork it then add or remove codes).

### ![vn_info](img/vn_info.png)  1.1v

## ![vn_warn](img/vn_warn.png) Important Note ![vn_warn](img/vn_warn.png)

You need to define ` #define VN_FS_IMPLEMENTATION ` before ` #include "vn_fs.h" `
```c
#define VN_FS_IMPLEMENTATION
#include "vn_fs.h"
```

## ![vn_example](img/vn_example.png) Example ![vn_example](img/vn_example.png)

```c
#include <stdio.h>

#define VN_FS_IMPLEMENTATION
#define VN_READ
#define VN_WRITE
#include "vn_fs.h"

int main()
{
  struct vn_fss vns; /* VARIATION TUI SECURITY */
  vns.fs_security = 0; /* STOP FUNCTION WHEN ERROR RECEIVED */
  
  vn_write("test.txt", "Hey,\nhow are you?\nAre you good?", "ww", vns);
  printf("%s", vn_read("test.txt", "rw", 0, vns));
  
  vnl_write("test.txt", "?ouy era woh", 2, vns);
  printf("%s", vnl_read("test.txt", 2, 4, 6, vns));

  return 0;
}
```

# ![vn](img/vn.png) Compiling as shared-library ![vn](img/vn.png)

![vn_warn](img/vn_warn.png) You can compile as shared-library and develope os specific projects. ![vn_warn](img/vn_warn.png)

![vn_example](img/vn_example.png) How should I compile? ![vn_example](img/vn_example.png)
```
  make win_run 
```
> Windows shared-library (.dll)
>
> If you want to delete this file you can use ` make win_clean `

```
  make uni_run 
```
> Unix shared-library (.so)
>
> If you want to delete this file you can use ` make uni_clean `

### [![vn_wiki](img/vn_wiki.png)](https://github.com/hanilr/variation-fs/wiki) : ![vn_warn](img/vn_warn.png) You can take a look to wiki page if you want learn more! (Under maintenance!) ![vn_warn](img/vn_warn.png)
