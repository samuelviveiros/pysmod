# PySMod
This SourceMod extension allows you to write plugins using Python.


## Which SDKs am I using?

To compile this extension I'am using the following SDKs (these are the versions running on my L4D server):

- sourcemod-1.9.0.6245 ([available here](https://github.com/alliedmodders/sourcemod/commit/50b5bb1))
- metamod-source-1.10.7-dev: ([available here](https://github.com/alliedmodders/metamod-source/commit/198f723))


## Source engine macros

These are the macros used in SM 1.9. I was able to find them just by searching the source code. You'll notice that not all of them are set in the Solution properties of the `sample_ext` extension that comes with the SM source code.

```
SE_EPISODEONE=1
SE_DARKMESSIAH=2
SE_ORANGEBOX=3
SE_BLOODYGOODTIME=4
SE_EYE=5
SE_CSS=6
SE_HL2DM=7
SE_DODS=8
SE_TF2=9
SE_LEFT4DEAD=10
SE_NUCLEARDAWN=11
SE_LEFT4DEAD2=12
SE_ALIENSWARM=13
SE_PORTAL2=14
SE_CSGO=15
SE_SDK2013=16
SE_BMS=17
SE_BLADE=18
SE_INSURGENCY=19
SE_DOI=20
SE_CONTAGION=21
```


## About Python

Right now this extension is working on Windows 10 using Python 3.9.13 and 3.11.1 (both 32 bits).


## Troubleshooting

### I receive the following error when compiling the extension: `Cannot open include file: 'sp_vm_types.h': No such file or directory`

```
1>Build FAILED.
1>
1>C:\Users\Dartz\Desktop\mods\source\sdk\sourcemod-1.9.0.6245_zombieverse\public\IShareSys.h(40,10): fatal error C1083: Cannot open include file: 'sp_vm_types.h': No such file or directory (compiling source file ..\extension.cpp)
1>C:\Users\Dartz\Desktop\mods\source\sdk\sourcemod-1.9.0.6245_zombieverse\public\IShareSys.h(40,10): fatal error C1083: Cannot open include file: 'sp_vm_types.h': No such file or directory (compiling source file ..\sdk\smsdk_ext.cpp)
1>C:\Users\Dartz\Desktop\mods\source\sdk\sourcemod-1.9.0.6245_zombieverse\public\IShareSys.h(40,10): fatal error C1083: Cannot open include file: 'sp_vm_types.h': No such file or directory (compiling source file ..\modules\files.cpp)
1>C:\Users\Dartz\Desktop\mods\source\sdk\sourcemod-1.9.0.6245_zombieverse\public\IShareSys.h(40,10): fatal error C1083: Cannot open include file: 'sp_vm_types.h': No such file or directory (compiling source file ..\modules\logging.cpp)
1>C:\Users\Dartz\Desktop\mods\source\sdk\sourcemod-1.9.0.6245_zombieverse\public\IShareSys.h(40,10): fatal error C1083: Cannot open include file: 'sp_vm_types.h': No such file or directory (compiling source file ..\modules\console.cpp)
1>C:\Users\Dartz\Desktop\mods\source\sdk\sourcemod-1.9.0.6245_zombieverse\public\IShareSys.h(40,10): fatal error C1083: Cannot open include file: 'sp_vm_types.h': No such file or directory (compiling source file ..\modules\sourcemod.cpp)
1>C:\Users\Dartz\Desktop\mods\source\sdk\sourcemod-1.9.0.6245_zombieverse\public\IShareSys.h(40,10): fatal error C1083: Cannot open include file: 'sp_vm_types.h': No such file or directory (compiling source file ..\pysmod_helpers.cpp)
1>C:\Users\Dartz\Desktop\mods\source\sdk\sourcemod-1.9.0.6245_zombieverse\public\IShareSys.h(40,10): fatal error C1083: Cannot open include file: 'sp_vm_types.h': No such file or directory (compiling source file ..\pysmod.cpp)
1>    0 Warning(s)
1>    8 Error(s)
1>
1>Time Elapsed 00:00:00.71
========== Rebuild All: 0 succeeded, 1 failed, 0 skipped ==========
```

In SourceMod 1.7.2, this file (`sp_vm_types.h`) is located at `public/sourcepawn`. However, this `sourcepawn` folder does not exists anymore in newer versions of SM. So, in order to fix this error, just copy it from SourceMod 1.7.2 to SourceMod 1.9.0.

After that, the compilation will work fine.


### I receive the following error when compiling the extension: `Cannot open include file: 'IExtensionSys.h': No such file or directory`

```
1>Build FAILED.
1>
1>cl : command line warning D9035: option 'Gm' has been deprecated and will be removed in a future release
1>C:\Users\Dartz\Desktop\mods\source\sourcemod-extensions\sm19_sample_ext\sdk\smsdk_ext.h(41,10): fatal error C1083: Cannot open include file: 'IExtensionSys.h': No such file or directory
1>C:\Users\Dartz\Desktop\mods\source\sourcemod-extensions\sm19_sample_ext\sdk\smsdk_ext.h(41,10): fatal error C1083: Cannot open include file: 'IExtensionSys.h': No such file or directory
1>    1 Warning(s)
1>    2 Error(s)
1>
1>Time Elapsed 00:00:00.16
========== Rebuild All: 0 succeeded, 1 failed, 0 skipped ==========
```

Make sure you have selected the correct `Solution Configuration` in the toolbar (a combo box field located right below `Build` and `Debug` menus).
