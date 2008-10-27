#include <Python.h>
#include <PRP/Geometry/plSpanInstance.h>
#include "pySpanInstance.h"
#include "../../Stream/pyStream.h"
#include "../../Math/pyMatrix44.h"
#include "../../Math/pyGeometry3.h"

extern "C" {

static void pySpanInstance_dealloc(pySpanInstance* self) {
    if (self->fPyOwned)
        delete self->fThis;
    self->ob_type->tp_free((PyObject*)self);
}

static int pySpanInstance___init__(pySpanInstance* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pySpanInstance_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySpanInstance* self = (pySpanInstance*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSpanInstance();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pySpanInstance_read(pySpanInstance* self, PyObject* args) {
    pyStream* stream;
    pySpanEncoding* encoding;
    int numVerts;
    if (!PyArg_ParseTuple(args, "OOi", &stream, &encoding, &numVerts)) {
        PyErr_SetString(PyExc_TypeError, "read expects hsStream, plSpanEncoding, int");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream) || !pySpanEncoding_Check((PyObject*)encoding)) {
        PyErr_SetString(PyExc_TypeError, "read expects hsStream, plSpanEncoding, int");
        return NULL;
    }
    self->fThis->read(stream->fThis, *encoding->fThis, numVerts);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySpanInstance_write(pySpanInstance* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return NULL;
    }
    self->fThis->write(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySpanInstance_getPosDeltas(pySpanInstance* self, void*) {
    hsTArray<hsVector3> deltas = self->fThis->getPosDeltas();
    PyObject* list = PyList_New(deltas.getSize());
    for (size_t i=0; i<deltas.getSize(); i++)
        PyList_SET_ITEM(list, i, pyVector3_FromVector3(deltas[i]));
    return list;
}

static PyObject* pySpanInstance_getColors(pySpanInstance* self, void*) {
    hsTArray<unsigned int> colors = self->fThis->getColors();
    PyObject* list = PyList_New(colors.getSize());
    for (size_t i=0; i<colors.getSize(); i++)
        PyList_SET_ITEM(list, i, PyInt_FromLong(colors[i]));
    return list;
}

static PyObject* pySpanInstance_getL2W(pySpanInstance* self, void*) {
    return pyMatrix44_FromMatrix44(self->fThis->getLocalToWorld());
}

static int pySpanInstance_setPosDeltas(pySpanInstance* self, PyObject* value, void*) {
    hsTArray<hsVector3> deltas;
    if (value == NULL) {
        self->fThis->setPosDeltas(deltas);
        return 0;
    }
    if (!PyList_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "posDeltas should be a list of hsVector3 objects");
        return -1;
    }
    deltas.setSize(PyList_Size(value));
    for (size_t i=0; i<deltas.getSize(); i++) {
        PyObject* itm = PyList_GetItem(value, i);
        if (!pyVector3_Check(itm)) {
            PyErr_SetString(PyExc_TypeError, "posDeltas should be a list of hsVector3 objects");
            return -1;
        }
        deltas[i] = *((pyVector3*)itm)->fThis;
    }
    self->fThis->setPosDeltas(deltas);
    return 0;
}

static int pySpanInstance_setColors(pySpanInstance* self, PyObject* value, void*) {
    hsTArray<unsigned int> colors;
    if (value == NULL) {
        self->fThis->setColors(colors);
        return 0;
    }
    if (!PyList_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "colors should be a list of ints");
        return -1;
    }
    colors.setSize(PyList_Size(value));
    for (size_t i=0; i<colors.getSize(); i++) {
        PyObject* itm = PyList_GetItem(value, i);
        if (!PyInt_Check(itm)) {
            PyErr_SetString(PyExc_TypeError, "colors should be a list of ints");
            return -1;
        }
        colors[i] = PyInt_AsLong(itm);
    }
    self->fThis->setColors(colors);
    return 0;
}

static int pySpanInstance_setL2W(pySpanInstance* self, PyObject* value, void*) {
    if (value == NULL || !pyMatrix44_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "localToWorld should be an hsMatrix44");
        return -1;
    }
    self->fThis->setLocalToWorld(*((pyMatrix44*)value)->fThis);
    return 0;
}

static PyMethodDef pySpanInstance_Methods[] = {
    { "read", (PyCFunction)pySpanInstance_read, METH_VARARGS,
      "Params: stream, encoding, numVerts\n"
      "Reads this object from the stream" },
    { "write", (PyCFunction)pySpanInstance_write, METH_VARARGS,
      "Params: stream\n"
      "Writes this object to the stream" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pySpanInstance_GetSet[] = {
    { "posDeltas", (getter)pySpanInstance_getPosDeltas, (setter)pySpanInstance_setPosDeltas, NULL, NULL },
    { "colors", (getter)pySpanInstance_getColors, (setter)pySpanInstance_setColors, NULL, NULL },
    { "localToWorld", (getter)pySpanInstance_getL2W, (setter)pySpanInstance_setL2W, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySpanInstance_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plSpanInstance",          /* tp_name */
    sizeof(pySpanInstance),             /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pySpanInstance_dealloc, /* tp_dealloc */
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
    "plSpanInstance wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySpanInstance_Methods,             /* tp_methods */
    NULL,                               /* tp_members */
    pySpanInstance_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pySpanInstance___init__,  /* tp_init */
    NULL,                               /* tp_alloc */
    pySpanInstance_new,                 /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pySpanInstance_Type() {
    if (PyType_Ready(&pySpanInstance_Type) < 0)
        return NULL;

    Py_INCREF(&pySpanInstance_Type);
    return (PyObject*)&pySpanInstance_Type;
}

int pySpanInstance_Check(PyObject* obj) {
    if (obj->ob_type == &pySpanInstance_Type
        || PyType_IsSubtype(obj->ob_type, &pySpanInstance_Type))
        return 1;
    return 0;
}

PyObject* pySpanInstance_FromSpanInstance(plSpanInstance* span) {
    if (span == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pySpanInstance* obj = PyObject_New(pySpanInstance, &pySpanInstance_Type);
    obj->fThis = span;
    obj->fPyOwned = false;
    return (PyObject*)obj;
}

}
