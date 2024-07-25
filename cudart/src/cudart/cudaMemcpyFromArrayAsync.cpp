
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemcpyFromArrayAsync)(void *, cudaArray_const_t, size_t, size_t, size_t, enum cudaMemcpyKind, cudaStream_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemcpyFromArrayAsync(void *dst, cudaArray_const_t src, size_t wOffset, size_t hOffset, size_t count, enum cudaMemcpyKind kind, cudaStream_t stream) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemcpyFromArrayAsync)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemcpyFromArrayAsync = (cudaError_t (*)(void *, cudaArray_const_t, size_t, size_t, size_t, enum cudaMemcpyKind, cudaStream_t)) dlsym(libcudart_handle, "cudaMemcpyFromArrayAsync");
			fprintf(stderr, "cudaMemcpyFromArrayAsync:%p\n", wrapper_cudaMemcpyFromArrayAsync);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemcpyFromArrayAsync():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemcpyFromArrayAsync(dst, src, wOffset, hOffset, count, kind, stream);
		return retval;
	}
}

