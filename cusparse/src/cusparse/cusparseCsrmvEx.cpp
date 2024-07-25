#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCsrmvEx)(cusparseHandle_t, cusparseAlgMode_t, cusparseOperation_t, int, int, int, const void *, cudaDataType, const cusparseMatDescr_t, const void *, cudaDataType, const int *, const int *, const void *, cudaDataType, const void *, cudaDataType, void *, cudaDataType, cudaDataType, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCsrmvEx(cusparseHandle_t handle, cusparseAlgMode_t alg, cusparseOperation_t transA, int m, int n, int nnz, const void *alpha, cudaDataType alphatype, const cusparseMatDescr_t descrA, const void *csrValA, cudaDataType csrValAtype, const int *csrRowPtrA, const int *csrColIndA, const void *x, cudaDataType xtype, const void *beta, cudaDataType betatype, void *y, cudaDataType ytype, cudaDataType executiontype, void *buffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCsrmvEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCsrmvEx = (cusparseStatus_t (*)(cusparseHandle_t, cusparseAlgMode_t, cusparseOperation_t, int, int, int, const void *, cudaDataType, const cusparseMatDescr_t, const void *, cudaDataType, const int *, const int *, const void *, cudaDataType, const void *, cudaDataType, void *, cudaDataType, cudaDataType, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCsrmvEx");
			fprintf(stderr, "wrapper_cusparseCsrmvEx:%p\n", wrapper_cusparseCsrmvEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCsrmvEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCsrmvEx(handle, alg, transA, m, n, nnz, alpha, alphatype, descrA, csrValA, csrValAtype, csrRowPtrA, csrColIndA, x, xtype, beta, betatype, y, ytype, executiontype, buffer);
		return retval;
	}
}