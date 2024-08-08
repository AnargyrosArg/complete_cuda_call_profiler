
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphicsResourceGetMappedMipmappedArray)(cudaMipmappedArray_t *, cudaGraphicsResource_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphicsResourceGetMappedMipmappedArray(cudaMipmappedArray_t *mipmappedArray, cudaGraphicsResource_t resource) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphicsResourceGetMappedMipmappedArray)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphicsResourceGetMappedMipmappedArray = (cudaError_t (*)(cudaMipmappedArray_t *, cudaGraphicsResource_t)) dlsym(libcudart_handle, "cudaGraphicsResourceGetMappedMipmappedArray");
			fprintf(stderr, "cudaGraphicsResourceGetMappedMipmappedArray:%p\n", wrapper_cudaGraphicsResourceGetMappedMipmappedArray);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphicsResourceGetMappedMipmappedArray():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphicsResourceGetMappedMipmappedArray(mipmappedArray, resource);
		return retval;
	}
}

