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

#ifndef _PYAGCHANNEL_H
#define _PYAGCHANNEL_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plAGChannel* fThis;
    bool fPyOwned;
} pyAGChannel;

typedef struct {
    PyObject_HEAD
    class plMatrixChannel* fThis;
    bool fPyOwned;
} pyMatrixChannel;

typedef struct {
    PyObject_HEAD
    class plMatrixBlend* fThis;
    bool fPyOwned;
} pyMatrixBlend;

typedef struct {
    PyObject_HEAD
    class plMatrixConstant* fThis;
    bool fPyOwned;
} pyMatrixConstant;

typedef struct {
    PyObject_HEAD
    class plMatrixControllerCacheChannel* fThis;
    bool fPyOwned;
} pyMatrixControllerCacheChannel;

typedef struct {
    PyObject_HEAD
    class plMatrixControllerChannel* fThis;
    bool fPyOwned;
} pyMatrixControllerChannel;

typedef struct {
    PyObject_HEAD
    class plMatrixTimeScale* fThis;
    bool fPyOwned;
} pyMatrixTimeScale;

typedef struct {
    PyObject_HEAD
    class plQuatPointCombine* fThis;
    bool fPyOwned;
} pyQuatPointCombine;

typedef struct {
    PyObject_HEAD
    class plPointChannel* fThis;
    bool fPyOwned;
} pyPointChannel;

typedef struct {
    PyObject_HEAD
    class plPointBlend* fThis;
    bool fPyOwned;
} pyPointBlend;

typedef struct {
    PyObject_HEAD
    class plPointConstant* fThis;
    bool fPyOwned;
} pyPointConstant;

typedef struct {
    PyObject_HEAD
    class plPointControllerCacheChannel* fThis;
    bool fPyOwned;
} pyPointControllerCacheChannel;

typedef struct {
    PyObject_HEAD
    class plPointControllerChannel* fThis;
    bool fPyOwned;
} pyPointControllerChannel;

typedef struct {
    PyObject_HEAD
    class plPointTimeScale* fThis;
    bool fPyOwned;
} pyPointTimeScale;

typedef struct {
    PyObject_HEAD
    class plQuatChannel* fThis;
    bool fPyOwned;
} pyQuatChannel;

typedef struct {
    PyObject_HEAD
    class plQuatBlend* fThis;
    bool fPyOwned;
} pyQuatBlend;

typedef struct {
    PyObject_HEAD
    class plQuatConstant* fThis;
    bool fPyOwned;
} pyQuatConstant;

typedef struct {
    PyObject_HEAD
    class plQuatTimeScale* fThis;
    bool fPyOwned;
} pyQuatTimeScale;

typedef struct {
    PyObject_HEAD
    class plScalarChannel* fThis;
    bool fPyOwned;
} pyScalarChannel;

typedef struct {
    PyObject_HEAD
    class plScalarBlend* fThis;
    bool fPyOwned;
} pyScalarBlend;

typedef struct {
    PyObject_HEAD
    class plScalarConstant* fThis;
    bool fPyOwned;
} pyScalarConstant;

typedef struct {
    PyObject_HEAD
    class plScalarControllerCacheChannel* fThis;
    bool fPyOwned;
} pyScalarControllerCacheChannel;

typedef struct {
    PyObject_HEAD
    class plScalarControllerChannel* fThis;
    bool fPyOwned;
} pyScalarControllerChannel;

typedef struct {
    PyObject_HEAD
    class plScalarTimeScale* fThis;
    bool fPyOwned;
} pyScalarTimeScale;

typedef struct {
    PyObject_HEAD
    class plScalarSDLChannel* fThis;
    bool fPyOwned;
} pyScalarSDLChannel;

typedef struct {
    PyObject_HEAD
    class plATCChannel* fThis;
    bool fPyOwned;
} pyATCChannel;

extern PyTypeObject pyAGChannel_Type;
PyObject* Init_pyAGChannel_Type();
int pyAGChannel_Check(PyObject* obj);
PyObject* pyAGChannel_FromAGChannel(class plAGChannel* chan);

extern PyTypeObject pyMatrixChannel_Type;
PyObject* Init_pyMatrixChannel_Type();
int pyMatrixChannel_Check(PyObject* obj);
PyObject* pyMatrixChannel_FromMatrixChannel(class plMatrixChannel* chan);

extern PyTypeObject pyMatrixBlend_Type;
PyObject* Init_pyMatrixBlend_Type();
int pyMatrixBlend_Check(PyObject* obj);
PyObject* pyMatrixBlend_FromMatrixBlend(class plMatrixBlend* chan);

extern PyTypeObject pyMatrixConstant_Type;
PyObject* Init_pyMatrixConstant_Type();
int pyMatrixConstant_Check(PyObject* obj);
PyObject* pyMatrixConstant_FromMatrixConstant(class plMatrixConstant* chan);

extern PyTypeObject pyMatrixControllerCacheChannel_Type;
PyObject* Init_pyMatrixControllerCacheChannel_Type();
int pyMatrixControllerCacheChannel_Check(PyObject* obj);
PyObject* pyMatrixControllerCacheChannel_FromMatrixControllerCacheChannel(class plMatrixControllerCacheChannel* chan);

extern PyTypeObject pyMatrixControllerChannel_Type;
PyObject* Init_pyMatrixControllerChannel_Type();
int pyMatrixControllerChannel_Check(PyObject* obj);
PyObject* pyMatrixControllerChannel_FromMatrixControllerChannel(class plMatrixControllerChannel* chan);

extern PyTypeObject pyMatrixTimeScale_Type;
PyObject* Init_pyMatrixTimeScale_Type();
int pyMatrixTimeScale_Check(PyObject* obj);
PyObject* pyMatrixTimeScale_FromMatrixTimeScale(class plMatrixTimeScale* chan);

extern PyTypeObject pyQuatPointCombine_Type;
PyObject* Init_pyQuatPointCombine_Type();
int pyQuatPointCombine_Check(PyObject* obj);
PyObject* pyQuatPointCombine_FromQuatPointCombine(class plQuatPointCombine* chan);

extern PyTypeObject pyPointChannel_Type;
PyObject* Init_pyPointChannel_Type();
int pyPointChannel_Check(PyObject* obj);
PyObject* pyPointChannel_FromPointChannel(class plPointChannel* chan);

extern PyTypeObject pyPointBlend_Type;
PyObject* Init_pyPointBlend_Type();
int pyPointBlend_Check(PyObject* obj);
PyObject* pyPointBlend_FromPointBlend(class plPointBlend* chan);

extern PyTypeObject pyPointConstant_Type;
PyObject* Init_pyPointConstant_Type();
int pyPointConstant_Check(PyObject* obj);
PyObject* pyPointConstant_FromPointConstant(class plPointConstant* chan);

extern PyTypeObject pyPointControllerCacheChannel_Type;
PyObject* Init_pyPointControllerCacheChannel_Type();
int pyPointControllerCacheChannel_Check(PyObject* obj);
PyObject* pyPointControllerCacheChannel_FromPointControllerCacheChannel(class plPointControllerCacheChannel* chan);

extern PyTypeObject pyPointControllerChannel_Type;
PyObject* Init_pyPointControllerChannel_Type();
int pyPointControllerChannel_Check(PyObject* obj);
PyObject* pyPointControllerChannel_FromPointControllerChannel(class plPointControllerChannel* chan);

extern PyTypeObject pyPointTimeScale_Type;
PyObject* Init_pyPointTimeScale_Type();
int pyPointTimeScale_Check(PyObject* obj);
PyObject* pyPointTimeScale_FromPointTimeScale(class plPointTimeScale* chan);

extern PyTypeObject pyQuatChannel_Type;
PyObject* Init_pyQuatChannel_Type();
int pyQuatChannel_Check(PyObject* obj);
PyObject* pyQuatChannel_FromQuatChannel(class plQuatChannel* chan);

extern PyTypeObject pyQuatBlend_Type;
PyObject* Init_pyQuatBlend_Type();
int pyQuatBlend_Check(PyObject* obj);
PyObject* pyQuatBlend_FromQuatBlend(class plQuatBlend* chan);

extern PyTypeObject pyQuatConstant_Type;
PyObject* Init_pyQuatConstant_Type();
int pyQuatConstant_Check(PyObject* obj);
PyObject* pyQuatConstant_FromQuatConstant(class plQuatConstant* chan);

extern PyTypeObject pyQuatTimeScale_Type;
PyObject* Init_pyQuatTimeScale_Type();
int pyQuatTimeScale_Check(PyObject* obj);
PyObject* pyQuatTimeScale_FromQuatTimeScale(class plQuatTimeScale* chan);

extern PyTypeObject pyScalarChannel_Type;
PyObject* Init_pyScalarChannel_Type();
int pyScalarChannel_Check(PyObject* obj);
PyObject* pyScalarChannel_FromScalarChannel(class plScalarChannel* chan);

extern PyTypeObject pyScalarBlend_Type;
PyObject* Init_pyScalarBlend_Type();
int pyScalarBlend_Check(PyObject* obj);
PyObject* pyScalarBlend_FromScalarBlend(class plScalarBlend* chan);

extern PyTypeObject pyScalarConstant_Type;
PyObject* Init_pyScalarConstant_Type();
int pyScalarConstant_Check(PyObject* obj);
PyObject* pyScalarConstant_FromScalarConstant(class plScalarConstant* chan);

extern PyTypeObject pyScalarControllerCacheChannel_Type;
PyObject* Init_pyScalarControllerCacheChannel_Type();
int pyScalarControllerCacheChannel_Check(PyObject* obj);
PyObject* pyScalarControllerCacheChannel_FromScalarControllerCacheChannel(class plScalarControllerCacheChannel* chan);

extern PyTypeObject pyScalarControllerChannel_Type;
PyObject* Init_pyScalarControllerChannel_Type();
int pyScalarControllerChannel_Check(PyObject* obj);
PyObject* pyScalarControllerChannel_FromScalarControllerChannel(class plScalarControllerChannel* chan);

extern PyTypeObject pyScalarTimeScale_Type;
PyObject* Init_pyScalarTimeScale_Type();
int pyScalarTimeScale_Check(PyObject* obj);
PyObject* pyScalarTimeScale_FromScalarTimeScale(class plScalarTimeScale* chan);

extern PyTypeObject pyScalarSDLChannel_Type;
PyObject* Init_pyScalarSDLChannel_Type();
int pyScalarSDLChannel_Check(PyObject* obj);
PyObject* pyScalarSDLChannel_FromScalarSDLChannel(class plScalarSDLChannel* chan);

extern PyTypeObject pyATCChannel_Type;
PyObject* Init_pyATCChannel_Type();
int pyATCChannel_Check(PyObject* obj);
PyObject* pyATCChannel_FromATCChannel(class plATCChannel* chan);

}

#endif
