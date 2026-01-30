SET GBDK=..\..\..\gbdk\bin\

%GBDK%lcc -c -o gbt_player.o gbt_player.s
%GBDK%sdar q gbt_player.lib gbt_player.o 
del /Q *.o