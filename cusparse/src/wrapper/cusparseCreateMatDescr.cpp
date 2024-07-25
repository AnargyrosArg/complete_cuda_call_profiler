#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCreateMatDescr(cusparseMatDescr_t *descrA)
{
	cusparseStatus_t retval = cusparseCreateMatDescr(descrA);
	return retval;
}