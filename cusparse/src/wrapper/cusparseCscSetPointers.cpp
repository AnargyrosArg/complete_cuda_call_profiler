#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCscSetPointers(cusparseSpMatDescr_t spMatDescr, void *cscColOffsets, void *cscRowInd, void *cscValues)
{
	cusparseStatus_t retval = cusparseCscSetPointers(spMatDescr, cscColOffsets, cscRowInd, cscValues);
	return retval;
}