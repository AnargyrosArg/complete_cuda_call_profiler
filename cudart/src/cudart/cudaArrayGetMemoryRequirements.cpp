
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaArrayGetMemoryRequirements)(struct cudaArrayMemoryRequirements *, cudaArray_t, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaArrayGetMemoryRequirements(struct cudaArrayMemoryRequirements *memoryRequirements, cudaArray_t array, int device) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaArrayGetMemoryRequirements)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaArrayGetMemoryRequirements = (cudaError_t (*)(struct cudaArrayMemoryRequirements *, cudaArray_t, int)) dlsym(libcudart_handle, "cudaArrayGetMemoryRequirements");
			fprintf(stderr, "cudaArrayGetMemoryRequirements:%p\n", wrapper_cudaArrayGetMemoryRequirements);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaArrayGetMemoryRequirements():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaArrayGetMemoryRequirements(memoryRequirements, array, device);
		return retval;
	}
}

