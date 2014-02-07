#include "Python.h"
#include "sorv.h"

static PyObject* computeSorv(PyObject* self, PyObject* args) {
	PyObject* callback_list;
	int C;
	double epsilon;
	PyArg_ParseTuple(args, "Oid", &callback_list, &C, &epsilon);
	if(!PyList_Check(callback_list)) {
		PyErr_SetString(PyExc_TypeError, "need a list of callback oracles.");
		return Py_BuildValue("");
	}
	int n = PyList_Size(callback_list);
	PyObject* oracles_obj[n];
	Oracle oracles[n];
	for(int i = 0; i < n; i++) {
		oracles_obj[i] = PyList_GetItem(callback_list, (size_t)i);
		if (!PyCallable_Check(oracles_obj[i])) {
	        PyErr_SetString(PyExc_TypeError, "need a callable object!");
	        return Py_BuildValue("");
	    }
	    Py_XINCREF(oracles_obj[i]);
		oracles[i] = new std::function<double(int, int)>();
		(*oracles[i]) = [i, &oracles_obj] (int s1, int s2) -> double{
			PyObject* arglist = Py_BuildValue("(i, i)", s1, s2);
			double res = PyFloat_AS_DOUBLE(PyEval_CallObject(oracles_obj[i], arglist));
			Py_XDECREF(arglist);
			return res;
		};
	}
	double res = sorv(n, oracles, C, epsilon);
	return Py_BuildValue("d", res);
}

static PyMethodDef SorvMethods[] = {
    {"computeSorv",  computeSorv, METH_VARARGS,
     "Compute the distribution of the sum of random variables using [J. Li, T. Shi 2013]."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};
	
PyMODINIT_FUNC 
initsorvlib() {
	(void) Py_InitModule("sorvlib", SorvMethods);
}