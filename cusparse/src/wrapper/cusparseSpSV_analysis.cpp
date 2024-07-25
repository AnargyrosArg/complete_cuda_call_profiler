#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpSV_analysis(cusparseHandle_t handle, cusparseOperation_t opA, const void *alpha, cusparseSpMatDescr_t matA, cusparseDnVecDescr_t vecX, cusparseDnVecDescr_t vecY, cudaDataType computeType, cusparseSpSVAlg_t alg, cusparseSpSVDescr_t spsvDescr, void *externalBuffer)
{
	cusparseStatus_t retval = cusparseSpSV_analysis(handle, opA, alpha, matA, vecX, vecY, computeType, alg, spsvDescr, externalBuffer);
	return retval;
}