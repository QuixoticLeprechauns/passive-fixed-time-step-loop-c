#ifndef PFTS_LOOP_H
#define PFTS_LOOP_H

#include <windows.h>

static DWORD WINAPI sleep_for(LPVOID lpParam)
{
    Sleep(*((int*)lpParam));
}

/// @brief Runs a process in a passive fixed time step loop. 
/// @param process A function returning int without arguments. Return 0 to exit loop.
/// @param MaxSleepTime The target fixed time step, in miliseconds, for this loop.
/// @param MinSleepTime The minimum period of time, in miliseconds, this loop will sleep between cycles.
void pfts_loop(int (*process) (void), int MaxSleepTime = 16, int MinSleepTime = 1)
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