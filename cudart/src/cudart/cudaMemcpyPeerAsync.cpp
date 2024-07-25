
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemcpyPeerAsync)(void *, int, const void *, int, size_t, cudaStream_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemcpyPeerAsync(void *dst, int dstDevice, const void *src, int srcDevice, size_t count, cudaStream_t stream) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemcpyPeerAsync)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemcpyPeerAsync = (cudaError_t (*)(void *, int, const void *, int, size_t, cudaStream_t)) dlsym(libcudart_handle, "cudaMemcpyPeerAsync");
			fprintf(stderr, "cudaMemcpyPeerAsync:%p\n", wrapper_cudaMemcpyPeerAsync);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemcpyPeerAsync():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemcpyPeerAsync(dst, dstDevice, src, srcDevice, count, stream);
		return retval;
	}
}

