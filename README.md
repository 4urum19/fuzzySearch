## Fuzzy directory search script
Searches through a given directory and returns a list of directories which match a given glob. Wildcards like
** are allowed.

Includes a script to add automatic switch function to the bashrc file. 

## Instructions
1. make
2. cp fuzzySearch /usr/local/bin
3. ./add_fuzzy_cd FUNC_NAME DIR
4. source ~/.bashrc 
5. FUNC_NAME GLOB

## FAQ
- Why in CPP?
I wanted to play with the filesystem abstraction interface.
- Is it good? 
No, it works on my machine though
