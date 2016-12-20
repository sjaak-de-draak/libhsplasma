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

#include "pyAgeLinkInfo.h"

#include <PRP/Misc/plAgeLinkInfo.h>
#include "pySpawnPointInfo.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyAgeLinkStruct_new(PyTypeObject* type, PyObject*, PyObject*) {
    pyAgeLinkStruct* self = (pyAgeLinkStruct*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plAgeLinkStruct();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

PY_GETSET_GETTER_DECL(AgeLinkStruct, ageInfo) {
    // This cannot be a subclass, since it's an inline member
    return pyAgeInfoStruct_FromAgeInfoStruct(&self->fThis->getAgeInfo());
}

PY_GETSET_SETTER_DECL(AgeLinkStruct, ageInfo) {
    plAgeInfoStruct& ais = self->fThis->getAgeInfo();
    if (value == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "ageInfo cannot be deleted");
        return -1;
    } else if (value == Py_None) {
        self->fThis->setHasAgeInfo(false);
        ais = plAgeInfoStruct();
        return 0;
    } else if (pyAgeInfoStruct_Check(value)) {
        self->fThis->setHasAgeInfo(true);
        ais = *((pyAgeInfoStruct*)value)->fThis;
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "ageInfo must be a plAgeInfoStruct");
        return -1;
    }
}

PY_PROPERTY_GETSET_DECL(AgeLinkStruct, ageInfo)

PY_GETSET_GETTER_DECL(AgeLinkStruct, spawnPoint) {
    return pySpawnPointInfo_FromSpawnPointInfo(&self->fThis->getSpawnPoint());
}

PY_GETSET_SETTER_DECL(AgeLinkStruct, spawnPoint) {
    plSpawnPointInfo& spi = self->fThis->getSpawnPoint();
    if (value == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "spawnPoint cannot be deleted");
        return -1;
    } else if (value == Py_None) {
        self->fThis->setHasSpawnPoint(false);
        spi = plSpawnPointInfo();
        return 0;
    } else if (pySpawnPointInfo_Check(value)) {
        self->fThis->setHasSpawnPoint(true);
        spi = *((pySpawnPointInfo*)value)->fThis;
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "spawnPoint must be a plSpawnPointInfo");
        return -1;
    }
}

PY_PROPERTY_GETSET_DECL(AgeLinkStruct, spawnPoint)

PY_PROPERTY(signed char, AgeLinkStruct, linkingRules, getLinkingRules, setLinkingRules)

PY_PROPERTY_READ(AgeLinkStruct, parentAgeFilename, getParentAgeFilename)

PY_GETSET_SETTER_DECL(AgeLinkStruct, parentAgeFilename) {
    if (value == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "Cannot delete parentAgeFilename");
        return -1;
    } else if (value == Py_None) {
        self->fThis->clearParentAgeFilename();
        return 0;
    } else if (pyPlasma_check<plString>(value)) {
        self->fThis->setParentAgeFilename(pyPlasma_get<plString>(value));
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "parentAgeFilename must be a string");
        return -1;
    }
}

PY_PROPERTY_GETSET_DECL(AgeLinkStruct, parentAgeFilename)

PyGetSetDef pyAgeLinkStruct_GetSet[] = {
    pyAgeLinkStruct_ageInfo_getset,
    pyAgeLinkStruct_spawnPoint_getset,
    pyAgeLinkStruct_linkingRules_getset,
    pyAgeLinkStruct_parentAgeFilename_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyAgeLinkStruct_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plAgeLinkStruct",       /* tp_name */
    sizeof(pyAgeLinkStruct),            /* tp_basicsize */
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
    "plAgeLinkStruct wrapper",                 /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyAgeLinkStruct_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyAgeLinkStruct_new,                /* tp_new */
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

PyObject* Init_pyAgeLinkStruct_Type() {
    pyAgeLinkStruct_Type.tp_base = &pyCreatable_Type;
    if (PyType_Ready(&pyAgeLinkStruct_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyAgeLinkStruct_Type.tp_dict, "kBasicLink",
                         PyInt_FromLong(plAgeLinkStruct::kBasicLink));
    PyDict_SetItemString(pyAgeLinkStruct_Type.tp_dict, "kOriginalBook",
                         PyInt_FromLong(plAgeLinkStruct::kOriginalBook));
    PyDict_SetItemString(pyAgeLinkStruct_Type.tp_dict, "kSubAgeBook",
                         PyInt_FromLong(plAgeLinkStruct::kSubAgeBook));
    PyDict_SetItemString(pyAgeLinkStruct_Type.tp_dict, "kOwnedBook",
                         PyInt_FromLong(plAgeLinkStruct::kOwnedBook));
    PyDict_SetItemString(pyAgeLinkStruct_Type.tp_dict, "kVisitBook",
                         PyInt_FromLong(plAgeLinkStruct::kVisitBook));
    PyDict_SetItemString(pyAgeLinkStruct_Type.tp_dict, "kChildAgeBook",
                         PyInt_FromLong(plAgeLinkStruct::kChildAgeBook));

    Py_INCREF(&pyAgeLinkStruct_Type);
    return (PyObject*)&pyAgeLinkStruct_Type;
}

PY_PLASMA_IFC_METHODS(AgeLinkStruct, plAgeLinkStruct)

}
