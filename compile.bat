@echo off
cl.exe  %1 user32.lib kernel32.lib gdi32.lib msimg32.lib winmm.lib greenpipe.c dglib2.obj /wd4996 /wd4716
