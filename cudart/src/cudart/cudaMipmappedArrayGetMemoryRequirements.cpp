
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMipmappedArrayGetMemoryRequirements)(struct cudaArrayMemoryRequirements *, cudaMipmappedArray_t, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMipmappedArrayGetMemoryRequirements(struct cudaArrayMemoryRequirements *memoryRequirements, cudaMipmappedArray_t mipmap, int device) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMipmappedArrayGetMemoryRequirements)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMipmappedArrayGetMemoryRequirements = (cudaError_t (*)(struct cudaArrayMemoryRequirements *, cudaMipmappedArray_t, int)) dlsym(libcudart_handle, "cudaMipmappedArrayGetMemoryRequirements");
			fprintf(stderr, "cudaMipmappedArrayGetMemoryRequirements:%p\n", wrapper_cudaMipmappedArrayGetMemoryRequirements);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMipmappedArrayGetMemoryRequirements():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMipmappedArrayGetMemoryRequirements(memoryRequirements, mipmap, device);
		return retval;
	}
}

