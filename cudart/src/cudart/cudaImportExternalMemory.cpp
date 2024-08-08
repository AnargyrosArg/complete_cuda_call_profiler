
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaImportExternalMemory)(cudaExternalMemory_t *, const struct cudaExternalMemoryHandleDesc *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaImportExternalMemory(cudaExternalMemory_t *extMem_out, const struct cudaExternalMemoryHandleDesc *memHandleDesc) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaImportExternalMemory)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaImportExternalMemory = (cudaError_t (*)(cudaExternalMemory_t *, const struct cudaExternalMemoryHandleDesc *)) dlsym(libcudart_handle, "cudaImportExternalMemory");
			fprintf(stderr, "cudaImportExternalMemory:%p\n", wrapper_cudaImportExternalMemory);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaImportExternalMemory():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaImportExternalMemory(extMem_out, memHandleDesc);
		return retval;
	}
}

