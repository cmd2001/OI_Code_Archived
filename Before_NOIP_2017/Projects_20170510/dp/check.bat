@echo off
set t=0
:loop
	set /a t=t+1
	make.exe
	echo start_my
	my.exe
	echo end_my
	yousiki.exe
	fc my.out yousiki.out
	echo %t%
if not errorlevel 1 goto loop
pause
goto loop
