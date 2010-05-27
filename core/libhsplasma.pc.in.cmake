prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}
includedir=${prefix}/include
libdir=${exec_prefix}/lib

Name: libhsplasma
Description: The libHSPlasma library.
Version: 0.1
Cflags: -I${includedir}/HSPlasma
Libs: -L${libdir} -lHSPlasma
