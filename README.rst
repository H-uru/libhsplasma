libHSPlasma, the universal Plasma Game Engine library!
======================================================

Building
--------

libHSPlasma uses the CMake build system, which can generate project files
for all major operating systems.

A typical build looks something like this::

$ mkdir build
$ cd ./build
$ cmake ..

On Unix-like systems (Linux, MacOSX) you should then be able to::

$ make
$ sudo make install

On Windows, make sure you have the required libraries as well as Visual
Studio (Express Edition works fine), and then use the generated .sln files
to compile.

Mac users can also generate XCode project files for libHSPlasma by
specifying the XCode generator::

$ cmake -G XCode ..

Note that ARM, PowerPC, etc. compilations *may* work, but are completely
unsupported for now.


Prerequisites
-------------

libHSPlasma depends on the following libraries; you'll need to have the dev
packages installed in order for libHSPlasma to compile successfully:

- `zlib <http://www.zlib.net/>`_
- `libjpeg-turbo <http://libjpeg-turbo.virtualgl.org/>`_
- `OpenSSL 1.0+ <http://www.openssl.org/>`_
- `Python 2.4+ or 3.0+ <http://www.python.org/>`_

You will also need a C++ compiler with at least some C++11 support.
The following compiler versions are currently supported (others may work,
but are currently untested):

- GCC 4.6 or later
- Clang 3.0 or later
- Microsoft Visual C++ 2010 or later


Win32/64 Special Considerations
-------------------------------

Python:
    Python is pretty straightforward if you only create release builds.  The
    default Windows installations come with the necessary header and lib files,
    so you just need to point VS to those.  Building Debug builds against
    Python, however, requires that you get the actual source packages from
    python.org and compile them yourself.
