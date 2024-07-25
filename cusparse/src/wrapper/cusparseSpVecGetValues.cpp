#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpVecGetValues(cusparseSpVecDescr_t spVecDescr, void **values)
{
	cusparseStatus_t retval = cusparseSpVecGetValues(spVecDescr, values);
	return retval;
}