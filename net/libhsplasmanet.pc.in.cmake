prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}
includedir=${prefix}/include
libdir=${exec_prefix}/lib

Name: libhsplasmanet
Description: The libHSPlasma networking library.
Version: 0.1
Requires: libhsplasma >= 0.1
Cflags: -I${includedir}/HSPlasmaNet
Libs: -L${libdir} -lHSPlasmaNet