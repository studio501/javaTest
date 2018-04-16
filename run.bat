@echo off

@rem 自动编译运行脚本

set CurrentPath=%~dp0
echo %CurrentPath%

choice /m "make your choice(gen,build,run,all,help)" /c gbrah
set option=%errorlevel%
echo option is %errorlevel%

if "%option%"=="1" (javac .\myjni\HelloWorld.java) & (javah -d include myjni.HelloWorld)
	
if "%option%"=="2" (g++ -Wl,--add-stdcall-alias -I"%JAVA_HOME%"\include -I"%JAVA_HOME%"\include\win32 -shared -o hello.dll .\src\hello.c .\helloImpl.cpp)
	
if "%option%"=="3" (java myjni.HelloWorld)

if "%option%"=="4" (javac .\myjni\HelloWorld.java) & (javah -d include myjni.HelloWorld) & (g++ -Wl,--add-stdcall-alias -I"%JAVA_HOME%"\include -I"%JAVA_HOME%"\include\win32 -shared -o hello.dll .\src\hello.c .\helloImpl.cpp) & (java myjni.HelloWorld)

if "%option%"=="5" (javap -s -p myjni.HelloWorld)

pause
