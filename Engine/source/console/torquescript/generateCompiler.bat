
call bison.bat CMD CMDgram.c CMDgram.y . CMDgram.cpp
..\..\..\bin\bison-flex\win_flex -PCMD -oCMDscan.cpp CMDscan.l
