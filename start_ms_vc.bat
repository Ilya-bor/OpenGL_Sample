@echo off

rem Define path to project file
set "PRJFILE=%~dp0\Smaple.sln"
rem Define path to OpenGL.dll
set "PATH=%PATH%;%~dp0\Needed\dlls needed"

set "DevEnvDir=%VS100COMNTOOLS%..\IDE"

rem Launch Visual Studio
if exist "%DevEnvDir%\devenv.exe"  (
  start "" "%DevEnvDir%\devenv.exe" "%PRJFILE%"
) else (
  echo Error: Could not find MS Visual Studio ^(%VCVER%^)
  echo Check relevant environment variable ^(e.g. VS80COMNTOOLS for vc8^)
)
