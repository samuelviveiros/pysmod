@ECHO OFF

SET scriptPath=%~dp0

IF NOT "%~1" == "" CALL %scriptPath%\init.bat %1

ECHO [*] Copying...
CALL %scriptPath%\copy.bat
ECHO.

ECHO [*] Generating autoload file...
CALL %scriptPath%\autoload.bat
ECHO.
