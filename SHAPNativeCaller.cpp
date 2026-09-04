
#include "SHAPNativeCaller.h"

#include <limits.h>


//static constexpr uintptr_t MODULEBASE = 0x400000;

int killPlayerWrapper(void* restartLevelFuncPtr, void* thisPtr)
{
    int ret;
    __asm__ volatile
    (
        "pushal\n"
        "pushfl\n"
        "mov %1, %%esi\n"
        "call *%2\n"
        "popfl\n"
        "popal\n"
        : "=a"(ret)
        : "r"(thisPtr), "r"(restartLevelFuncPtr)
        : "memory"
    );
    return ret;
}

int modifyLivesWrapper(void* restartLevelFuncPtr, int amount)
{
    int ret;
    __asm__ volatile
    (
        "pushal\n"
        "pushfl\n"
        "mov $0x0, %%ecx\n"
        "mov %2, %%edx\n"
        "call *%1\n"
        "popfl\n"
        "popal\n"
        : "=a"(ret)
        : "r"(restartLevelFuncPtr), "r"(amount)
        : "memory"
    );
    return ret;
}

int givePlayerShieldWrapper(void* giveShieldFuncPtr)
{
    int ret;
    __asm__ volatile
    (
        "pushal\n"
        "pushfl\n"
        "mov $0x0, %%ebx\n"
        "call *%1\n"
        "popfl\n"
        "popal\n"
        : "=a"(ret)
        : "r"(giveShieldFuncPtr)
        : "memory"
    );
    return ret;
}

int playSoundWrapper(void* playSoundFuncPtr, void* soundStreamPtr, const int soundId)
{
    int ret;
    __asm__ volatile
    (
        "pushal\n"
        "pushfl\n"
        "mov (%2), %%esi\n"
        "push $0x0\n"
        "push $0x0\n"
        "mov %3, %%ebx\n"
        "call *%1\n"
        "popfl\n"
        "popal\n"
        : "=a"(ret)
        : "r"(playSoundFuncPtr), "r"(soundStreamPtr), "r" (soundId)
        : "memory"
    );
    return ret;
}

int playAFSSoundWrapper(void* playAFSSoundFuncPtr, void* soundStreamPtr, const int soundId)
{
    int ret;
    __asm__ volatile
    (
        "pushal\n"
        "pushfl\n"
        "push $0x7\n"
        "push %3\n"
        "mov $0x403, %%ebx\n"
        "call *%1\n"
        "add $0x8, %%esp\n"
        "popfl\n"
        "popal\n"
        : "=a"(ret)
        : "r"(playAFSSoundFuncPtr), "r"(soundStreamPtr), "r" (soundId)
        : "memory"
    );
    return ret;
}


bool isPtrValid(const unsigned int ptr, const int moduleBase)
{
    return moduleBase < ptr && ptr < UINT_MAX;
}


extern "C" __declspec(dllexport) void __cdecl RestartLevel(const int moduleBase)
{
    //mov esi, esiPtrAddr
    //call restartFuncAddr
    //Restart Level is usercall (which is not a thing)

    void* thisPtr = reinterpret_cast<void*>(moduleBase + 0x4D66E8);
    void* restartLevelFuncPtr = reinterpret_cast<void*>(moduleBase + 0x4520);
    int result = killPlayerWrapper(restartLevelFuncPtr, thisPtr);
}

extern "C" __declspec(dllexport) void __cdecl ModifyLives(const int moduleBase, const int amount)
{
    void* lifeSetFuncPtr = reinterpret_cast<void*>(moduleBase + 0x23B60);
    int result = modifyLivesWrapper(lifeSetFuncPtr, amount);
}

extern "C" __declspec(dllexport) void __cdecl GiveShield(const int moduleBase)
{
    void* giveShieldFuncPtr = reinterpret_cast<void*>(moduleBase + 0x1821C0);
    int result = givePlayerShieldWrapper(giveShieldFuncPtr);
}

extern "C" __declspec(dllexport) void __cdecl PlaySound(const int moduleBase, const int soundId)
{
    void* playSoundFuncPtr = reinterpret_cast<void*>(moduleBase + 0x40720);
    void* soundStreamPtr = reinterpret_cast<void*>(moduleBase + 0x62F8B0);
    if (!isPtrValid(reinterpret_cast<unsigned int>(soundStreamPtr), moduleBase))
    {
        return;
    }
    int result = playSoundWrapper(playSoundFuncPtr, soundStreamPtr, soundId);
}

extern "C" __declspec(dllexport) void __cdecl PlayAFSSound(const int moduleBase, const int soundId)
{
    void* playAFSSoundFuncPtr = reinterpret_cast<void*>(moduleBase + 0x3EC20);
    void* soundStreamPtr = reinterpret_cast<void*>(moduleBase + 0x62F8B0);
    if (!isPtrValid(reinterpret_cast<unsigned int>(soundStreamPtr), moduleBase))
    {
        return;
    }
    int result = playAFSSoundWrapper(playAFSSoundFuncPtr, soundStreamPtr, soundId);
}











