#include <iostream>
#include <Python.h>
#include <stdarg.h>
#include "python_bind.h"
#define PYTHON_LOG_MAXLEN 4096
void _log(MODULE_NAME * self, const char * type, const char * msg, ...)
{
    char str_tmp[PYTHON_LOG_MAXLEN];
    va_list v_arg_list;                           
    va_start(v_arg_list, msg);                 
    vsnprintf(str_tmp, MAXLEN, msg, v_arg_list);  
    va_end(v_arg_list); 
    PyObject * log_function = PyObject_GetAttrString(reinterpret_cast<PyObject*>(self), "log");
    if(NULL != log_function || 1 == PyCallable_Check(log_function))
    { 
        PyObject * args= PyTuple_New(2);
        PyTuple_SetItem(args, 0, Py_BuildValue("s", type));
        PyTuple_SetItem(args, 1, Py_BuildValue("s", str_tmp));
        PyObject_CallObject(log_function, args);
        Py_DECREF(args);
    }
    else
        std::cerr<<"Find log fail or log is not callable at "<<__FILE__<<":"<<__LINE__<<std::endl;
    Py_XDECREF(log_function);
}

void pylog(MODULE_NAME * self, PyObject * args, PyObject * kwds)
{
    const char * type = NULL, * msg = NULL;
    if(PyArg_ParseTuple(args, "ss", &type, &msg))
    {
        if(NULL != type && NULL != msg)
            std::cerr<<"Default log:("<<type<<')'<<msg<<'['<<__FILE__<<':'<<__LINE__<<']'<<std::endl;
    }
    else
        std::cerr<<"PyArg_ParseTuple error at "<<__FILE__<<":"<<__LINE__<<std::endl;
}

