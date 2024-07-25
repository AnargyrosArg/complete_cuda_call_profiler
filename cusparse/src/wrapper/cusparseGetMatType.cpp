#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseMatrixType_t wrapper_cusparseGetMatType(const cusparseMatDescr_t descrA)
{
	cusparseMatrixType_t retval = cusparseGetMatType(descrA);
	return retval;
}