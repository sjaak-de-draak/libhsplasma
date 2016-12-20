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

#include "pyKeys.h"

#include <PRP/Animation/hsKeys.h>
#include "Math/pyGeometry3.h"

extern "C" {

static int pyPoint3Key___init__(pyPoint3Key* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyPoint3Key_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyPoint3Key* self = (pyPoint3Key*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new hsPoint3Key();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

PY_PROPERTY_MEMBER(hsVector3, Point3Key, inTan, fInTan)
PY_PROPERTY_MEMBER(hsVector3, Point3Key, outTan, fOutTan)
PY_PROPERTY_MEMBER(hsVector3, Point3Key, value, fValue)

static PyGetSetDef pyPoint3Key_GetSet[] = {
    pyPoint3Key_inTan_getset,
    pyPoint3Key_outTan_getset,
    pyPoint3Key_value_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyPoint3Key_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsPoint3Key",           /* tp_name */
    sizeof(pyPoint3Key),                /* tp_basicsize */
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
    "hsPoint3Key wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyPoint3Key_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyPoint3Key___init__,     /* tp_init */
    NULL,                               /* tp_alloc */
    pyPoint3Key_new,                    /* tp_new */
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

PyObject* Init_pyPoint3Key_Type() {
    pyPoint3Key_Type.tp_base = &pyKeyFrame_Type;
    if (PyType_Ready(&pyPoint3Key_Type) < 0)
        return NULL;

    Py_INCREF(&pyPoint3Key_Type);
    return (PyObject*)&pyPoint3Key_Type;
}

PY_PLASMA_IFC_METHODS(Point3Key, hsPoint3Key)

}
