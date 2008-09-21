#ifndef _PYSOUNDBUFFER_H
#define _PYSOUNDBUFFER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plWAVHeader* fThis;
} pyWAVHeader;

typedef struct {
    PyObject_HEAD
    class plSoundBuffer* fThis;
    bool fPyOwned;
} pySoundBuffer;

extern PyTypeObject pyWAVHeader_Type;
PyObject* Init_pyWAVHeader_Type();
PyObject* pyWAVHeader_FromWAVHeader(class plWAVHeader& header);

extern PyTypeObject pySoundBuffer_Type;
PyObject* Init_pySoundBuffer_Type();
int pySoundBuffer_Check(PyObject* obj);
PyObject* pySoundBuffer_FromSoundBuffer(class plSoundBuffer* buf);

}

#endif
