#include <Python.h>
#include <ResManager/plFactory.h>
#include "../PRP/pyCreatable.h"

extern "C" {

static PyObject* pyFactory_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plFactory cannot be constructed");
    return NULL;
}

static PyObject* pyFactory_Create(PyObject*, PyObject* args) {
    int classIdx, version = pvUnknown;
    const char* className;

    if (PyArg_ParseTuple(args, "i|i", &classIdx, &version)) {
        plCreatable* pCre = NULL;
        if (version == pvUnknown)
            pCre = plFactory::Create(classIdx);
        else
            pCre = plFactory::Create(classIdx, (PlasmaVer)version);
        return pyCreatable_FromCreatable(pCre);
    } else if (PyArg_ParseTuple(args, "s", className)) {
        PyErr_Clear();
        plCreatable* pCre = plFactory::Create(className);
        return pyCreatable_FromCreatable(pCre);
    } else {
        PyErr_SetString(PyExc_TypeError, "Create expects int, int OR string");
        return NULL;
    }
}

static PyObject* pyFactory_ClassName(PyObject*, PyObject* args) {
    int classIdx, version = pvUnknown;

    if (!PyArg_ParseTuple(args, "i|i", &classIdx, &version)) {
        PyErr_SetString(PyExc_TypeError, "ClassName expects int, int");
        return NULL;
    }
    if (version == pvUnknown)
        return PyString_FromString(plFactory::ClassName(classIdx));
    else
        return PyString_FromString(plFactory::ClassName(classIdx, (PlasmaVer)version));
}

static PyObject* pyFactory_ClassIndex(PyObject*, PyObject* args) {
    const char* className;

    if (!PyArg_ParseTuple(args, "s", &className)) {
        PyErr_SetString(PyExc_TypeError, "ClassIndex expects a string");
        return NULL;
    }
    return PyInt_FromLong(plFactory::ClassIndex(className));
}

static PyObject* pyFactory_ClassVersion(PyObject*, PyObject* args) {
    int classIdx, version;

    if (!PyArg_ParseTuple(args, "ii", &classIdx, &version)) {
        PyErr_SetString(PyExc_TypeError, "ClassVersion expects int, int");
        return NULL;
    }
    return PyInt_FromLong(plFactory::ClassVersion(classIdx, (PlasmaVer)version));
}

static PyMethodDef pyFactory_Methods[] = {
    { "Create", (PyCFunction)pyFactory_Create, METH_STATIC | METH_VARARGS,
      "Params: classIdx, [version]\n"
      "Params: className\n"
      "Create a new instance of the specified class\n"
      "If `version` is specified, the classIdx is looked up for\n"
      "that version (otherwise the global mapping is used)" },
    { "ClassName", (PyCFunction)pyFactory_ClassName, METH_STATIC | METH_VARARGS,
      "Params: classIdx, [version]\n"
      "Get the name of the specified class\n"
      "If `version` is specified, the classIdx is looked up for\n"
      "that version (otherwise the global mapping is used)" },
    { "ClassIndex", (PyCFunction)pyFactory_ClassIndex, METH_STATIC | METH_VARARGS,
      "Params: className\n"
      "Returns the global ClassIndex for the specified class" },
    { "ClassVersion", (PyCFunction)pyFactory_ClassVersion, METH_STATIC | METH_VARARGS,
      "Params: classIdx, version\n"
      "Returns the Class Version of the specified class" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyFactory_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plFactory",               /* tp_name */
    0,                                  /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "Creatable Factory",                /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyFactory_Methods,                  /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyFactory_new,                      /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

void AddCreatableType(PyObject* dict, unsigned short classIdx) {
    PyDict_SetItemString(dict, plFactory::ClassName(classIdx),
                         PyInt_FromLong(classIdx));
}

PyObject* Init_pyFactory_Type() {
    if (PyType_Ready(&pyFactory_Type) < 0)
        return NULL;

    for (size_t i=kSceneNode; i<=kCameraBrain_Flight; i++)
        AddCreatableType(pyFactory_Type.tp_dict, i);
    for (size_t i=kObjRefMsg; i<=kAvTaskOneShot; i++)
        AddCreatableType(pyFactory_Type.tp_dict, i);
    for (size_t i=kVaultGameServerInitializationTask; i<=kAvBrainRideAnimatedPhysical; i++)
        AddCreatableType(pyFactory_Type.tp_dict, i);

    Py_INCREF(&pyFactory_Type);
    return (PyObject*)&pyFactory_Type;
}

}
