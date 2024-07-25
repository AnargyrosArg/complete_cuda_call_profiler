#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDnMatSetStridedBatch(cusparseDnMatDescr_t dnMatDescr, int batchCount, int64_t batchStride)
{
	cusparseStatus_t retval = cusparseDnMatSetStridedBatch(dnMatDescr, batchCount, batchStride);
	return retval;
}