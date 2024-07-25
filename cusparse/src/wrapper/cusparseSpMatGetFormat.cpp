#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpMatGetFormat(cusparseSpMatDescr_t spMatDescr, cusparseFormat_t *format)
{
	cusparseStatus_t retval = cusparseSpMatGetFormat(spMatDescr, format);
	return retval;
}