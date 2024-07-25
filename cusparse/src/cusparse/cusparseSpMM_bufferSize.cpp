#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpMM_bufferSize)(cusparseHandle_t, cusparseOperation_t, cusparseOperation_t, const void *, cusparseSpMatDescr_t, cusparseDnMatDescr_t, const void *, cusparseDnMatDescr_t, cudaDataType, cusparseSpMMAlg_t, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpMM_bufferSize(cusparseHandle_t handle, cusparseOperation_t opA, cusparseOperation_t opB, const void *alpha, cusparseSpMatDescr_t matA, cusparseDnMatDescr_t matB, const void *beta, cusparseDnMatDescr_t matC, cudaDataType computeType, cusparseSpMMAlg_t alg, size_t *bufferSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpMM_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpMM_bufferSize = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, cusparseOperation_t, const void *, cusparseSpMatDescr_t, cusparseDnMatDescr_t, const void *, cusparseDnMatDescr_t, cudaDataType, cusparseSpMMAlg_t, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpMM_bufferSize");
			fprintf(stderr, "wrapper_cusparseSpMM_bufferSize:%p\n", wrapper_cusparseSpMM_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpMM_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpMM_bufferSize(handle, opA, opB, alpha, matA, matB, beta, matC, computeType, alg, bufferSize);
		return retval;
	}
}