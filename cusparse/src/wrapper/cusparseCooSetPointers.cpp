#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCooSetPointers(cusparseSpMatDescr_t spMatDescr, void *cooRows, void *cooColumns, void *cooValues)
{
	cusparseStatus_t retval = cusparseCooSetPointers(spMatDescr, cooRows, cooColumns, cooValues);
	return retval;
}