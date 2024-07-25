#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCreateDnMat(cusparseDnMatDescr_t *dnMatDescr, int64_t rows, int64_t cols, int64_t ld, void *values, cudaDataType valueType, cusparseOrder_t order)
{
	cusparseStatus_t retval = cusparseCreateDnMat(dnMatDescr, rows, cols, ld, values, valueType, order);
	return retval;
}