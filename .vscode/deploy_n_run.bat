@ECHO OFF

SET scriptPath=%~dp0

IF NOT "%~1" == "" CALL %scriptPath%\init.bat %1

CALL %scriptPath%\deploy.bat

ECHO [*] Running game...
CALL %scriptPath%\run.bat
ECHO.
