#pragma once
#include <iostream>
#include <Python.h>

#define _COMB(a, b) #a"."#b
#define COMB(a, b) _COMB(a, b)
#define _STR(a) #a
#define STR(a) _STR(a)
#define _JOIN(a, b) a##b
#define JOIN(a, b) _JOIN(a, b)
#define PYTHON_LOG_MAXLEN 4096

template<class T>
void _log(T * self, const char * type, const char * msg, ...) {
    char str_tmp[PYTHON_LOG_MAXLEN];
    va_list v_arg_list;                           
    va_start(v_arg_list, msg);                 
    vsnprintf(str_tmp, PYTHON_LOG_MAXLEN, msg, v_arg_list);  
    va_end(v_arg_list); 
    auto log_function = PyObject_GetAttrString(reinterpret_cast<PyObject*>(self), "log");
    if (nullptr != log_function || 1 == PyCallable_Check(log_function)) { 
        auto args= PyTuple_New(2);
        PyTuple_SetItem(args, 0, Py_BuildValue("s", type));
        PyTuple_SetItem(args, 1, Py_BuildValue("s", str_tmp));
        PyObject_CallObject(log_function, args);
        Py_DECREF(args);
    } else {
        std::cerr<<"["__FILE__<<":"<<__LINE__<<"] fails."<<std::endl;
    }
    Py_XDECREF(log_function);
}

template<class T>
void pylog(T * self, PyObject * args, PyObject * kwds)
{
    const char * type = nullptr, * msg = nullptr;
    if (PyArg_ParseTuple(args, "ss", &type, &msg)) {
        if(nullptr != type && nullptr != msg) {
            std::cerr<<'['<<__FILE__<<':'<<__LINE__<<']'<<"Default log:("<<type<<')'<<msg<<std::endl;
        }
    } else {
        std::cerr<<"["<<__FILE__<<":"<<__LINE__<<"] fails."<<std::endl;
    }
}