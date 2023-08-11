@ECHO OFF

SET scriptPath=%~dp0
IF NOT "%~1" == "" CALL %scriptPath%\init.bat %1

link.exe ^
    /LIBPATH:"%pythonHome%\libs" ^
    /LIBPATH:"%hl2SdkPath%\lib\public" ^
    "%hl2SdkPath%\lib\public\tier0.lib" ^
    "%hl2SdkPath%\lib\public\tier1.lib" ^
    "%hl2SdkPath%\lib\public\vstdlib.lib" ^
    legacy_stdio_definitions.lib ^
    kernel32.lib ^
    user32.lib ^
    gdi32.lib ^
    winspool.lib ^
    comdlg32.lib ^
    advapi32.lib ^
    shell32.lib ^
    ole32.lib ^
    oleaut32.lib ^
    uuid.lib ^
    odbc32.lib ^
    odbccp32.lib ^
    /NODEFAULTLIB:LIBC ^
    /NODEFAULTLIB:LIBCD ^
    /NODEFAULTLIB:LIBCMTD ^
    /MANIFEST ^
    /DEBUG ^
    /PDB:"%buildPath%\%targetName%.pdb" ^
    /DLL ^
    /INCREMENTAL:NO ^
    /SUBSYSTEM:WINDOWS ^
    /OPT:REF ^
    /OPT:ICF ^
    /DYNAMICBASE:NO ^
    /MACHINE:X86 ^
    /ERRORREPORT:PROMPT ^
    /NOLOGO ^
    /manifest:embed ^
    /LTCG:incremental ^
    /TLBID:1 ^
    /SAFESEH ^
    /MANIFESTUAC:"level='asInvoker' uiAccess='false'" ^
    /LTCGOUT:"%buildPath%\%targetName%.iobj" ^
    /IMPLIB:"%buildPath%\%targetName%.lib" ^
    /OUT:"%buildPath%\%targetName%.dll" ^
    "%buildPath%\*.obj"
