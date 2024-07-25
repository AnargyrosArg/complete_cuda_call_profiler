#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasGetVectorAsync)(int, int, const void *, int, void *, int, cudaStream_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasGetVectorAsync(int n, int elemSize, const void *devicePtr, int incx, void *hostPtr, int incy, cudaStream_t stream) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasGetVectorAsync)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasGetVectorAsync = (cublasStatus_t (*)(int, int, const void *, int, void *, int, cudaStream_t)) dlsym(libwrapper_handle, "wrapper_cublasGetVectorAsync");
			fprintf(stderr, "wrapper_cublasGetVectorAsync:%p\n", wrapper_cublasGetVectorAsync);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasGetVectorAsync():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasGetVectorAsync(n, elemSize, devicePtr, incx, hostPtr, incy, stream);
		return retval;
	}
}