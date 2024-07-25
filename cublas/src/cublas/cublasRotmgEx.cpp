#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasRotmgEx)(cublasHandle_t, void *, cudaDataType, void *, cudaDataType, void *, cudaDataType, const void *, cudaDataType, void *, cudaDataType, cudaDataType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasRotmgEx(cublasHandle_t handle, void *d1, cudaDataType d1Type, void *d2, cudaDataType d2Type, void *x1, cudaDataType x1Type, const void *y1, cudaDataType y1Type, void *param, cudaDataType paramType, cudaDataType executiontype) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasRotmgEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasRotmgEx = (cublasStatus_t (*)(cublasHandle_t, void *, cudaDataType, void *, cudaDataType, void *, cudaDataType, const void *, cudaDataType, void *, cudaDataType, cudaDataType)) dlsym(libwrapper_handle, "wrapper_cublasRotmgEx");
			fprintf(stderr, "wrapper_cublasRotmgEx:%p\n", wrapper_cublasRotmgEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasRotmgEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasRotmgEx(handle, d1, d1Type, d2, d2Type, x1, x1Type, y1, y1Type, param, paramType, executiontype);
		return retval;
	}
}