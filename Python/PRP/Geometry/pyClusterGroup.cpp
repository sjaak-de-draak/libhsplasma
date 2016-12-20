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

#include "pyClusterGroup.h"

#include <PRP/Geometry/plClusterGroup.h>
#include "pyCluster.h"
#include "pySpanTemplate.h"
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyClusterGroup_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyClusterGroup* self = (pyClusterGroup*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plClusterGroup();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyClusterGroup_addCluster(pyClusterGroup* self, PyObject* args) {
    pyCluster* cluster;
    if (!PyArg_ParseTuple(args, "O", &cluster)) {
        PyErr_SetString(PyExc_TypeError, "addCluster expects a plCluster");
        return NULL;
    }
    if (!pyCluster_Check((PyObject*)cluster)) {
        PyErr_SetString(PyExc_TypeError, "addCluster expects a plCluster");
        return NULL;
    }
    self->fThis->addCluster(cluster->fThis);
    cluster->fPyOwned = false;
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyClusterGroup_delCluster(pyClusterGroup* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delCluster expects an int");
        return NULL;
    }
    self->fThis->delCluster(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyClusterGroup_clearClusters(pyClusterGroup* self) {
    self->fThis->clearClusters();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyClusterGroup_addRegion(pyClusterGroup* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addRegion expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addRegion expects a plKey");
        return NULL;
    }
    self->fThis->addRegion(*key->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyClusterGroup_delRegion(pyClusterGroup* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delRegion expects an int");
        return NULL;
    }
    self->fThis->delRegion(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyClusterGroup_clearRegions(pyClusterGroup* self) {
    self->fThis->clearRegions();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyClusterGroup_addLight(pyClusterGroup* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addLight expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addLight expects a plKey");
        return NULL;
    }
    self->fThis->addLight(*key->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyClusterGroup_delLight(pyClusterGroup* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delLight expects an int");
        return NULL;
    }
    self->fThis->delLight(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyClusterGroup_clearLights(pyClusterGroup* self) {
    self->fThis->clearLights();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyClusterGroup_getClusters(pyClusterGroup* self, void*) {
    PyObject* list = PyList_New(self->fThis->getClusters().size());
    for (size_t i=0; i<self->fThis->getClusters().size(); i++)
        PyList_SET_ITEM(list, i, pyCluster_FromCluster(self->fThis->getClusters()[i]));
    return list;
}

static PyObject* pyClusterGroup_getRegions(pyClusterGroup* self, void*) {
    PyObject* list = PyList_New(self->fThis->getRegions().size());
    for (size_t i=0; i<self->fThis->getRegions().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getRegions()[i]));
    return list;
}

static PyObject* pyClusterGroup_getLights(pyClusterGroup* self, void*) {
    PyObject* list = PyList_New(self->fThis->getLights().size());
    for (size_t i=0; i<self->fThis->getLights().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getLights()[i]));
    return list;
}

static int pyClusterGroup_setClusters(pyClusterGroup* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add clusters, use addCluster");
    return -1;
}

static int pyClusterGroup_setRegions(pyClusterGroup* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add regions, use addRegion");
    return -1;
}

static int pyClusterGroup_setLights(pyClusterGroup* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add lights, use addLight");
    return -1;
}

static PyMethodDef pyClusterGroup_Methods[] = {
    { "addCluster", (PyCFunction)pyClusterGroup_addCluster, METH_VARARGS,
      "Params: region\n"
      "Add a plCluster object to the group" },
    { "delCluster", (PyCFunction)pyClusterGroup_delCluster, METH_VARARGS,
      "Params: idx\n"
      "Remove a plCluster object from the group" },
    { "clearClusters", (PyCFunction)pyClusterGroup_clearClusters, METH_NOARGS,
      "Remove all clusters from the group" },
    { "addRegion", (PyCFunction)pyClusterGroup_addRegion, METH_VARARGS,
      "Params: key\n"
      "Add a region reference to the group" },
    { "delRegion", (PyCFunction)pyClusterGroup_delRegion, METH_VARARGS,
      "Params: idx\n"
      "Remove a region reference from the group" },
    { "clearRegions", (PyCFunction)pyClusterGroup_clearRegions, METH_NOARGS,
      "Remove all regions from the group" },
    { "addLight", (PyCFunction)pyClusterGroup_addLight, METH_VARARGS,
      "Params: key\n"
      "Add a light reference to the group" },
    { "delLight", (PyCFunction)pyClusterGroup_delLight, METH_VARARGS,
      "Params: idx\n"
      "Remove a light reference from the group" },
    { "clearLights", (PyCFunction)pyClusterGroup_clearLights, METH_NOARGS,
      "Remove all lights from the group" },
    { NULL, NULL, 0, NULL }
};

PY_PROPERTY_PROXY_RO(plLODDist, ClusterGroup, LOD, getLOD)
PY_PROPERTY_PROXY_RO(plSpanTemplate, ClusterGroup, template, getTemplate)
PY_PROPERTY(plKey, ClusterGroup, material, getMaterial, setMaterial)
PY_PROPERTY(plKey, ClusterGroup, sceneNode, getSceneNode, setSceneNode)
PY_PROPERTY(plKey, ClusterGroup, drawable, getDrawable, setDrawable)
PY_PROPERTY(unsigned int, ClusterGroup, renderLevel, getRenderLevel, setRenderLevel)

static PyGetSetDef pyClusterGroup_GetSet[] = {
    pyClusterGroup_LOD_getset,
    pyClusterGroup_template_getset,
    pyClusterGroup_material_getset,
    pyClusterGroup_sceneNode_getset,
    pyClusterGroup_drawable_getset,
    pyClusterGroup_renderLevel_getset,
    { _pycs("clusters"), (getter)pyClusterGroup_getClusters,
        (setter)pyClusterGroup_setClusters, NULL, NULL },
    { _pycs("regions"), (getter)pyClusterGroup_getRegions,
        (setter)pyClusterGroup_setRegions, NULL, NULL },
    { _pycs("lights"), (getter)pyClusterGroup_getLights,
        (setter)pyClusterGroup_setLights, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PyTypeObject pyClusterGroup_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plClusterGroup",        /* tp_name */
    sizeof(pyClusterGroup),             /* tp_basicsize */
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
    "pyClusterGroup wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyClusterGroup_Methods,             /* tp_methods */
    NULL,                               /* tp_members */
    pyClusterGroup_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyClusterGroup_new,                 /* tp_new */
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

PyObject* Init_pyClusterGroup_Type() {
    pyClusterGroup_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_Ready(&pyClusterGroup_Type) < 0)
        return NULL;

    Py_INCREF(&pyClusterGroup_Type);
    return (PyObject*)&pyClusterGroup_Type;
}

PY_PLASMA_IFC_METHODS(ClusterGroup, plClusterGroup)

}
