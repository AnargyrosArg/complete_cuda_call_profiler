
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaBindTextureToMipmappedArray)(const struct textureReference *, cudaMipmappedArray_const_t, const struct cudaChannelFormatDesc *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaBindTextureToMipmappedArray(const struct textureReference *texref, cudaMipmappedArray_const_t mipmappedArray, const struct cudaChannelFormatDesc *desc) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaBindTextureToMipmappedArray)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaBindTextureToMipmappedArray = (cudaError_t (*)(const struct textureReference *, cudaMipmappedArray_const_t, const struct cudaChannelFormatDesc *)) dlsym(libcudart_handle, "cudaBindTextureToMipmappedArray");
			fprintf(stderr, "cudaBindTextureToMipmappedArray:%p\n", wrapper_cudaBindTextureToMipmappedArray);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaBindTextureToMipmappedArray():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaBindTextureToMipmappedArray(texref, mipmappedArray, desc);
		return retval;
	}
}

