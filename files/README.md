## File processing 

Use `#include <fstream>`
<b>ifstream and ofstream</b> are input and output file objects 
<b>istream and ostream</b> are input and output stream objects, which include files and keyboard i/o 

Always check if a file has opened successfully before attempting to read/write. 
When an object like `ifstream in_file` is declared, `in_file` is a boolean if connection is successful/not.
- `in_file.open("in.txt")` = input/output file open command
- `while(!in_file)` = while file connection failed 
- `in_file.clear()` = no longer necessary, but still recommended—clear file after failed open attempt

Always close file after using so it can be used for other purposes/by other programs.
- `in_file.close()`

Can't read + write a file at the same time. Typical flow: 
1. Read in file contents + keep in a temporary storage buffer. 
2. Alter contents in storage buffer from user updates.
3. Write out the changed contents of the storage buffer, overwriting the old copy.
(Like opening a Word doc > editing > saving, or opening a Git branch > editing > committing) 

### input files 
Reading input from files. 
- `cin >> in_file` = reads until any whitespace (key space, tab, new line)
- `getline(in_file, str)` = reads entire line until new line 
- `infile.get() == ch` = reads next char, including white spaces 
- `in_file.ignore(9999, \n)` = skips next 9,999 characters OR all chars until new line (whichever comes first)
- `in_file.seekg(0)` = move forwards (positive int param) or backwards (negative int). 0 moves to the beginning. 


### output files
Writing output to files:
- `out_file.open("out.txt")` = for output files, it overwrites existing file or creates new file if none exists 
- `out_file.open("out.txt", ios::app)` = append any new output to existing contents, instead of writing over 