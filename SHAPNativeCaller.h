//
// Created by ethicallogic on 9/2/26.
//

#ifndef SHAP_NATIVE_CALLER_SHAPNATIVECALLER_H
#define SHAP_NATIVE_CALLER_SHAPNATIVECALLER_H


extern "C" __declspec(dllexport) void __cdecl RestartLevel(int moduleBase);
extern "C" __declspec(dllexport) void __cdecl ModifyLives(int moduleBase, int amount);
extern "C" __declspec(dllexport) void __cdecl GiveShield(int moduleBase);
extern "C" __declspec(dllexport) void __cdecl PlaySound(int moduleBase, int soundId);
extern "C" __declspec(dllexport) void __cdecl PlayAFSSound(int moduleBase, int soundId);

#endif //SHAP_NATIVE_CALLER_SHAPNATIVECALLER_H
