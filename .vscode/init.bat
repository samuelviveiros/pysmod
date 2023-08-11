@ECHO OFF

@REM Parameter %1 is required and must be a configuration name
IF "%~1" == "" (
    ECHO Usage:
    ECHO     init.bat "Some Configuration Name"
    ECHO.
    ECHO     Example: init.bat "Release - Left 4 Dead"
    ECHO.
    ECHO     NOTE: See the .vscode\configurations directory for a list of configuration scripts
    ECHO.

    @REM Terminate this script and its parents
    EXIT

    @REM Terminate only this script
    @REM EXIT /b
)

SET scriptPath=%~dp0

@REM LOAD GENERAL SETTINGS
CALL %scriptPath%\configurations\general_settings.bat

@REM LOAD GAME-RELATED SETTINGS
CALL %scriptPath%\configurations\%1.bat

SET buildPath=%workspaceFolder%\%buildDir%

@REM CREATE BUILD DIRECTORY IF DOESN'T EXISTS
CALL %scriptPath%\mkdir.bat

IF "%2" == "--show-info" CALL %scriptPath%\info.bat
