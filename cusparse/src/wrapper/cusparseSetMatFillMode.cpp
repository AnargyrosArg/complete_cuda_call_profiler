#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSetMatFillMode(cusparseMatDescr_t descrA, cusparseFillMode_t fillMode)
{
	cusparseStatus_t retval = cusparseSetMatFillMode(descrA, fillMode);
	return retval;
}