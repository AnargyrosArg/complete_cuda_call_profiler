#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSetVectorAsync)(int, int, const void *, int, void *, int, cudaStream_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSetVectorAsync(int n, int elemSize, const void *hostPtr, int incx, void *devicePtr, int incy, cudaStream_t stream) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSetVectorAsync)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSetVectorAsync = (cublasStatus_t (*)(int, int, const void *, int, void *, int, cudaStream_t)) dlsym(libwrapper_handle, "wrapper_cublasSetVectorAsync");
			fprintf(stderr, "wrapper_cublasSetVectorAsync:%p\n", wrapper_cublasSetVectorAsync);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSetVectorAsync():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSetVectorAsync(n, elemSize, hostPtr, incx, devicePtr, incy, stream);
		return retval;
	}
}