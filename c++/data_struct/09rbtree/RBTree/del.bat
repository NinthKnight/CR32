@echo off
for /r %%i in (debug,release,ipch x64) do rd /s /q "%%i"
for /r %%i in (*.sdf *.VC.db) do del /s /f /q "%%i"
pause