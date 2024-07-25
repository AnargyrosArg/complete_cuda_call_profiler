#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpGEMMreuse_copy(cusparseHandle_t handle, cusparseOperation_t opA, cusparseOperation_t opB, cusparseSpMatDescr_t matA, cusparseSpMatDescr_t matB, cusparseSpMatDescr_t matC, cusparseSpGEMMAlg_t alg, cusparseSpGEMMDescr_t spgemmDescr, size_t *bufferSize5, void *externalBuffer5)
{
	cusparseStatus_t retval = cusparseSpGEMMreuse_copy(handle, opA, opB, matA, matB, matC, alg, spgemmDescr, bufferSize5, externalBuffer5);
	return retval;
}