
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemPoolImportPointer)(void **, cudaMemPool_t, struct cudaMemPoolPtrExportData *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemPoolImportPointer(void **ptr, cudaMemPool_t memPool, struct cudaMemPoolPtrExportData *exportData) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemPoolImportPointer)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemPoolImportPointer = (cudaError_t (*)(void **, cudaMemPool_t, struct cudaMemPoolPtrExportData *)) dlsym(libcudart_handle, "cudaMemPoolImportPointer");
			fprintf(stderr, "cudaMemPoolImportPointer:%p\n", wrapper_cudaMemPoolImportPointer);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemPoolImportPointer():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemPoolImportPointer(ptr, memPool, exportData);
		return retval;
	}
}

