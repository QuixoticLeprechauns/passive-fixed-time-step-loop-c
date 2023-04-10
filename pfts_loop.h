#ifndef PFTS_LOOP_H
#define PFTS_LOOP_H

#include <windows.h>
static DWORD WINAPI sleep_for(LPVOID lpParam)
{
    Sleep(*((int*)lpParam));
}

void pfts_loop(int (*process) (void), int MaxSleepTime, int MinSleepTime)
{
    int retval;
    do
    {
        HANDLE ts = CreateThread(NULL, 0, sleep_for, &MaxSleepTime, 0, NULL);
        retval = process();
        Sleep(MinSleepTime);

        WaitForSingleObject(ts, INFINITE);
        CloseHandle(ts);
    } while (retval != 0);
}

#endif