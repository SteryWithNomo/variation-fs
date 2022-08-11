/* VARIATION FS (CONFIGURATION) */
#ifndef _VN_CONF_H
#define _VN_CONF_H

    struct vn_fss /* '0' STOP FUNCTION WHEN ERROR RECEIVED */
    { /* '1' DON'T STOP FUNCTION WHEN ERROR RECEIVED */
        int fs_security; /* ONLY '0', '1' AND '2' CAN PROCESS */
    }; /* '2' DON'T DO ANYTHING WHEN ERROR RECEIVED */
    /* ------------------------------ */

#endif /* MADE BY @hanilr */