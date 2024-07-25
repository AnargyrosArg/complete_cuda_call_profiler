
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphicsUnmapResources)(int, cudaGraphicsResource_t *, cudaStream_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphicsUnmapResources(int count, cudaGraphicsResource_t *resources, cudaStream_t stream) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphicsUnmapResources)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphicsUnmapResources = (cudaError_t (*)(int, cudaGraphicsResource_t *, cudaStream_t)) dlsym(libcudart_handle, "cudaGraphicsUnmapResources");
			fprintf(stderr, "cudaGraphicsUnmapResources:%p\n", wrapper_cudaGraphicsUnmapResources);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphicsUnmapResources():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphicsUnmapResources(count, resources, stream);
		return retval;
	}
}
