
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemcpyToArray)(cudaArray_t, size_t, size_t, const void *, size_t, enum cudaMemcpyKind);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemcpyToArray(cudaArray_t dst, size_t wOffset, size_t hOffset, const void *src, size_t count, enum cudaMemcpyKind kind) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemcpyToArray)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemcpyToArray = (cudaError_t (*)(cudaArray_t, size_t, size_t, const void *, size_t, enum cudaMemcpyKind)) dlsym(libcudart_handle, "cudaMemcpyToArray");
			fprintf(stderr, "cudaMemcpyToArray:%p\n", wrapper_cudaMemcpyToArray);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemcpyToArray():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemcpyToArray(dst, wOffset, hOffset, src, count, kind);
		return retval;
	}
}

