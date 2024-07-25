
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaLaunchHostFunc)(cudaStream_t, cudaHostFn_t, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaLaunchHostFunc(cudaStream_t stream, cudaHostFn_t fn, void *userData) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaLaunchHostFunc)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaLaunchHostFunc = (cudaError_t (*)(cudaStream_t, cudaHostFn_t, void *)) dlsym(libcudart_handle, "cudaLaunchHostFunc");
			fprintf(stderr, "cudaLaunchHostFunc:%p\n", wrapper_cudaLaunchHostFunc);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaLaunchHostFunc():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaLaunchHostFunc(stream, fn, userData);
		return retval;
	}
}

