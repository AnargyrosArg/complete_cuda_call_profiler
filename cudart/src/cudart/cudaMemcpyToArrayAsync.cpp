
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemcpyToArrayAsync)(cudaArray_t, size_t, size_t, const void *, size_t, enum cudaMemcpyKind, cudaStream_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemcpyToArrayAsync(cudaArray_t dst, size_t wOffset, size_t hOffset, const void *src, size_t count, enum cudaMemcpyKind kind, cudaStream_t stream) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemcpyToArrayAsync)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemcpyToArrayAsync = (cudaError_t (*)(cudaArray_t, size_t, size_t, const void *, size_t, enum cudaMemcpyKind, cudaStream_t)) dlsym(libcudart_handle, "cudaMemcpyToArrayAsync");
			fprintf(stderr, "cudaMemcpyToArrayAsync:%p\n", wrapper_cudaMemcpyToArrayAsync);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemcpyToArrayAsync():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemcpyToArrayAsync(dst, wOffset, hOffset, src, count, kind, stream);
		return retval;
	}
}

