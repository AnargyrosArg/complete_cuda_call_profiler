#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCsrmvEx(cusparseHandle_t handle, cusparseAlgMode_t alg, cusparseOperation_t transA, int m, int n, int nnz, const void *alpha, cudaDataType alphatype, const cusparseMatDescr_t descrA, const void *csrValA, cudaDataType csrValAtype, const int *csrRowPtrA, const int *csrColIndA, const void *x, cudaDataType xtype, const void *beta, cudaDataType betatype, void *y, cudaDataType ytype, cudaDataType executiontype, void *buffer)
{
	cusparseStatus_t retval = cusparseCsrmvEx(handle, alg, transA, m, n, nnz, alpha, alphatype, descrA, csrValA, csrValAtype, csrRowPtrA, csrColIndA, x, xtype, beta, betatype, y, ytype, executiontype, buffer);
	return retval;
}