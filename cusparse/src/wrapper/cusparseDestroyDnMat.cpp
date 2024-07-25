#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDestroyDnMat(cusparseDnMatDescr_t dnMatDescr)
{
	cusparseStatus_t retval = cusparseDestroyDnMat(dnMatDescr);
	return retval;
}