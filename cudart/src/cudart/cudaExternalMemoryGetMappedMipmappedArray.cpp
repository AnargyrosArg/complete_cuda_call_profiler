
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaExternalMemoryGetMappedMipmappedArray)(cudaMipmappedArray_t *, cudaExternalMemory_t, const struct cudaExternalMemoryMipmappedArrayDesc *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaExternalMemoryGetMappedMipmappedArray(cudaMipmappedArray_t *mipmap, cudaExternalMemory_t extMem, const struct cudaExternalMemoryMipmappedArrayDesc *mipmapDesc) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaExternalMemoryGetMappedMipmappedArray)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaExternalMemoryGetMappedMipmappedArray = (cudaError_t (*)(cudaMipmappedArray_t *, cudaExternalMemory_t, const struct cudaExternalMemoryMipmappedArrayDesc *)) dlsym(libcudart_handle, "cudaExternalMemoryGetMappedMipmappedArray");
			fprintf(stderr, "cudaExternalMemoryGetMappedMipmappedArray:%p\n", wrapper_cudaExternalMemoryGetMappedMipmappedArray);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaExternalMemoryGetMappedMipmappedArray():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaExternalMemoryGetMappedMipmappedArray(mipmap, extMem, mipmapDesc);
		return retval;
	}
}

