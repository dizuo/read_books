http://cetus.sakura.ne.jp/softlab/b2p-home/

png2bmp, a PNG-to-BMP converter - version 1.62 (Sep 4, 2005)
   Copyright (C) 1999-2005 MIYASAKA Masaru
   Compiled with libpng 1.2.8 and zlib 1.2.3.

Usage: png2bmp.exe [-switches] inputfile(s) ...
   or: ... | png2bmp.exe [-switches] | ...

List of input files may use wildcards (* and ?)
Output filename is same as input filename, but extension .bmp

Switches (case-insensitive) :
   -A       Preserve alpha channel (save in 32bit ARGB BMP format)
   -B       Preserve alpha channel (save in 32bit Bitfield BMP format)
   -R       Convert transparent color to alpha channel (use with -A or -B)
   -O name  Specify name for output file
   -D dir   Output files into dir
   -E       Delete input files after successful conversion
   -T       Set the timestamp of input file on output file
   -Q       Quiet mode
   -L       Log errors to .\P2BERROR.LOG file
   -X       Disable conversion through standard input/output

E:\>PNG2BMP.EXE -a -r location_radius_anim.png
OK      location_radiu o
