pushd %~dp0
@echo off
xextool.exe -o decrypted_xbLive.xex -e -u -c -u "ENGINE.BO2.xex"
TIMEOUT /T 2 /NOBREAK
start StringEncryption.exe
TIMEOUT /T 2 /NOBREAK
start xbLiveFuscate.exe
TIMEOUT /T 2 /NOBREAK
sextool-bo2.exe -m -r -o "ENGINE.BO2.OBF.xex" -e -e -c -c output.xex
TIMEOUT /T 2 /NOBREAK
del /S decrypted_xbLive.xex
del /S output.xex
del /S rc4_key_dec.bin
del /S text.bin
TIMEOUT /T 2 /NOBREAK