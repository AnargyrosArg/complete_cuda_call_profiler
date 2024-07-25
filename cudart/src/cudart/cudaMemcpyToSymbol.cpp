
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemcpyToSymbol)(const void *, const void *, size_t, size_t, enum cudaMemcpyKind);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemcpyToSymbol(const void *symbol, const void *src, size_t count, size_t offset, enum cudaMemcpyKind kind) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemcpyToSymbol)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemcpyToSymbol = (cudaError_t (*)(const void *, const void *, size_t, size_t, enum cudaMemcpyKind)) dlsym(libcudart_handle, "cudaMemcpyToSymbol");
			fprintf(stderr, "cudaMemcpyToSymbol:%p\n", wrapper_cudaMemcpyToSymbol);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemcpyToSymbol():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemcpyToSymbol(symbol, src, count, offset, kind);
		return retval;
	}
}

