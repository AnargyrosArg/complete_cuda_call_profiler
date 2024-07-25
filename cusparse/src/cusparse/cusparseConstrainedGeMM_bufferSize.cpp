#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseConstrainedGeMM_bufferSize)(cusparseHandle_t, cusparseOperation_t, cusparseOperation_t, const void *, cusparseDnMatDescr_t, cusparseDnMatDescr_t, const void *, cusparseSpMatDescr_t, cudaDataType, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseConstrainedGeMM_bufferSize(cusparseHandle_t handle, cusparseOperation_t opA, cusparseOperation_t opB, const void *alpha, cusparseDnMatDescr_t matA, cusparseDnMatDescr_t matB, const void *beta, cusparseSpMatDescr_t matC, cudaDataType computeType, size_t *bufferSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseConstrainedGeMM_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseConstrainedGeMM_bufferSize = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, cusparseOperation_t, const void *, cusparseDnMatDescr_t, cusparseDnMatDescr_t, const void *, cusparseSpMatDescr_t, cudaDataType, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseConstrainedGeMM_bufferSize");
			fprintf(stderr, "wrapper_cusparseConstrainedGeMM_bufferSize:%p\n", wrapper_cusparseConstrainedGeMM_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseConstrainedGeMM_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseConstrainedGeMM_bufferSize(handle, opA, opB, alpha, matA, matB, beta, matC, computeType, bufferSize);
		return retval;
	}
}