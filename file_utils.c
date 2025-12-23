#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32)
#include <windows.h>

#include <commdlg.h>
#endif

// 使用静态变量存储路径，确保返回的指针在函数结束后依然有效
static char global_file_path[1024];

const char *
ShowOpenFileDialog ()
{
        memset (global_file_path, 0, sizeof (global_file_path));

#if defined(_WIN32)
        OPENFILENAME ofn;
        ZeroMemory (&ofn, sizeof (ofn));
        ofn.lStructSize = sizeof (ofn);
        ofn.hwndOwner   = NULL;
        ofn.lpstrFile   = global_file_path;
        ofn.nMaxFile    = sizeof (global_file_path);
        ofn.lpstrFilter = "Raylib Painter Files (*.dat)\0*.dat\0All Files\0*.*\0";
        ofn.lpstrDefExt = "dat";
        ofn.Flags       = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetOpenFileName (&ofn))
                return global_file_path;

#elif defined(__APPLE__)
        FILE *pipe = popen ("osascript -e 'POSIX path of (choose file)' 2>/dev/null", "r");
        if (pipe)
                {
                        if (fgets (global_file_path, sizeof (global_file_path), pipe))
                                {
                                        global_file_path[strcspn (global_file_path, "\r\n")] = 0;
                                        pclose (pipe);
                                        return global_file_path[0] != '\0' ? global_file_path
                                                                           : NULL;
                                }
                        pclose (pipe);
                }

#elif defined(__linux__)
        FILE *pipe = popen ("zenity --file-selection --title=\"Open File\" 2>/dev/null", "r");
        if (pipe)
                {
                        if (fgets (global_file_path, sizeof (global_file_path), pipe))
                                {
                                        global_file_path[strcspn (global_file_path, "\r\n")] = 0;
                                        pclose (pipe);
                                        return global_file_path[0] != '\0' ? global_file_path
                                                                           : NULL;
                                }
                        pclose (pipe);
                }
#endif
        return NULL;
}

const char *
ShowSaveFileDialog ()
{
        memset (global_file_path, 0, sizeof (global_file_path));

#if defined(_WIN32)
        OPENFILENAME ofn;
        ZeroMemory (&ofn, sizeof (ofn));
        ofn.lStructSize = sizeof (ofn);
        ofn.lpstrFile   = global_file_path;
        ofn.nMaxFile    = sizeof (global_file_path);
        ofn.lpstrFilter = "Raylib Painter Files (*.dat)\0*.dat\0All Files\0*.*\0";
        ofn.lpstrDefExt = "dat";
        ofn.Flags       = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
        if (GetSaveFileName (&ofn))
                return global_file_path;

#elif defined(__APPLE__)
        // macOS: AppleScript 保存对话框
        FILE *pipe = popen (
            "osascript -e 'POSIX path of (choose file name with prompt \"Save As:\")' 2>/dev/null",
            "r");
        if (pipe)
                {
                        if (fgets (global_file_path, sizeof (global_file_path), pipe))
                                {
                                        global_file_path[strcspn (global_file_path, "\r\n")] = 0;
                                        pclose (pipe);
                                        return global_file_path[0] != '\0' ? global_file_path
                                                                           : NULL;
                                }
                        pclose (pipe);
                }

#elif defined(__linux__)
        // Linux: Zenity 保存模式
        FILE *pipe = popen ("zenity --file-selection --save --confirm-overwrite 2>/dev/null", "r");
        if (pipe)
                {
                        if (fgets (global_file_path, sizeof (global_file_path), pipe))
                                {
                                        global_file_path[strcspn (global_file_path, "\r\n")] = 0;
                                        pclose (pipe);
                                        return global_file_path[0] != '\0' ? global_file_path
                                                                           : NULL;
                                }
                        pclose (pipe);
                }
#endif
        return NULL;
}
