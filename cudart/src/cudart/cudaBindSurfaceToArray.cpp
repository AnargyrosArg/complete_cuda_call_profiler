
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaBindSurfaceToArray)(const struct surfaceReference *, cudaArray_const_t, const struct cudaChannelFormatDesc *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaBindSurfaceToArray(const struct surfaceReference *surfref, cudaArray_const_t array, const struct cudaChannelFormatDesc *desc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaBindSurfaceToArray)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaBindSurfaceToArray = (cudaError_t (*)(const struct surfaceReference *, cudaArray_const_t, const struct cudaChannelFormatDesc *)) dlsym(libcudart_handle, "cudaBindSurfaceToArray");
			fprintf(stderr, "cudaBindSurfaceToArray:%p\n", wrapper_cudaBindSurfaceToArray);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaBindSurfaceToArray():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaBindSurfaceToArray(surfref, array, desc);
		return retval;
	}
}

