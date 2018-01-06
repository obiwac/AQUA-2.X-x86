# AQUA-2.X-x86
This is the repository for the AQUA 2.X x86 kernel

# How to run (linux)

First, download this repository with
`git clone https://github.com/obiwac/AQUA-2.X-x86`
`cd AQUA-2.X-x86`

Then, build it with
`make`

For this step, you will need a gcc cross compiler setup for i686-elf. See http://wiki.osdev.org/GCC_Cross-Compiler for instructions on how to set one up. If not already done,
`export PATH="/home/<username>/opt/cross/bin:$PATH"`

Then you can setup your Virtual Box vm or what not with the aqua.iso in aqua/.
