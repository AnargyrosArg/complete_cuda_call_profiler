#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpSV_bufferSize(cusparseHandle_t handle, cusparseOperation_t opA, const void *alpha, cusparseSpMatDescr_t matA, cusparseDnVecDescr_t vecX, cusparseDnVecDescr_t vecY, cudaDataType computeType, cusparseSpSVAlg_t alg, cusparseSpSVDescr_t spsvDescr, size_t *bufferSize)
{
	cusparseStatus_t retval = cusparseSpSV_bufferSize(handle, opA, alpha, matA, vecX, vecY, computeType, alg, spsvDescr, bufferSize);
	return retval;
}