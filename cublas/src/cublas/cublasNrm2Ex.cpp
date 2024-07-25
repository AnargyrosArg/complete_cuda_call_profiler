#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasNrm2Ex)(cublasHandle_t, int, const void *, cudaDataType, int, void *, cudaDataType, cudaDataType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasNrm2Ex(cublasHandle_t handle, int n, const void *x, cudaDataType xType, int incx, void *result, cudaDataType resultType, cudaDataType executionType) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasNrm2Ex)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasNrm2Ex = (cublasStatus_t (*)(cublasHandle_t, int, const void *, cudaDataType, int, void *, cudaDataType, cudaDataType)) dlsym(libwrapper_handle, "wrapper_cublasNrm2Ex");
			fprintf(stderr, "wrapper_cublasNrm2Ex:%p\n", wrapper_cublasNrm2Ex);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasNrm2Ex():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasNrm2Ex(handle, n, x, xType, incx, result, resultType, executionType);
		return retval;
	}
}