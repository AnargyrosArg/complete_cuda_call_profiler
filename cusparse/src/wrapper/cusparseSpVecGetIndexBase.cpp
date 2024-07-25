#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpVecGetIndexBase(cusparseSpVecDescr_t spVecDescr, cusparseIndexBase_t *idxBase)
{
	cusparseStatus_t retval = cusparseSpVecGetIndexBase(spVecDescr, idxBase);
	return retval;
}