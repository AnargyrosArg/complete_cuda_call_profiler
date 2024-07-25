#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpMatGetStridedBatch(cusparseSpMatDescr_t spMatDescr, int *batchCount)
{
	cusparseStatus_t retval = cusparseSpMatGetStridedBatch(spMatDescr, batchCount);
	return retval;
}