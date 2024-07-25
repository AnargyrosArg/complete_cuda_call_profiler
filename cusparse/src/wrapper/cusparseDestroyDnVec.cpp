#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDestroyDnVec(cusparseDnVecDescr_t dnVecDescr)
{
	cusparseStatus_t retval = cusparseDestroyDnVec(dnVecDescr);
	return retval;
}