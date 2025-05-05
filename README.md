Made for a friend because their mouse kept leaving the window making them tab out. (Yes the game is brawlhalla)  
```console
Usage: WindowTitle X Y
```
You can create a bat file to make it easier to run something like this should work:
```console
@echo off
setlocal

set WINDOW_TITLE=Notepad
set X_COORD=300
set Y_COORD=200

:: Run the EXE from the same directory as this script
GameCursorLock.exe "%WINDOW_TITLE%" %X_COORD% %Y_COORD%

pause
endlocal
```
