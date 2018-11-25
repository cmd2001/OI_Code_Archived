@echo off
set t=0
:loop
	set /a t=t+1
	make.exe
	bzoj4870
	std.exe
	fc my.txt std.out
	echo %t%
if not errorlevel 1 goto loop
pause
goto loop
