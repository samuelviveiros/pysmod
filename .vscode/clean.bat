@ECHO OFF

SET scriptPath=%~dp0

IF NOT "%~1" == "" CALL %scriptPath%\init.bat %1

IF NOT EXIST "%buildPath%" EXIT /b

DEL ^
    /F /S /Q ^
    "%buildPath%\*.obj" ^
    "%buildPath%\*.lib" ^
    "%buildPath%\*.dll" ^
    "%buildPath%\*.exp" ^
    "%buildPath%\*.pdb" ^
    "%buildPath%\*.iobj" ^
    "%buildPath%\*.ipdb"
