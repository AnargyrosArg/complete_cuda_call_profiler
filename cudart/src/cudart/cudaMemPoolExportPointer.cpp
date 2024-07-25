
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemPoolExportPointer)(struct cudaMemPoolPtrExportData *, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemPoolExportPointer(struct cudaMemPoolPtrExportData *exportData, void *ptr) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemPoolExportPointer)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemPoolExportPointer = (cudaError_t (*)(struct cudaMemPoolPtrExportData *, void *)) dlsym(libcudart_handle, "cudaMemPoolExportPointer");
			fprintf(stderr, "cudaMemPoolExportPointer:%p\n", wrapper_cudaMemPoolExportPointer);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemPoolExportPointer():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemPoolExportPointer(exportData, ptr);
		return retval;
	}
}

