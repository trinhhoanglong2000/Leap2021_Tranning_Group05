@echo off

call config.bat

cocos compile -s .\%PROJECT_NAME% -p win32 -m release -o .\%PROJECT_NAME%\bin --vs 2017

pause