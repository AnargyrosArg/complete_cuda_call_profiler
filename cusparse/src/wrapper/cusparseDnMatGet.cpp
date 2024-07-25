#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDnMatGet(cusparseDnMatDescr_t dnMatDescr, int64_t *rows, int64_t *cols, int64_t *ld, void **values, cudaDataType *type, cusparseOrder_t *order)
{
	cusparseStatus_t retval = cusparseDnMatGet(dnMatDescr, rows, cols, ld, values, type, order);
	return retval;
}