
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemcpy2DFromArrayAsync)(void *, size_t, cudaArray_const_t, size_t, size_t, size_t, size_t, enum cudaMemcpyKind, cudaStream_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemcpy2DFromArrayAsync(void *dst, size_t dpitch, cudaArray_const_t src, size_t wOffset, size_t hOffset, size_t width, size_t height, enum cudaMemcpyKind kind, cudaStream_t stream) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemcpy2DFromArrayAsync)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemcpy2DFromArrayAsync = (cudaError_t (*)(void *, size_t, cudaArray_const_t, size_t, size_t, size_t, size_t, enum cudaMemcpyKind, cudaStream_t)) dlsym(libcudart_handle, "cudaMemcpy2DFromArrayAsync");
			fprintf(stderr, "cudaMemcpy2DFromArrayAsync:%p\n", wrapper_cudaMemcpy2DFromArrayAsync);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemcpy2DFromArrayAsync():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemcpy2DFromArrayAsync(dst, dpitch, src, wOffset, hOffset, width, height, kind, stream);
		return retval;
	}
}

