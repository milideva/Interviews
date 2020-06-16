#include <stdio.h>

struct s_tag {
    char c;
    double d;
    int i;
};

int main () {
    struct s_tag s;
    printf("sizeof struct:%d\n", sizeof(s));
    return 0;
}

/*

Alignment in general is unspecified in C99 and implementation-defined
in C11 where the _Alignof and _Alignas operators can be used to query
and increase the alignment of types and objects.

Alignment of struct members is implementation-defined in both. In C99,
the section that discusses the subject is 6.7.2.1 Structure and union
specifiers, specifically paragraph 12 which reads:

   Each non-bit-field member of a structure or union object is aligned
   in an implementation-defined manner appropriate to its type.

On a 64-bit machine
====================
~>gcc -ansi=c99 sizeof_struct.c
~>a.out
sizeof struct:24
~>gcc --v
Reading specs from /usr/lib/gcc/x86_64-redhat-linux/3.4.6/specs
Configured with: ../configure --prefix=/usr --mandir=/usr/share/man --infodir=/usr/share/info --enable-shared --enable-threads=posix --disable-checking --with-system-zlib --enable-__cxa_atexit --disable-libunwind-exceptions --enable-java-awt=gtk --host=x86_64-redhat-linux
Thread model: posix
gcc version 3.4.6 20060404 (Red Hat 3.4.6-11)
~>uname -a
Linux sjc-ads-2122 2.6.9-89.0.11.ELlargesmp #1 SMP Mon Aug 31 11:05:24 EDT 2009 x86_64 x86_64 x86_64 GNU/Linux
~> 


On a 32-bit machine :
=====================
~>gcc sizeof_struct.c 
~>a.out
sizeof struct:16 <-------------------------
~>uname -a
Linux dsbu-lnx15 2.6.18-194.8.1.el5 #1 SMP Wed Jun 23 10:58:38 EDT 2010 i686 i686 i386 GNU/Linux
~>gcc -v
Using built-in specs.
Target: i386-redhat-linux
Configured with: ../configure --prefix=/usr --mandir=/usr/share/man --infodir=/usr/share/info --enable-shared --enable-threads=posix --enable-checking=release --with-system-zlib --enable-__cxa_atexit --disable-libunwind-exceptions --enable-libgcj-multifile --enable-languages=c,c++,objc,obj-c++,java,fortran,ada --enable-java-awt=gtk --disable-dssi --enable-plugin --with-java-home=/usr/lib/jvm/java-1.4.2-gcj-1.4.2.0/jre --with-cpu=generic --host=i386-redhat-linux
Thread model: posix
gcc version 4.1.2 20080704 (Red Hat 4.1.2-48)
~>hostname
dsbu-lnx15
~>



There's a difference between the i386 and x86_64 ABIs in the alignment
of the types double and long long. i386 aligns both on a 4 byte boundary
while x86_64 on an 8 byte boundary. The different alignment calls for
different amounts of padding between struct members and results in
different sizes of the structs. In GCC, -malign-double option can be
used to change the alignment. It's off for i386 and on for x86_64.

You can find the ABIs at the following links:

   http://www.sco.com/developers/devspecs/abi386-4.pdf
   http://www.x86-64.org/documentation/abi.pdf

and the GCC option in the latest manual here:

http://gcc.gnu.org/onlinedocs/gcc/i386-and-x86-64-Options.html#index-malign-double-1630

*/
