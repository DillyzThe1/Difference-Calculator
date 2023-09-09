# Difference Calculator
A small C program to distinguish two folders from another on Windows.

# Features
This program can tell you the difference between two folders.<br>
If something exists in directory 1 that doesn't exist in directory 2, it reports that the file was `ADDED`.<br>
If something exists in directory 2, that doesn't exist in direcotry 1, it reports that the file was `REMOVED`.<br>
If the file exists in both directories but is not the same, it reports that there was a `HASH MISMATCH`.<br>
If the file is the same in both directories, it is ignored.

Example `diff.txt` output:
```
Difference Calculator Report
https://github.com/DillyzThe1/Difference-Calculator/


HASH MISMATCH - f1/BgmImage_10.png & f2/BgmImage_10.png
ADDED - f1/BgmImage_37.png
ADDED - f1/exists/mario.txt
ADDED - f1/exists/serious stuff
REMOVED - f2/BgmImage_39.png
REMOVED - f2/exist/hbnawf.txt
REMOVED - f2/exist/toy store
```

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
