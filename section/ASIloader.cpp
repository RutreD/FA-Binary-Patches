typedef struct _FILETIME
{
    unsigned long dwLowDateTime;
    unsigned long dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;

typedef struct _WIN32_FIND_DATAA
{
    unsigned long dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    unsigned long nFileSizeHigh;
    unsigned long nFileSizeLow;
    unsigned long dwReserved0;
    unsigned long dwReserved1;
    char cFileName[260];
    char cAlternateFileName[14];
    unsigned long dwFileType;
    unsigned long dwCreatorType;
    unsigned short wFinderFlags;
} WIN32_FIND_DATAA, *PWIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;

void ASILoader()
{
    auto LoadLibrary = *reinterpret_cast<void *(__stdcall **)(const char *)>(0xC0F488);
    auto FindFirstFile = *reinterpret_cast<void *(__stdcall **)(const char *, LPWIN32_FIND_DATAA)>(0xC0F370);
    auto FindNextFile = *reinterpret_cast<int(__stdcall **)(void *, LPWIN32_FIND_DATAA)>(0xC0F36C);
    auto FindClose = *reinterpret_cast<int(__stdcall **)(void *)>(0xC0F494);

    WIN32_FIND_DATAA foundFile;
    auto hFind = FindFirstFile("*.asi", &foundFile);
    if (hFind != reinterpret_cast<void *>(-1))
    {
        do
        {
            LoadLibrary(foundFile.cFileName);
        } while (FindNextFile(hFind, &foundFile));
        FindClose(hFind);
    }

    __asm(
        "ADD ESP,0x2C;"
        "POP EBX;"
        "POP ESI;"
        "POP EDI;"
        "POP EBP;"
        "JMP 0xA8ED7E;");
}