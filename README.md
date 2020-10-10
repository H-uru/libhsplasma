libHSPlasma, the universal Plasma Game Engine library!
======================================================

Building
--------

libHSPlasma uses the CMake build system, which can generate project files
for all major operating systems.

A typical build looks something like this:

    $ mkdir build
    $ cd build
    $ cmake -DCMAKE_BUILD_TYPE=Release ..

On Unix-like systems (Linux, MacOSX) you should then be able to:

    $ make
    $ sudo make install

On Windows, make sure you have the required libraries as well as Visual
Studio (Express Edition works fine), and then use the generated .sln files
to compile.

Mac users can also generate XCode project files for libHSPlasma by
specifying the XCode generator:

    $ cmake -G XCode ..

Note that ARM, PowerPC, etc. compilations *may* work, but are completely
unsupported for now.


Prerequisites
-------------

libHSPlasma depends on the following libraries; you'll need to have the dev
packages installed in order for libHSPlasma to compile successfully:

- [string_theory](http://github.com/zrax/string_theory)
- [zlib](http://www.zlib.net/)
- [libjpeg-turbo](http://libjpeg-turbo.virtualgl.org/)
- [libpng](http://www.libpng.org/pub/png/libpng.html)
- [PhysX](http://www.nvidia.com/object/physx_archives.html#SDK) (Optional)

For libHSPlasmaNet

- [OpenSSL 1.0+](http://www.openssl.org/)

For PyHSPlasma

- [Python 2.6+ or 3.0+](http://www.python.org/)

You will also need CMake and a C++ compiler with at least some C++11 support.
The following compiler versions are currently supported (others may work,
but are currently untested):

- GCC 4.6 or later
- Clang 3.0 or later
- Microsoft Visual C++ 2013 or later


Using vcpkg on Windows
----------------------

When building with Microsoft Visual C++ 2015 or later, the recommended way
to get all prerequisite libraries (except for PhysX) is with
[vcpkg](https://github.com/microsoft/vcpkg). The recommended configuration
is to build everything except Python as a static library.  For now (as of
Oct. 2020), Python needs to be built as a DLL in order for PyHSPlasma to
correctly export its symbols. However, the built Python DLLs do NOT need to
be distributed with the compiled .pyd files.

To make building the prerequisites simpler, you can use the
`libhsplasma-vcpkg.cmake` file in the root of the libhsplasma source directory
as a vcpkg toolchain file:

    copy libhsplasma-vcpkg.cmake <Path to vcpkg>\triplets
    cd <Path to vcpkg>
    .\vcpkg install --triplet libhsplasma-vcpkg string-theory zlib libjpeg-turbo libpng openssl python3

(Note: use `python2` instead of `python3` when building PyHSPlasma for
Python 2.7).

Then, when configuring libhsplasma with CMake, you can just point it to your
vcpkg install directory with the custom triplet:

    mkdir build
    cd build
    cmake -DCMAKE_PREFIX_PATH=<Path to vcpkg>\installed\libhsplasma-vcpkg;<Path to vcpkg>\installed\libhsplasma-vcpkg\debug ..
