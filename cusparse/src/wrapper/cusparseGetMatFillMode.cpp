#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseFillMode_t wrapper_cusparseGetMatFillMode(const cusparseMatDescr_t descrA)
{
	cusparseFillMode_t retval = cusparseGetMatFillMode(descrA);
	return retval;
}