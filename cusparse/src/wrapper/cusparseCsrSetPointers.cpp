#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCsrSetPointers(cusparseSpMatDescr_t spMatDescr, void *csrRowOffsets, void *csrColInd, void *csrValues)
{
	cusparseStatus_t retval = cusparseCsrSetPointers(spMatDescr, csrRowOffsets, csrColInd, csrValues);
	return retval;
}