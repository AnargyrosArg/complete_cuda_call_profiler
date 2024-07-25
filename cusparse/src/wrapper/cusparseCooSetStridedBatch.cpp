#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCooSetStridedBatch(cusparseSpMatDescr_t spMatDescr, int batchCount, int64_t batchStride)
{
	cusparseStatus_t retval = cusparseCooSetStridedBatch(spMatDescr, batchCount, batchStride);
	return retval;
}