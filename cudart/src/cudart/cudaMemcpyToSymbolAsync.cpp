
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemcpyToSymbolAsync)(const void *, const void *, size_t, size_t, enum cudaMemcpyKind, cudaStream_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemcpyToSymbolAsync(const void *symbol, const void *src, size_t count, size_t offset, enum cudaMemcpyKind kind, cudaStream_t stream) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemcpyToSymbolAsync)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemcpyToSymbolAsync = (cudaError_t (*)(const void *, const void *, size_t, size_t, enum cudaMemcpyKind, cudaStream_t)) dlsym(libcudart_handle, "cudaMemcpyToSymbolAsync");
			fprintf(stderr, "cudaMemcpyToSymbolAsync:%p\n", wrapper_cudaMemcpyToSymbolAsync);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemcpyToSymbolAsync():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemcpyToSymbolAsync(symbol, src, count, offset, kind, stream);
		return retval;
	}
}

