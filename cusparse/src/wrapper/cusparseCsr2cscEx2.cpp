#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCsr2cscEx2(cusparseHandle_t handle, int m, int n, int nnz, const void *csrVal, const int *csrRowPtr, const int *csrColInd, void *cscVal, int *cscColPtr, int *cscRowInd, cudaDataType valType, cusparseAction_t copyValues, cusparseIndexBase_t idxBase, cusparseCsr2CscAlg_t alg, void *buffer)
{
	cusparseStatus_t retval = cusparseCsr2cscEx2(handle, m, n, nnz, csrVal, csrRowPtr, csrColInd, cscVal, cscColPtr, cscRowInd, valType, copyValues, idxBase, alg, buffer);
	return retval;
}