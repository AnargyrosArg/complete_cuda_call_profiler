#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSetMatIndexBase(cusparseMatDescr_t descrA, cusparseIndexBase_t base)
{
	cusparseStatus_t retval = cusparseSetMatIndexBase(descrA, base);
	return retval;
}