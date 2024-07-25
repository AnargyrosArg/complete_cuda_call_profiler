#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSetMatType(cusparseMatDescr_t descrA, cusparseMatrixType_t type)
{
	cusparseStatus_t retval = cusparseSetMatType(descrA, type);
	return retval;
}