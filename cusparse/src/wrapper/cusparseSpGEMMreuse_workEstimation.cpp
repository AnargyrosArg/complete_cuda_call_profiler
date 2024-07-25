#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpGEMMreuse_workEstimation(cusparseHandle_t handle, cusparseOperation_t opA, cusparseOperation_t opB, cusparseSpMatDescr_t matA, cusparseSpMatDescr_t matB, cusparseSpMatDescr_t matC, cusparseSpGEMMAlg_t alg, cusparseSpGEMMDescr_t spgemmDescr, size_t *bufferSize1, void *externalBuffer1)
{
	cusparseStatus_t retval = cusparseSpGEMMreuse_workEstimation(handle, opA, opB, matA, matB, matC, alg, spgemmDescr, bufferSize1, externalBuffer1);
	return retval;
}