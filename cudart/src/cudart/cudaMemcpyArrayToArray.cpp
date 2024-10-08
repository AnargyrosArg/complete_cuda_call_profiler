
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemcpyArrayToArray)(cudaArray_t, size_t, size_t, cudaArray_const_t, size_t, size_t, size_t, enum cudaMemcpyKind);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemcpyArrayToArray(cudaArray_t dst, size_t wOffsetDst, size_t hOffsetDst, cudaArray_const_t src, size_t wOffsetSrc, size_t hOffsetSrc, size_t count, enum cudaMemcpyKind kind) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemcpyArrayToArray)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemcpyArrayToArray = (cudaError_t (*)(cudaArray_t, size_t, size_t, cudaArray_const_t, size_t, size_t, size_t, enum cudaMemcpyKind)) dlsym(libcudart_handle, "cudaMemcpyArrayToArray");
			fprintf(stderr, "cudaMemcpyArrayToArray:%p\n", wrapper_cudaMemcpyArrayToArray);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemcpyArrayToArray():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemcpyArrayToArray(dst, wOffsetDst, hOffsetDst, src, wOffsetSrc, hOffsetSrc, count, kind);
		return retval;
	}
}

