output\obj\subproj.o: ..\..\source\subprojtest\subproj.c \
 ..\..\source\subprojtest\subproj.h

:cmdList=ccv850 -c  -MD -I..\..\device -IC:\Users\nikhil.patil\Documents\renesas\RH850_F1L_sample\source\test5 -IC:\Users\nikhil.patil\Documents\renesas\RH850_F1L_sample\source\subprojtest -G -object_dir=output\obj -list -list_dir=output/list -passsource -bsp generic -fsoft -cpu=rh850g3k -D__GHS__ -dwarf2 -large_sda -sda -filetype.c ..\..\source\subprojtest\subproj.c -o output\obj\subproj.o ; 
:cmdHash=0x86b206a0

:installDir=c:\ghs\comp_201517
:installDirHash=0x9d4d044c
