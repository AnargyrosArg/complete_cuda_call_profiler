
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemcpyAsync)(void *, const void *, size_t, enum cudaMemcpyKind, cudaStream_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemcpyAsync(void *dst, const void *src, size_t count, enum cudaMemcpyKind kind, cudaStream_t stream) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemcpyAsync)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemcpyAsync = (cudaError_t (*)(void *, const void *, size_t, enum cudaMemcpyKind, cudaStream_t)) dlsym(libcudart_handle, "cudaMemcpyAsync");
			fprintf(stderr, "cudaMemcpyAsync:%p\n", wrapper_cudaMemcpyAsync);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemcpyAsync():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemcpyAsync(dst, src, count, kind, stream);
		return retval;
	}
}

