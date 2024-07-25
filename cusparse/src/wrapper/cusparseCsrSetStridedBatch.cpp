#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCsrSetStridedBatch(cusparseSpMatDescr_t spMatDescr, int batchCount, int64_t offsetsBatchStride, int64_t columnsValuesBatchStride)
{
	cusparseStatus_t retval = cusparseCsrSetStridedBatch(spMatDescr, batchCount, offsetsBatchStride, columnsValuesBatchStride);
	return retval;
}