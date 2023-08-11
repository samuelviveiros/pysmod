@ECHO OFF

SET scriptPath=%~dp0
IF NOT "%~1" == "" CALL %scriptPath%\init.bat %1

ECHO [*] Cleaning...
CALL %scriptPath%\clean.bat
ECHO.

ECHO [*] Compiling...
CALL %scriptPath%\compile_all.bat
ECHO.

ECHO [*] Linking...
CALL %scriptPath%\link.bat
ECHO.
