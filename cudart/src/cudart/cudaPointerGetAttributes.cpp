
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaPointerGetAttributes)(struct cudaPointerAttributes *, const void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaPointerGetAttributes(struct cudaPointerAttributes *attributes, const void *ptr) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaPointerGetAttributes)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaPointerGetAttributes = (cudaError_t (*)(struct cudaPointerAttributes *, const void *)) dlsym(libcudart_handle, "cudaPointerGetAttributes");
			fprintf(stderr, "cudaPointerGetAttributes:%p\n", wrapper_cudaPointerGetAttributes);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaPointerGetAttributes():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaPointerGetAttributes(attributes, ptr);
		return retval;
	}
}

