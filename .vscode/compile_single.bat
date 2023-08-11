@ECHO OFF

@REM Parameters %1 and %2 are required
IF "%~1" == "" GOTO :show_usage
IF "%~2" == "" GOTO :show_usage
GOTO :parameters_supplied

:show_usage

ECHO Usage:
ECHO     compile_single.bat "Some Configuration Name" "c:\absolute\path\to\some\source_file.cpp"
ECHO.
ECHO     Example: compile_single.bat "Release - Left 4 Dead" "C:\Users\Dartz\Desktop\mods\source\extensions\pysmod\extension.cpp"
ECHO.
ECHO     NOTE: See the .vscode\configurations directory for a list of configuration scripts
ECHO.

@REM Terminate this script and its parents (if any)
EXIT

@REM Terminate only this script
@REM EXIT /b

:parameters_supplied

SET scriptPath=%~dp0
CALL %scriptPath%\init.bat %1
SET sourceFile=%2

cl.exe ^
    /c ^
    /I"%workspaceFolder%" ^
    /I"%workspaceFolder%\sdk" ^
    /I"%pythonHome%\include" ^
    /I"%smSdkPath%\public" ^
    /I"%smSdkPath%\public\sourcepawn" ^
    /I"%smSdkPath%\public\extensions" ^
    /I"%smSdkPath%\public\amtl" ^
    /I"%mmSdkPath%\core" ^
    /I"%mmSdkPath%\core\sourcehook" ^
    /I"%hl2SdkPath%\public" ^
    /I"%hl2SdkPath%\public\vstdlib" ^
    /I"%hl2SdkPath%\public\engine" ^
    /I"%hl2SdkPath%\public\tier0" ^
    /I"%hl2SdkPath%\public\tier1" ^
    /I"%hl2SdkPath%\public\game\server" ^
    /I"%hl2SdkPath%\game\shared" ^
    /Zi ^
    /W3 ^
    /Ot ^
    /MT ^
    /GR- ^
    /nologo ^
    /WX- ^
    /diagnostics:column ^
    /O2 ^
    /Oy- ^
    /GL ^
    /Gm- ^
    /GS ^
    /fp:precise ^
    /Zc:wchar_t ^
    /Zc:forScope ^
    /Zc:inline ^
    /analyze- ^
    /FC ^
    /errorReport:prompt ^
    /external:env:EXTERNAL_INCLUDE ^
    /external:W3 ^
    /Gd ^
    /Fo"%workspaceFolder%\\%buildDir%\\" ^
    /Fd"%workspaceFolder%\\%buildDir%\\vc142.pdb" ^
    /EHsc ^
    /TP ^
    /D WIN32 ^
    /D NDEBUG ^
    /D _WINDOWS ^
    /D _USRDLL ^
    /D SDK_EXPORTS ^
    /D _CRT_SECURE_NO_DEPRECATE ^
    /D SOURCEMOD_BUILD ^
    /D _WINDLL ^
    /D _MBCS ^
    /D SOURCE_ENGINE=%sourceEngine% ^
    /MP ^
    /D SE_EPISODEONE=1 ^
    /D SE_DARKMESSIAH=2 ^
    /D SE_ORANGEBOX=3 ^
    /D SE_BLOODYGOODTIME=4 ^
    /D SE_EYE=5 ^
    /D SE_CSS=6 ^
    /D SE_HL2DM=7 ^
    /D SE_DODS=8 ^
    /D SE_TF2=9 ^
    /D SE_LEFT4DEAD=10 ^
    /D SE_NUCLEARDAWN=11 ^
    /D SE_LEFT4DEAD2=12 ^
    /D SE_ALIENSWARM=13 ^
    /D SE_PORTAL2=14 ^
    /D SE_CSGO=15 ^
    /D SE_DOTA=16 ^
    "%sourceFile%"
