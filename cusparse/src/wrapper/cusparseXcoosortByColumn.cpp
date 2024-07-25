#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseXcoosortByColumn(cusparseHandle_t handle, int m, int n, int nnz, int *cooRowsA, int *cooColsA, int *P, void *pBuffer)
{
	cusparseStatus_t retval = cusparseXcoosortByColumn(handle, m, n, nnz, cooRowsA, cooColsA, P, pBuffer);
	return retval;
}