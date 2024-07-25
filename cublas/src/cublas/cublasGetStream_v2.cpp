#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasGetStream_v2)(cublasHandle_t, cudaStream_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasGetStream_v2(cublasHandle_t handle, cudaStream_t *streamId) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasGetStream_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasGetStream_v2 = (cublasStatus_t (*)(cublasHandle_t, cudaStream_t *)) dlsym(libwrapper_handle, "wrapper_cublasGetStream_v2");
			fprintf(stderr, "wrapper_cublasGetStream_v2:%p\n", wrapper_cublasGetStream_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasGetStream_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasGetStream_v2(handle, streamId);
		return retval;
	}
}