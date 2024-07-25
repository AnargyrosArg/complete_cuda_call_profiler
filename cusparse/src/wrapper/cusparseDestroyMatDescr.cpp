#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDestroyMatDescr(cusparseMatDescr_t descrA)
{
	cusparseStatus_t retval = cusparseDestroyMatDescr(descrA);
	return retval;
}