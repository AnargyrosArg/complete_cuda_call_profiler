
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemcpy2D)(void *, size_t, const void *, size_t, size_t, size_t, enum cudaMemcpyKind);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemcpy2D(void *dst, size_t dpitch, const void *src, size_t spitch, size_t width, size_t height, enum cudaMemcpyKind kind) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemcpy2D)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemcpy2D = (cudaError_t (*)(void *, size_t, const void *, size_t, size_t, size_t, enum cudaMemcpyKind)) dlsym(libcudart_handle, "cudaMemcpy2D");
			fprintf(stderr, "cudaMemcpy2D:%p\n", wrapper_cudaMemcpy2D);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemcpy2D():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemcpy2D(dst, dpitch, src, spitch, width, height, kind);
		return retval;
	}
}

