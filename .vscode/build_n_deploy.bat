@ECHO OFF

SET scriptPath=%~dp0
IF NOT "%~1" == "" CALL %scriptPath%\init.bat %1 --show-info

CALL %scriptPath%\build.bat
CALL %scriptPath%\deploy.bat
