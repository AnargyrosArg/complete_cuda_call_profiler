#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDnMatGetValues(cusparseDnMatDescr_t dnMatDescr, void **values)
{
	cusparseStatus_t retval = cusparseDnMatGetValues(dnMatDescr, values);
	return retval;
}