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

#ifndef _PYEVENTDATA_H
#define _PYEVENTDATA_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class proEventData* fThis;
    bool fPyOwned;
} pyEventData;

typedef struct {
    PyObject_HEAD
    class proCollisionEventData* fThis;
    bool fPyOwned;
} pyCollisionEventData;

typedef struct {
    PyObject_HEAD
    class proPickedEventData* fThis;
    bool fPyOwned;
} pyPickedEventData;

typedef struct {
    PyObject_HEAD
    class proControlKeyEventData* fThis;
    bool fPyOwned;
} pyControlKeyEventData;

typedef struct {
    PyObject_HEAD
    class proVariableEventData* fThis;
    bool fPyOwned;
} pyVariableEventData;

typedef struct {
    PyObject_HEAD
    class proFacingEventData* fThis;
    bool fPyOwned;
} pyFacingEventData;

typedef struct {
    PyObject_HEAD
    class proContainedEventData* fThis;
    bool fPyOwned;
} pyContainedEventData;

typedef struct {
    PyObject_HEAD
    class proActivateEventData* fThis;
    bool fPyOwned;
} pyActivateEventData;

typedef struct {
    PyObject_HEAD
    class proCallbackEventData* fThis;
    bool fPyOwned;
} pyCallbackEventData;

typedef struct {
    PyObject_HEAD
    class proResponderStateEventData* fThis;
    bool fPyOwned;
} pyResponderStateEventData;

typedef struct {
    PyObject_HEAD
    class proMultiStageEventData* fThis;
    bool fPyOwned;
} pyMultiStageEventData;

typedef struct {
    PyObject_HEAD
    class proSpawnedEventData* fThis;
    bool fPyOwned;
} pySpawnedEventData;

typedef struct {
    PyObject_HEAD
    class proClickDragEventData* fThis;
    bool fPyOwned;
} pyClickDragEventData;

typedef struct {
    PyObject_HEAD
    class proCoopEventData* fThis;
    bool fPyOwned;
} pyCoopEventData;

typedef struct {
    PyObject_HEAD
    class proOfferLinkBookEventData* fThis;
    bool fPyOwned;
} pyOfferLinkBookEventData;

typedef struct {
    PyObject_HEAD
    class proBookEventData* fThis;
    bool fPyOwned;
} pyBookEventData;

typedef struct {
    PyObject_HEAD
    class proClimbingBlockerHitEventData* fThis;
    bool fPyOwned;
} pyClimbingBlockerHitEventData;

extern PyTypeObject pyEventData_Type;
PyObject* Init_pyEventData_Type();
int pyEventData_Check(PyObject* obj);
PyObject* pyEventData_FromEventData(class proEventData* evt);

extern PyTypeObject pyCollisionEventData_Type;
PyObject* Init_pyCollisionEventData_Type();
int pyCollisionEventData_Check(PyObject* obj);
PyObject* pyCollisionEventData_FromCollisionEventData(class proCollisionEventData* evt);

extern PyTypeObject pyPickedEventData_Type;
PyObject* Init_pyPickedEventData_Type();
int pyPickedEventData_Check(PyObject* obj);
PyObject* pyPickedEventData_FromPickedEventData(class proPickedEventData* evt);

extern PyTypeObject pyControlKeyEventData_Type;
PyObject* Init_pyControlKeyEventData_Type();
int pyControlKeyEventData_Check(PyObject* obj);
PyObject* pyControlKeyEventData_FromControlKeyEventData(class proControlKeyEventData* evt);

extern PyTypeObject pyVariableEventData_Type;
PyObject* Init_pyVariableEventData_Type();
int pyVariableEventData_Check(PyObject* obj);
PyObject* pyVariableEventData_FromVariableEventData(class proVariableEventData* evt);

extern PyTypeObject pyFacingEventData_Type;
PyObject* Init_pyFacingEventData_Type();
int pyFacingEventData_Check(PyObject* obj);
PyObject* pyFacingEventData_FromFacingEventData(class proFacingEventData* evt);

extern PyTypeObject pyContainedEventData_Type;
PyObject* Init_pyContainedEventData_Type();
int pyContainedEventData_Check(PyObject* obj);
PyObject* pyContainedEventData_FromContainedEventData(class proContainedEventData* evt);

extern PyTypeObject pyActivateEventData_Type;
PyObject* Init_pyActivateEventData_Type();
int pyActivateEventData_Check(PyObject* obj);
PyObject* pyActivateEventData_FromActivateEventData(class proActivateEventData* evt);

extern PyTypeObject pyCallbackEventData_Type;
PyObject* Init_pyCallbackEventData_Type();
int pyCallbackEventData_Check(PyObject* obj);
PyObject* pyCallbackEventData_FromCallbackEventData(class proCallbackEventData* evt);

extern PyTypeObject pyResponderStateEventData_Type;
PyObject* Init_pyResponderStateEventData_Type();
int pyResponderStateEventData_Check(PyObject* obj);
PyObject* pyResponderStateEventData_FromResponderStateEventData(class proResponderStateEventData* evt);

extern PyTypeObject pyMultiStageEventData_Type;
PyObject* Init_pyMultiStageEventData_Type();
int pyMultiStageEventData_Check(PyObject* obj);
PyObject* pyMultiStageEventData_FromMultiStageEventData(class proMultiStageEventData* evt);

extern PyTypeObject pySpawnedEventData_Type;
PyObject* Init_pySpawnedEventData_Type();
int pySpawnedEventData_Check(PyObject* obj);
PyObject* pySpawnedEventData_FromSpawnedEventData(class proSpawnedEventData* evt);

extern PyTypeObject pyClickDragEventData_Type;
PyObject* Init_pyClickDragEventData_Type();
int pyClickDragEventData_Check(PyObject* obj);
PyObject* pyClickDragEventData_FromClickDragEventData(class proClickDragEventData* evt);

extern PyTypeObject pyCoopEventData_Type;
PyObject* Init_pyCoopEventData_Type();
int pyCoopEventData_Check(PyObject* obj);
PyObject* pyCoopEventData_FromCoopEventData(class proCoopEventData* evt);

extern PyTypeObject pyOfferLinkBookEventData_Type;
PyObject* Init_pyOfferLinkBookEventData_Type();
int pyOfferLinkBookEventData_Check(PyObject* obj);
PyObject* pyOfferLinkBookEventData_FromOfferLinkBookEventData(class proOfferLinkBookEventData* evt);

extern PyTypeObject pyBookEventData_Type;
PyObject* Init_pyBookEventData_Type();
int pyBookEventData_Check(PyObject* obj);
PyObject* pyBookEventData_FromBookEventData(class proBookEventData* evt);

extern PyTypeObject pyClimbingBlockerHitEventData_Type;
PyObject* Init_pyClimbingBlockerHitEventData_Type();
int pyClimbingBlockerHitEventData_Check(PyObject* obj);
PyObject* pyClimbingBlockerHitEventData_FromClimbingBlockerHitEventData(class proClimbingBlockerHitEventData* evt);

}

#endif
