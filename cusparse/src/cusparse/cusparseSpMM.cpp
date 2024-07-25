#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpMM)(cusparseHandle_t, cusparseOperation_t, cusparseOperation_t, const void *, cusparseSpMatDescr_t, cusparseDnMatDescr_t, const void *, cusparseDnMatDescr_t, cudaDataType, cusparseSpMMAlg_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpMM(cusparseHandle_t handle, cusparseOperation_t opA, cusparseOperation_t opB, const void *alpha, cusparseSpMatDescr_t matA, cusparseDnMatDescr_t matB, const void *beta, cusparseDnMatDescr_t matC, cudaDataType computeType, cusparseSpMMAlg_t alg, void *externalBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpMM)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpMM = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, cusparseOperation_t, const void *, cusparseSpMatDescr_t, cusparseDnMatDescr_t, const void *, cusparseDnMatDescr_t, cudaDataType, cusparseSpMMAlg_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpMM");
			fprintf(stderr, "wrapper_cusparseSpMM:%p\n", wrapper_cusparseSpMM);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpMM():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpMM(handle, opA, opB, alpha, matA, matB, beta, matC, computeType, alg, externalBuffer);
		return retval;
	}
}