@echo off
title 更改文件名大写为小写
set dir=%~dp0&call:cdto
for /f "delims=" %%i in ('dir/s/b/ad') do set dir=%%i&call:cdto
pause
exit/b
:cdto
cd /d %dir%
for /f "delims=" %%i in ('dir/b/a-d/l') do ren "%%i" "%%i"