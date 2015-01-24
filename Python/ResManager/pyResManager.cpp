/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <PyPlasma.h>
#include <ResManager/plResManager.h>
#include <PRP/KeyedObject/hsKeyedObject.h>
#include <PRP/plCreatable.h>
#include "pyResManager.h"
#include "Stream/pyStream.h"
#include "PRP/pyCreatable.h"
#include "PRP/pySceneNode.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/KeyedObject/pyKeyedObject.h"

extern "C" {

static void pyResManager_dealloc(pyResManager* self) {
    delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyResManager___init__(pyResManager* self, PyObject* args, PyObject* kwds) {
    int version = PlasmaVer::pvUnknown;
    if (!PyArg_ParseTuple(args, "|i", &version))
        return -1;

    self->fThis->setVer((PlasmaVer)version);
    return 0;
}

static PyObject* pyResManager_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyResManager* self = (pyResManager*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new plResManager();
    return (PyObject*)self;
}

static PyObject* pyResManager_setVer(pyResManager* self, PyObject* args) {
    int ver, force = 0;
    if (!PyArg_ParseTuple(args, "i|i", &ver, &force)) {
        PyErr_SetString(PyExc_TypeError, "setVer expects an int");
        return NULL;
    }
    self->fThis->setVer((PlasmaVer)ver, (force != 0));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyResManager_getVer(pyResManager* self) {
    return PyInt_FromLong(self->fThis->getVer());
}

static PyObject* pyResManager_readKey(pyResManager* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "readKey expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "readKey expects an hsStream");
        return NULL;
    }
    return pyKey_FromKey(self->fThis->readKey(stream->fThis));
}

static PyObject* pyResManager_readUoid(pyResManager* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "readUoid expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "readUoid expects an hsStream");
        return NULL;
    }
    return pyKey_FromKey(self->fThis->readUoid(stream->fThis));
}

static PyObject* pyResManager_writeKey(pyResManager* self, PyObject* args) {
    pyStream* stream;
    pyKey* key;
    if (!PyArg_ParseTuple(args, "OO", &stream, &key)) {
        PyErr_SetString(PyExc_TypeError, "writeKey expects hsStream, plKey");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream) || !pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "writeKey expects hsStream, plKey");
        return NULL;
    }
    self->fThis->writeKey(stream->fThis, *(key->fThis));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyResManager_writeUoid(pyResManager* self, PyObject* args) {
    pyStream* stream;
    pyKey* key;
    if (!PyArg_ParseTuple(args, "OO", &stream, &key)) {
        PyErr_SetString(PyExc_TypeError, "writeUoid expects hsStream, plKey");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream) || !pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "writeUoid expects hsStream, plKey");
        return NULL;
    }
    self->fThis->writeUoid(stream->fThis, *(key->fThis));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyResManager_getObject(pyResManager* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "getObject expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "getObject expects a plKey");
        return NULL;
    }
    return ICreate(dynamic_cast<plCreatable*>(self->fThis->getObject(*(key->fThis))));
}

static PyObject* pyResManager_countKeys(pyResManager* self, PyObject* args) {
    pyLocation* loc;
    if (!PyArg_ParseTuple(args, "O", &loc)) {
        PyErr_SetString(PyExc_TypeError, "countKeys expects a plLocation");
        return NULL;
    }
    if (!pyLocation_Check((PyObject*)loc)) {
        PyErr_SetString(PyExc_TypeError, "countKeys expects a plLocation");
        return NULL;
    }
    return PyInt_FromLong(self->fThis->countKeys(*(loc->fThis)));
}

static PyObject* pyResManager_ReadPage(pyResManager* self, PyObject* args) {
    const char* filename;
    int stub = false;
    if (!PyArg_ParseTuple(args, "s|i", &filename, &stub)) {
        PyErr_SetString(PyExc_TypeError, "ReadPage expects a string");
        return NULL;
    }
    plPageInfo* page = NULL;
    try {
        page = self->fThis->ReadPage(filename, (stub != 0));
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error reading page");
        return NULL;
    }
    if (page == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    } else {
        return pyPageInfo_FromPageInfo(page);
    }
}

static PyObject* pyResManager_WritePage(pyResManager* self, PyObject* args) {
    const char* filename;
    pyPageInfo* page;
    if (!PyArg_ParseTuple(args, "sO", &filename, &page)) {
        PyErr_SetString(PyExc_TypeError, "WritePage expects string, plPageInfo");
        return NULL;
    }
    if (!pyPageInfo_Check((PyObject*)page)) {
        PyErr_SetString(PyExc_TypeError, "WritePage expects string, plPageInfo");
        return NULL;
    }
    try {
        self->fThis->WritePage(filename, page->fThis);
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing page");
        return NULL;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyResManager_FindPage(pyResManager* self, PyObject* args) {
    pyLocation* loc;
    if (!PyArg_ParseTuple(args, "O", &loc)) {
        PyErr_SetString(PyExc_TypeError, "FindPage expects a plLocation");
        return NULL;
    }
    if (!pyLocation_Check((PyObject*)loc)) {
        PyErr_SetString(PyExc_TypeError, "FindPage expects a plLocation");
        return NULL;
    }
    plPageInfo* page = self->fThis->FindPage(*loc->fThis);
    if (page == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    } else {
        return pyPageInfo_FromPageInfo(page);
    }
}

static PyObject* pyResManager_UnloadPage(pyResManager* self, PyObject* args) {
    pyLocation* loc;
    if (!PyArg_ParseTuple(args, "O", &loc)) {
        PyErr_SetString(PyExc_TypeError, "UnloadPage expects a plLocation");
        return NULL;
    }
    if (!pyLocation_Check((PyObject*)loc)) {
        PyErr_SetString(PyExc_TypeError, "UnloadPage expects a plLocation");
        return NULL;
    }
    self->fThis->UnloadPage(*loc->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyResManager_ReadAge(pyResManager* self, PyObject* args) {
    const char* filename;
    char readPages;
    if (!PyArg_ParseTuple(args, "sb", &filename, &readPages)) {
        PyErr_SetString(PyExc_TypeError, "ReadAge expects string, bool");
        return NULL;
    }
    plAgeInfo* age = NULL;
    try {
        age = self->fThis->ReadAge(filename, readPages != 0);
    } catch (hsException& e) {
        plString err = plString::Format("Error reading age: %s", e.what());
        PyErr_SetString(PyExc_IOError, err.cstr());
        return NULL;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error reading age");
        return NULL;
    }
    if (age == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    } else {
        return pyAgeInfo_FromAgeInfo(age);
    }
}

static PyObject* pyResManager_WriteAge(pyResManager* self, PyObject* args) {
    const char* filename;
    pyAgeInfo* age;
    if (!PyArg_ParseTuple(args, "sO", &filename, &age)) {
        PyErr_SetString(PyExc_TypeError, "WriteAge expects string, plAgeInfo");
        return NULL;
    }
    if (!pyAgeInfo_Check((PyObject*)age)) {
        PyErr_SetString(PyExc_TypeError, "WriteAge expects string, plAgeInfo");
        return NULL;
    }
    try {
        self->fThis->WriteAge(filename, age->fThis);
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing age");
        return NULL;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyResManager_FindAge(pyResManager* self, PyObject* args) {
    const char* ageName;
    if (!PyArg_ParseTuple(args, "s", &ageName)) {
        PyErr_SetString(PyExc_TypeError, "FindAge expects a string");
        return NULL;
    }
    plAgeInfo* age = self->fThis->FindAge(ageName);
    if (age == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    } else {
        return pyAgeInfo_FromAgeInfo(age);
    }
}

static PyObject* pyResManager_UnloadAge(pyResManager* self, PyObject* args) {
    const char* ageName;
    if (!PyArg_ParseTuple(args, "s", &ageName)) {
        PyErr_SetString(PyExc_TypeError, "UnloadAge expects a string");
        return NULL;
    }
    self->fThis->UnloadAge(ageName);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyResManager_ReadCreatable(pyResManager* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "ReadCreatable expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "ReadCreatable expects an hsStream");
        return NULL;
    }
    return ICreate(self->fThis->ReadCreatable(stream->fThis));
}

static PyObject* pyResManager_ReadCreatableStub(pyResManager* self, PyObject* args) {
    pyStream* stream;
    int size;
    if (!PyArg_ParseTuple(args, "Oi", &stream, &size)) {
        PyErr_SetString(PyExc_TypeError, "ReadCreatable expects hsStream, int");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "ReadCreatable expects hsStream, int");
        return NULL;
    }
    return ICreate(self->fThis->ReadCreatable(stream->fThis, true, (size_t)size));
}

static PyObject* pyResManager_WriteCreatable(pyResManager* self, PyObject* args) {
    pyStream* stream;
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "OO", &stream, &cre)) {
        PyErr_SetString(PyExc_TypeError, "WriteCreatable expects hsStream, plCreatable");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream) || !pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "WriteCreatable expects hsStream, plCreatable");
        return NULL;
    }
    self->fThis->WriteCreatable(stream->fThis, IConvert((pyCreatable*)cre));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyResManager_getSceneNode(pyResManager* self, PyObject* args) {
    pyLocation* loc;
    if (!PyArg_ParseTuple(args, "O", &loc)) {
        PyErr_SetString(PyExc_TypeError, "getSceneNode expects a plLocation");
        return NULL;
    }
    if (!pyLocation_Check((PyObject*)loc)) {
        PyErr_SetString(PyExc_TypeError, "getSceneNode expects a plLocation");
        return NULL;
    }
    return pySceneNode_FromSceneNode(self->fThis->getSceneNode(*loc->fThis));
}

static PyObject* pyResManager_getLocations(pyResManager* self) {
    std::vector<plLocation> locs = self->fThis->getLocations();
    PyObject* list = PyList_New(locs.size());
    for (size_t i=0; i<locs.size(); i++)
        PyList_SET_ITEM(list, i, pyLocation_FromLocation(locs[i]));
    return list;
}

static PyObject* pyResManager_getTypes(pyResManager* self, PyObject* args) {
    pyLocation* loc;
    char checkKeys = 0;
    if (!PyArg_ParseTuple(args, "O|b", &loc, &checkKeys)) {
        PyErr_SetString(PyExc_TypeError, "getTypes expects a plLocation");
        return NULL;
    }
    if (!pyLocation_Check((PyObject*)loc)) {
        PyErr_SetString(PyExc_TypeError, "getTypes expects a plLocation");
        return NULL;
    }

    std::vector<short> types = self->fThis->getTypes(*loc->fThis, (checkKeys != 0));
    PyObject* list = PyList_New(types.size());
    for (size_t i=0; i<types.size(); i++)
        PyList_SET_ITEM(list, i, PyInt_FromLong(types[i]));
    return list;
}

static PyObject* pyResManager_getKeys(pyResManager* self, PyObject* args) {
    pyLocation* loc;
    int type;
    char checkKeys = 0;
    if (!PyArg_ParseTuple(args, "Oi|b", &loc, &type, &checkKeys)) {
        PyErr_SetString(PyExc_TypeError, "getTypes expects plLocation, int");
        return NULL;
    }
    if (!pyLocation_Check((PyObject*)loc)) {
        PyErr_SetString(PyExc_TypeError, "getTypes expects plLocation, int");
        return NULL;
    }

    std::vector<plKey> keys = self->fThis->getKeys(*loc->fThis, type, (checkKeys != 0));
    PyObject* list = PyList_New(keys.size());
    for (size_t i=0; i<keys.size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(keys[i]));
    return list;
}

static PyObject* pyResManager_AddObject(pyResManager* self, PyObject* args) {
    pyLocation* loc;
    pyKeyedObject* obj;
    if (!PyArg_ParseTuple(args, "OO", &loc, &obj)) {
        PyErr_SetString(PyExc_TypeError, "AddObject expects plLocation, hsKeyedObject");
        return NULL;
    }
    if (!pyLocation_Check((PyObject*)loc) || !pyKeyedObject_Check((PyObject*)obj)) {
        PyErr_SetString(PyExc_TypeError, "AddObject expects plLocation, hsKeyedObject");
        return NULL;
    }

    self->fThis->AddObject(*loc->fThis, hsKeyedObject::Convert(IConvert((pyCreatable*)obj)));
    obj->fPyOwned = false;
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyResManager_AddPage(pyResManager* self, PyObject* args) {
    pyPageInfo* page;
    if (!PyArg_ParseTuple(args, "O", &page)) {
        PyErr_SetString(PyExc_TypeError, "AddPage expects a plPageInfo");
        return NULL;
    }
    if (!pyPageInfo_Check((PyObject*)page)) {
        PyErr_SetString(PyExc_TypeError, "AddPage expects a plPageInfo");
        return NULL;
    }

    self->fThis->AddPage(page->fThis);
    page->fPyOwned = false;
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyResManager_AddAge(pyResManager* self, PyObject* args) {
    pyAgeInfo* age;
    if (!PyArg_ParseTuple(args, "O", &age)) {
        PyErr_SetString(PyExc_TypeError, "AddAge expects a plAgeInfo");
        return NULL;
    }
    if (!pyAgeInfo_Check((PyObject*)age)) {
        PyErr_SetString(PyExc_TypeError, "AddAge expects a plAgeInfo");
        return NULL;
    }

    self->fThis->AddAge(age->fThis);
    age->fPyOwned = false;
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyResManager_DelObject(pyResManager* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "DelObject expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "DelObject expects a plKey");
        return NULL;
    }

    self->fThis->DelObject(*key->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyResManager_DelPage(pyResManager* self, PyObject* args) {
    pyLocation* loc;
    if (!PyArg_ParseTuple(args, "O", &loc)) {
        PyErr_SetString(PyExc_TypeError, "DelPage expects a plLocation");
        return NULL;
    }
    if (!pyLocation_Check((PyObject*)loc)) {
        PyErr_SetString(PyExc_TypeError, "DelPage expects a plLocation");
        return NULL;
    }

    self->fThis->DelPage(*loc->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyResManager_DelAge(pyResManager* self, PyObject* args) {
    const char* age;
    if (!PyArg_ParseTuple(args, "s", &age)) {
        PyErr_SetString(PyExc_TypeError, "DelAge expects a string");
        return NULL;
    }

    self->fThis->DelAge(age);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyResManager_ChangeLocation(pyResManager* self, PyObject* args) {
    pyLocation* locFrom;
    pyLocation* locTo;
    if (!PyArg_ParseTuple(args, "OO", &locFrom, &locTo)) {
        PyErr_SetString(PyExc_TypeError, "ChangeLocation expects plLocation, plLocation");
        return NULL;
    }
    if (!pyLocation_Check((PyObject*)locFrom) || !pyLocation_Check((PyObject*)locTo)) {
        PyErr_SetString(PyExc_TypeError, "ChangeLocation expects plLocation, plLocation");
        return NULL;
    }

    self->fThis->ChangeLocation(*locFrom->fThis, *locTo->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pyResManager_Methods[] = {
    { "setVer", (PyCFunction)pyResManager_setVer, METH_VARARGS,
      "Params: version, [force]\n"
      "Sets the plasma version of the resource manager" },
    { "getVer", (PyCFunction)pyResManager_getVer, METH_NOARGS,
      "Gets the plasma version of the resource manager" },
    { "readKey", (PyCFunction)pyResManager_readKey, METH_VARARGS,
      "Params: stream\n"
      "Reads a plKey from the stream" },
    { "readUoid", (PyCFunction)pyResManager_readUoid, METH_VARARGS,
      "Params: stream\n"
      "Reads a non-null plKey from the stream" },
    { "writeKey", (PyCFunction)pyResManager_writeKey, METH_VARARGS,
      "Params: stream, key\n"
      "Writes a plKey to the stream" },
    { "writeUoid", (PyCFunction)pyResManager_writeUoid, METH_VARARGS,
      "Params: stream, key\n"
      "Writes a non-null plKey to the stream" },
    { "getObject", (PyCFunction)pyResManager_getObject, METH_VARARGS,
      "Params: key\n"
      "Finds and returns the loaded Keyed Object described by `key`" },
    { "countKeys", (PyCFunction)pyResManager_countKeys, METH_VARARGS,
      "Params: location\n"
      "Counts the number of loaded keys in `location`" },
    { "ReadPage", (PyCFunction)pyResManager_ReadPage, METH_VARARGS,
      "Params: filename, [stub]\n"
      "Reads an entire PRP file and returns the plPageInfo for it" },
    { "WritePage", (PyCFunction)pyResManager_WritePage, METH_VARARGS,
      "Params: filename, page\n"
      "Writes an entire page to a PRP file" },
    { "FindPage", (PyCFunction)pyResManager_FindPage, METH_VARARGS,
      "Params: location\n"
      "Finds and returns the plPageInfo at `location`" },
    { "UnloadPage", (PyCFunction)pyResManager_UnloadPage, METH_VARARGS,
      "Params: location\n"
      "Unloads the specified page, as well as all associated objects\n"
      "from the ResManager" },
    { "ReadAge", (PyCFunction)pyResManager_ReadAge, METH_VARARGS,
      "Params: filename, readPages\n"
      "Reads a .age file. If readPages is True, also loads all PRPs\n"
      "identified in the .age file" },
    { "WriteAge", (PyCFunction)pyResManager_WriteAge, METH_VARARGS,
      "Params: filename, age\n"
      "Writes a plAgeInfo to the specified file\n"
      "Does NOT write any PRP files!" },
    { "FindAge", (PyCFunction)pyResManager_FindAge, METH_VARARGS,
      "Params: age\n"
      "Finds and returns the plAgeInfo for `age`" },
    { "UnloadAge", (PyCFunction)pyResManager_UnloadAge, METH_VARARGS,
      "Params: age\n"
      "Unloads the specified age, as well as any pages and objects\n"
      "associated with it from the ResManager" },
    { "ReadCreatable", (PyCFunction)pyResManager_ReadCreatable, METH_VARARGS,
      "Params: stream\n"
      "Reads a Creatable from the stream" },
    { "ReadCreatableStub", (PyCFunction)pyResManager_ReadCreatableStub, METH_VARARGS,
      "Params: stream, size\n"
      "Reads a Creatable if the class is supported by libPlasma, "
      "or a CreatableStub of size `size` if it is not" },
    { "WriteCreatable", (PyCFunction)pyResManager_WriteCreatable, METH_VARARGS,
      "Params: stream, obj\n"
      "Writes the Creatable `obj` to the stream" },
    { "getSceneNode", (PyCFunction)pyResManager_getSceneNode, METH_VARARGS,
      "Params: location\n"
      "Returns the SceneNode for the specified location" },
    { "getLocations", (PyCFunction)pyResManager_getLocations, METH_NOARGS,
      "Returns a list of all loaded locations" },
    { "getTypes", (PyCFunction)pyResManager_getTypes, METH_VARARGS,
      "Params: location\n"
      "Returns a list of the Creatable Types that are used in location" },
    { "getKeys", (PyCFunction)pyResManager_getKeys, METH_VARARGS,
      "Params: location, type\n"
      "Returns all keys of type `type` loaded for the specified location" },
    { "AddObject", (PyCFunction)pyResManager_AddObject, METH_VARARGS,
      "Params: location, object\n"
      "Registers the object to `location` and adds it to the ResManager" },
    { "AddPage", (PyCFunction)pyResManager_AddPage, METH_VARARGS,
      "Params: page\n"
      "Adds the plPageInfo to the ResManager" },
    { "AddAge", (PyCFunction)pyResManager_AddAge, METH_VARARGS,
      "Params: age\n"
      "Adds the plAgeInfo to the ResManager" },
    { "DelObject", (PyCFunction)pyResManager_DelObject, METH_VARARGS,
      "Params: key\n"
      "Removes the object specified by `key` from the ResManager" },
    { "DelPage", (PyCFunction)pyResManager_DelPage, METH_VARARGS,
      "Params: location\n"
      "Deletes the Page specified by `location` from the ResManager" },
    { "DelAge", (PyCFunction)pyResManager_DelAge, METH_VARARGS,
      "Params: name\n"
      "Deletes the Age from the ResManager" },
    { "ChangeLocation", (PyCFunction)pyResManager_ChangeLocation, METH_VARARGS,
      "Params: locFrom, locTo\n"
      "Changes a location for a page and/or all keys registered under locFrom\n"
      "to locTo" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyResManager_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plResManager",          /* tp_name */
    sizeof(pyResManager),               /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyResManager_dealloc,   /* tp_dealloc */
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

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "Resource Manager",                 /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyResManager_Methods,               /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyResManager___init__,    /* tp_init */
    NULL,                               /* tp_alloc */
    pyResManager_new,                   /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
    TP_FINALIZE_INIT                    /* tp_finalize */
};

PyObject* Init_pyResManager_Type() {
    if (PyType_Ready(&pyResManager_Type) < 0)
        return NULL;

    Py_INCREF(&pyResManager_Type);
    return (PyObject*)&pyResManager_Type;
}

int pyResManager_Check(PyObject* obj) {
    if (obj->ob_type == &pyResManager_Type
        || PyType_IsSubtype(obj->ob_type, &pyResManager_Type))
        return 1;
    return 0;
}

}
