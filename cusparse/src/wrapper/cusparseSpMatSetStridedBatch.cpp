#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpMatSetStridedBatch(cusparseSpMatDescr_t spMatDescr, int batchCount)
{
	cusparseStatus_t retval = cusparseSpMatSetStridedBatch(spMatDescr, batchCount);
	return retval;
}