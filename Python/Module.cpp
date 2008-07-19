#include <Python.h>

#include <Util/PlasmaVersions.h>
#include <Stream/hsStream.h>
#include "Stream/pyStream.h"
#include "Util/pyUtil.h"
#include "Sys/pyColor.h"

static PyMethodDef PyPlasma_Methods[] = {
    { NULL, NULL, 0, NULL }
};

void initPyPlasma_Constants(PyObject* module) {
    /* Generic constants */
    PyModule_AddIntConstant(module, "pvUnknown", pvUnknown);
    PyModule_AddIntConstant(module, "pvPrime", pvPrime);
    PyModule_AddIntConstant(module, "pvPots", pvPots);
    PyModule_AddIntConstant(module, "pvLive", pvLive);
    PyModule_AddIntConstant(module, "pvEoa", pvEoa);
    PyModule_AddIntConstant(module, "pvHex", pvHex);

    /* File modes */
    PyModule_AddIntConstant(module, "fmRead", fmRead);
    PyModule_AddIntConstant(module, "fmWrite", fmWrite);
    PyModule_AddIntConstant(module, "fmReadWrite", fmReadWrite);
    PyModule_AddIntConstant(module, "fmCreate", fmCreate);
}

PyMODINIT_FUNC initPyPlasma() {
    PyObject* module = Py_InitModule3("PyPlasma", PyPlasma_Methods,
                                      "libPlasma Python Interface Module");
    initPyPlasma_Constants(module);

    /* Stream */
    PyModule_AddObject(module, "hsStream", Init_pyStream_Type());
    PyModule_AddObject(module, "hsFileStream", Init_pyFileStream_Type());
    PyModule_AddObject(module, "plEncryptedStream", Init_pyEncryptedStream_Type());

    /* Util */
    PyModule_AddObject(module, "hsBitVector", Init_pyBitVector_Type());

    /* pyColor */
    PyModule_AddObject(module, "hsColorRGBA", Init_pyColorRGBA_Type());
    PyModule_AddObject(module, "hsColor32", Init_pyColor32_Type());
}
