@ECHO OFF

SET scriptPath=%~dp0

IF NOT "%~1" == "" CALL %scriptPath%\init.bat %1

%game% -console -toconsole -dev -insecure +map %map%
