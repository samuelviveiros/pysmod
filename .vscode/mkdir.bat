@ECHO OFF

SET scriptPath=%~dp0

IF NOT "%~1" == "" CALL %scriptPath%\init.bat %1

IF NOT EXIST "%buildPath%" (
    ECHO [*] Creating build directory...
    ECHO "%buildPath%"
    MKDIR "%buildPath%"
    ECHO.
)
