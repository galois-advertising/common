#include <stdarg.h>
#include "python_bind.h"

void throw_exception(const char * msg, ...)
{
    char str_tmp[PYTHON_LOG_MAXLEN];
    va_list v_arg_list;
    va_start(v_arg_list, msg);                 
    vsnprintf(str_tmp, PYTHON_LOG_MAXLEN, msg, v_arg_list);  
    va_end(v_arg_list); 
    PyErr_SetString(PyExc_RuntimeError, str_tmp);
}
