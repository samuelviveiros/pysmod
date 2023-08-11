@ECHO OFF

SET scriptPath=%~dp0

IF NOT "%~1" == "" CALL %scriptPath%\init.bat %1

IF NOT EXIST "%deployPath%" EXIT /b

DEL /F /S /Q "%deployPath%\%targetName%.dll"
DEL /F /S /Q "%deployPath%\%extensionBasename%.autoload"
