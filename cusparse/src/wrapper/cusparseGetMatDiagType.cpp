#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseDiagType_t wrapper_cusparseGetMatDiagType(const cusparseMatDescr_t descrA)
{
	cusparseDiagType_t retval = cusparseGetMatDiagType(descrA);
	return retval;
}