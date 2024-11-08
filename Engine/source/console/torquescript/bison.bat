echo Changing to %4 ...
cd %4
echo Generating %2 and %3 with prefix %1.
..\..\..\bin\bison-flex\win_bison.exe -o %2 %3 --defines -p %1 -H
echo Renaming %2 to %5 .
move /Y %2 %5