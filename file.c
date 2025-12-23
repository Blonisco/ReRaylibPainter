#include "screens.h"
#include <string.h>
static Mode next_mode = FILE_READ;
static char name[1024];

void
init_file ()
{
        next_mode = FILE_READ;
}
FILE *
update_mode_file (char *file_name, int is_new_file)
{
        const char *path = NULL;

        if (file_name[0] == '\0')
                {
                        if (is_new_file)
                                {
                                        path = ShowSaveFileDialog ();
                                }
                        else
                                {
                                        path = ShowOpenFileDialog ();
                                }

                        if (path != NULL)
                                {
                                        strcpy (file_name, path);
                                }
                        else
                                {
                                        next_mode = MENU;
                                        return NULL;
                                }
                }

        FILE *fp = fopen (file_name, "rb+");
        if (fp == NULL)
                {
                        fp = fopen (file_name, "wb+");
                }

        if (fp != NULL)
                {
                        next_mode = DRAW;
                        return fp;
                }
        else
                {
                        next_mode = MENU;
                        return NULL;
                }
}

Mode
return_mode_file ()
{
        return next_mode;
}
