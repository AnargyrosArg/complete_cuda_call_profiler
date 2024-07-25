#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpGEMM_destroyDescr(cusparseSpGEMMDescr_t descr)
{
	cusparseStatus_t retval = cusparseSpGEMM_destroyDescr(descr);
	return retval;
}