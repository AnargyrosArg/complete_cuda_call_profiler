
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaExternalMemoryGetMappedBuffer)(void **, cudaExternalMemory_t, const struct cudaExternalMemoryBufferDesc *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaExternalMemoryGetMappedBuffer(void **devPtr, cudaExternalMemory_t extMem, const struct cudaExternalMemoryBufferDesc *bufferDesc) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaExternalMemoryGetMappedBuffer)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaExternalMemoryGetMappedBuffer = (cudaError_t (*)(void **, cudaExternalMemory_t, const struct cudaExternalMemoryBufferDesc *)) dlsym(libcudart_handle, "cudaExternalMemoryGetMappedBuffer");
			fprintf(stderr, "cudaExternalMemoryGetMappedBuffer:%p\n", wrapper_cudaExternalMemoryGetMappedBuffer);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaExternalMemoryGetMappedBuffer():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaExternalMemoryGetMappedBuffer(devPtr, extMem, bufferDesc);
		return retval;
	}
}

