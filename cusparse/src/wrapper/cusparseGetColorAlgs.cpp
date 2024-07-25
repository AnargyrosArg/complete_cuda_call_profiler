#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseGetColorAlgs(cusparseColorInfo_t info, cusparseColorAlg_t *alg)
{
	cusparseStatus_t retval = cusparseGetColorAlgs(info, alg);
	return retval;
}