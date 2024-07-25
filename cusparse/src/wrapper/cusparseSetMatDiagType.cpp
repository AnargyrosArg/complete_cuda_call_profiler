#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSetMatDiagType(cusparseMatDescr_t descrA, cusparseDiagType_t diagType)
{
	cusparseStatus_t retval = cusparseSetMatDiagType(descrA, diagType);
	return retval;
}