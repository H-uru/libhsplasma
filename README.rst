libHSPlasma, the universal Plasma Game Engine library!

Building
--------

libHSPlasma uses the CMake build system, which can generate project files
for all major operating systems.

A typical build looks something like this::

$ mkdir build
$ cd ./build
$ cmake ..

To build with Python support run this cmake command::

$ cmake -DDISABLE_PYTHON=OFF ..

On Unix-like systems (Linux, MacOSX) you should then be able to
$ make
$ sudo make install

On Windows, make sure you have the required libraries as well as
Visual Studio (Express Edition works fine), and then use the generated
.sln files to compile.  Note that building the prerequisites on Win64 can
be a bit of a pain, so I've included some hints below for this...
Of course, you can always just stick to Win32 compilation, which works
on Win64 (x86_64) installations too ;)

Mac users can also generate XCode project files for libHSPlasma as follows
$ cmake -G XCode ..

Note that IA64, PowerPC, etc. compilations *may* work, but are completely
unsupported for now.


Prerequisites
-------------

libHSPlasma depends on the following libraries; you'll need to have the dev
packages installed in order for libHSPlasma to compile successfully:

* zlib                     http://www.zlib.net/
* libJpeg                  http://www.ijg.org/
* OpenSSL                  http://www.openssl.org/
* Python 2.4+ or 3.0+      http://www.python.org/

You will also need a C++ compiler with at least some C++11 support.
The following compilers are currently known to work:

* GCC 4.4 or later
* Clang 3.0 or later
* Microsoft Visual C++ 2010 or later (2008 is no longer supported)


Win32/64 Special Considerations
----------------------------

OpenSSL:
    OpenSSL is a bit of a pain on Windows.  You'll need ActivePerl (either the
    32-bit or 64-bit version should work fine), and then you'll need to do
    some makefile editing.  Also, you can only use the static version as of
    this writing.  (The version I release uses the static libssl for both the
    Win32 and Win64 builds).  If you want to build both the Win32 and Win64
    versions, you must create a separate build dir (or do more makefile editing
    which isn't covered here).

    To build on Win64, here are the steps I use (in a command prompt):
    > perl Configure VC-WIN64A no-shared no-idea
    > ms\do_win64a
    Open ms\nt.mak and remove bufferoverflowu.lib from EX_LIBS
    > nmake -f ms\nt.mak

    Note also that to actually use it on either Win32 or Win64, the "include"
    directory is actually misleading, and only contains empty files.  You'll
    want to point VS to your inc32 dir for includes, and your out32 (or
    out32dll if you built DLLs) dir for libraries.

Python:
    Python is pretty straightforward if you only create release builds.  The
    default Windows installations come with the necessary header and lib files,
    so you just need to point VS to those.  Building Debug builds against
    Python, however, requires that you get the actual source packages from
    python.org and compile them yourself.
