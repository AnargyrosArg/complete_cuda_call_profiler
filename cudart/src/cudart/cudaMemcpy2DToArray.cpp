
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemcpy2DToArray)(cudaArray_t, size_t, size_t, const void *, size_t, size_t, size_t, enum cudaMemcpyKind);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemcpy2DToArray(cudaArray_t dst, size_t wOffset, size_t hOffset, const void *src, size_t spitch, size_t width, size_t height, enum cudaMemcpyKind kind) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemcpy2DToArray)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemcpy2DToArray = (cudaError_t (*)(cudaArray_t, size_t, size_t, const void *, size_t, size_t, size_t, enum cudaMemcpyKind)) dlsym(libcudart_handle, "cudaMemcpy2DToArray");
			fprintf(stderr, "cudaMemcpy2DToArray:%p\n", wrapper_cudaMemcpy2DToArray);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemcpy2DToArray():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemcpy2DToArray(dst, wOffset, hOffset, src, spitch, width, height, kind);
		return retval;
	}
}
