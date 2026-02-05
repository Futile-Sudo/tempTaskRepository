Temporary repository for a test assignment. Convert from ASCII HEX to BIN and vice versa.

-a Convert ASCII HEX to BIN;<br>
-b Convert BIN to ASCII HEX;<br>
-h Show help info

Build:


gcc -c converter.c -o converter.o  
gcc -c main.c -o main.o  
gcc main.o converter.o -o prog
