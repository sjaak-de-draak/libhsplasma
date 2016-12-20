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

#include "pyViewFaceModifier.h"

#include <PRP/Animation/plViewFaceModifier.h>
#include "PRP/Modifier/pyModifier.h"
#include "PRP/Region/pyBounds.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"
#include "Math/pyGeometry3.h"
#include "Math/pyMatrix.h"

extern "C" {

static PyObject* pyViewFaceModifier_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyViewFaceModifier* self = (pyViewFaceModifier*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plViewFaceModifier();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

PY_PROPERTY(hsVector3, ViewFaceModifier, scale, getScale, setScale)
PY_PROPERTY(hsVector3, ViewFaceModifier, offset, getOffset, setOffset)
PY_PROPERTY(hsMatrix44, ViewFaceModifier, localToparent, getLocalToParent, setLocalToParent)
PY_PROPERTY(hsMatrix44, ViewFaceModifier, parentToLocal, getParentToLocal, setParentToLocal)
PY_PROPERTY(plKey, ViewFaceModifier, faceObj, getFaceObj, setFaceObj)
PY_PROPERTY_BOUNDS(Bounds3Ext, ViewFaceModifier, maxBounds, getMaxBounds, setMaxBounds)

static PyGetSetDef pyViewFaceModifier_GetSet[] = {
    pyViewFaceModifier_scale_getset,
    pyViewFaceModifier_offset_getset,
    pyViewFaceModifier_localToparent_getset,
    pyViewFaceModifier_parentToLocal_getset,
    pyViewFaceModifier_faceObj_getset,
    pyViewFaceModifier_maxBounds_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyViewFaceModifier_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plViewFaceModifier",    /* tp_name */
    sizeof(pyViewFaceModifier),         /* tp_basicsize */
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

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "plViewFaceModifier wrapper",       /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyViewFaceModifier_GetSet,          /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyViewFaceModifier_new,             /* tp_new */
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

PyObject* Init_pyViewFaceModifier_Type() {
    pyViewFaceModifier_Type.tp_base = &pySingleModifier_Type;
    if (PyType_Ready(&pyViewFaceModifier_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kPivotFace",
                         PyInt_FromLong(plViewFaceModifier::kPivotFace));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kPivotFavorY",
                         PyInt_FromLong(plViewFaceModifier::kPivotFavorY));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kPivotY",
                         PyInt_FromLong(plViewFaceModifier::kPivotY));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kPivotTumple",
                         PyInt_FromLong(plViewFaceModifier::kPivotTumple));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kScale",
                         PyInt_FromLong(plViewFaceModifier::kScale));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kFaceCam",
                         PyInt_FromLong(plViewFaceModifier::kFaceCam));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kFaceList",
                         PyInt_FromLong(plViewFaceModifier::kFaceList));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kFacePlay",
                         PyInt_FromLong(plViewFaceModifier::kFacePlay));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kFaceObj",
                         PyInt_FromLong(plViewFaceModifier::kFaceObj));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kOffset",
                         PyInt_FromLong(plViewFaceModifier::kOffset));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kOffsetLocal",
                         PyInt_FromLong(plViewFaceModifier::kOffsetLocal));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kMaxBounds",
                         PyInt_FromLong(plViewFaceModifier::kMaxBounds));

    Py_INCREF(&pyViewFaceModifier_Type);
    return (PyObject*)&pyViewFaceModifier_Type;
}

PY_PLASMA_IFC_METHODS(ViewFaceModifier, plViewFaceModifier)

}
