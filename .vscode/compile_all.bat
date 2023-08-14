@ECHO OFF

SET scriptPath=%~dp0
IF NOT "%~1" == "" CALL %scriptPath%\init.bat %1

CALL %scriptPath%\sources.bat

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
    /D SE_SDK2013=16 ^
    /D SE_BMS=17 ^
    /D SE_BLADE=18 ^
    /D SE_INSURGENCY=19 ^
    /D SE_DOI=20 ^
    /D SE_CONTAGION=21 ^
    %sourceFiles%
