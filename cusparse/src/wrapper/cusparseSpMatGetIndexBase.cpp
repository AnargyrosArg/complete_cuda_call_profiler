#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpMatGetIndexBase(cusparseSpMatDescr_t spMatDescr, cusparseIndexBase_t *idxBase)
{
	cusparseStatus_t retval = cusparseSpMatGetIndexBase(spMatDescr, idxBase);
	return retval;
}