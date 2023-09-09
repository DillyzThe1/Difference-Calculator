# Difference Calculator
A small C program to distinguish two folders from another on Windows.

# Usage
Double click the EXE, then type your original folder's path and the path of the folder that differs from it.<br>
Open the diff.txt file that gets thrown out.<br>
That's it. That's all it does.

# Building
You need [MinGW](https://sourceforge.net/projects/mingw/).<nr>
After that, simply type `gcc diffcalc.c -o diffcalc.exe`.

# Credits
Programmed by DillyzThe1.<br>
<br>
Sourced code:
- https://stackoverflow.com/questions/4204666/how-to-list-files-in-a-directory-in-a-c-program
- https://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c
- https://learn.microsoft.com/en-us/windows/win32/seccrypto/example-c-program--creating-an-md-5-hash-from-file-content
