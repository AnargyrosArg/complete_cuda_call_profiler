
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemcpyFromArray)(void *, cudaArray_const_t, size_t, size_t, size_t, enum cudaMemcpyKind);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemcpyFromArray(void *dst, cudaArray_const_t src, size_t wOffset, size_t hOffset, size_t count, enum cudaMemcpyKind kind) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemcpyFromArray)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemcpyFromArray = (cudaError_t (*)(void *, cudaArray_const_t, size_t, size_t, size_t, enum cudaMemcpyKind)) dlsym(libcudart_handle, "cudaMemcpyFromArray");
			fprintf(stderr, "cudaMemcpyFromArray:%p\n", wrapper_cudaMemcpyFromArray);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemcpyFromArray():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemcpyFromArray(dst, src, wOffset, hOffset, count, kind);
		return retval;
	}
}

