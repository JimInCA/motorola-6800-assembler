# Motorola 6800 Assembler

This repository contains the source code to build the Motorola Cross Assembler for their 6800 family of 8bit processors.  This code was originally published in 1984 and then ported to the IBM PC and republished in 1987.  I want to give full credit to those you developed this code and my full respect for their work.

My intent is to keep the source code as close to the original as possible.  The original source code was written in pre-ANSI C, so it required some editing to bring it up the ANSI C standard.  It was also designed to have one main c file that included the correct *.h and *.c files to build the assemblers for the different processors in the 6800 family.  I updated this to build each module into its own object file and then directed the linker to include the appropriate object files for the different processors.  I also added a directory structure where the source code is kept in the ./src directory, object files are placed in the ./obj directory, and binary files are place in the ./bin directory.

The code was ported to Linux and builds using the gcc compiler.

This module will build the following binaries for the specified Motorola processors:

- as0   6800/6802 processors
- as1   6801 processor
- as4   6804 processor
- as5   6805 processor
- as9   6809 processor
- as11  68HC11 processor


## Compiling The Source Code

All you need to do to compile the assemblers is to go to the main directly for this repository and run make as in the example below.
```
cd /<path>/motorola-6800-assembler
make all
```
You can also build individual assemblers with statements similar to the following:
```
make as0
```
This will build just the 6800/6802 assembler.

You can enter the following command to remove all derived objects:
```
make clean
```
And you can remove all derived objects, binaries, and added directories with the following command:
```
make realclean
```

## Testing Your Binary

I've included a few programs written using the Motorola 6800 syntax.  The programs are examples from the MEK6802D5 Microcomputer Evaluation Board User's Manual.  The code is almost identical to the book with the exception of the opt pre-assembler directive and the addition of a few comments of mine.  These programs are included in the ./test directory and can be used to verify the functionality of the assembler binaries.  A simple procedure follows that you can use to test the assemblers:
```
cd ./test
../bin/as0 used5.asm -l cre c s
```
Using the above command, the output to the terminal window from the as0 assembler should look this:
```
<system>:~/motorola-6800-assembler/test$ ../bin/as0 used5.asm -l cre c s
0001                               *
0002                               *	    Copied from:
0003                               *	    MEK6802D5 Microcomputer Evaluation Board User's Manual
0004                               *	    Page 3-8
0005                               *
0006                               *	    Assemble with the following command:
0007                               *		as0 used5.asm -l cre c s
0008                               *
0009                                       nam     used5
0010                               *       Options set in file override command line option settings
0011                               *        opt     c       * options must be in lower case
0012 0000                                  org     $0
0013 e41d                          disbuf  equ     $e41d
0014 f0a2                          diddle  equ     $f0a2
0015 e419                          mnptr   equ     $e419
0016 f0bb                          put     equ     $f0bb
0017                               *
0018 0000 86 3e              [ 2 ] beg     ldaa    #$3e
0019 0002 b7 e4 1d           [ 5 ]         staa    disbuf
0020 0005 86 6d              [ 2 ]         ldaa    #$6d
0021 0007 b7 e4 1e           [ 5 ]         staa    disbuf+1
0022 000a 86 79              [ 2 ]         ldaa    #$79
0023 000c b7 e4 1f           [ 5 ]         staa    disbuf+2
0024 000f 86 00              [ 2 ]         ldaa    #$00
0025 0011 b7 e4 20           [ 5 ]         staa    disbuf+3
0026 0014 86 5e              [ 2 ]         ldaa    #$5e
0027 0016 b7 e4 21           [ 5 ]         staa    disbuf+4
0028 0019 86 6d              [ 2 ]         ldaa    #$6d
0029 001b b7 e4 22           [ 5 ]         staa    disbuf+5
0030 001e 86 a2              [ 2 ]         ldaa    #diddle
0031 0020 ff e4 19           [ 6 ]         stx     mnptr
0032 0023 7e f0 bb           [ 3 ]         jmp     put
0033                                       end

beg        0000
diddle     f0a2
disbuf     e41d
mnptr      e419
put        f0bb

beg        0000 *0018 
diddle     f0a2 *0014 0030 
disbuf     e41d *0013 0019 0021 0023 0025 0027 0029 
mnptr      e419 *0015 0031 
put        f0bb *0016 0032 
```

The as0 assembler produces the S-recored output file used5.s19.  This file is written to the ./test directory.  A listing the test directory should look like this:

```
<system>:~/motorola-6800-assembler/test$ ls -al
total 20
drwxrwxr-x 2 jim jim 4096 May 29 07:53 .
drwxrwxr-x 8 jim jim 4096 May 29 07:53 ..
-rw-rw-r-- 1 jim jim  657 May 26 18:56 help.asm
-rw-rw-r-- 1 jim jim  778 May 26 18:56 used5.asm
-rw-rw-r-- 1 jim jim  109 May 29 07:53 used5.s19
```

## Documentation

I've included to files in the ./documentation directory.  File `assembler.txt` is the original documentation included with the sources for the assemblers.  The other file, `motorola_cross_asm_manual.pdf` is a manual for the Motorola assemblers that was published in 1990.  This information in this second file is not absolutely consistent with the assemblers used here, but is seems to be close and is a much more complete document than the text file.  So use at your own discretion.

That's it for now...

