Motorola 6800 Assembler
===

This repository contains the source code to build the Motorola Cross Assembler for their 6800 family of 8bit processors.  This code was originally published in 1984 and then ported to the IBM PC and republished in 1987.  I want to give full credit to those you developed this code and my full respect for their work.

My intent is to keep the source code as close to the original as possible.  The original source code was written in pre-ANSI C, so it required some editing to bring it up the ANSI C standard.  It was also designed to have one main c file that included the correct *.h and *.c files to build the assemblers for the different processors in the 6800 family.  I updated this to build each module into its own object file and then directed the linker to include the appropriate object files for the different processors.  I also added a directory structure where the source code is kept in the ./src directory, object files are placed in the ./obj directory, and binary files are place in the ./bin directory.

The code was ported to Linux and builds using the gcc compiler.

This module will build the following binaries for the specified Motorola processors:

as0		6800/6802 processors

as1		6801 processor

as4		6804 processor

as5		6805 processor

as9		6809 processor

as11	68HC11 processor


Compiling The Source Code
---

All you need to do to compile the assemblers is to go to the main directly for this repository and run make as in the example below.

cd <path>/motorola-6800-assembler
make all

You can also build individual assemblers with statements similar to the following:

make as0

This will build just the 6800/6802 assembler.

You can enter the following command to remove all derived objects:

make clean

And you can remove all derived objects, binaries, and added directories with the following command:

make realclean

