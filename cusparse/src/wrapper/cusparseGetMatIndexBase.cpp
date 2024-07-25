#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseIndexBase_t wrapper_cusparseGetMatIndexBase(const cusparseMatDescr_t descrA)
{
	cusparseIndexBase_t retval = cusparseGetMatIndexBase(descrA);
	return retval;
}