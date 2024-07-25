
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGetTextureObjectTextureDesc)(struct cudaTextureDesc *, cudaTextureObject_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGetTextureObjectTextureDesc(struct cudaTextureDesc *pTexDesc, cudaTextureObject_t texObject) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGetTextureObjectTextureDesc)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGetTextureObjectTextureDesc = (cudaError_t (*)(struct cudaTextureDesc *, cudaTextureObject_t)) dlsym(libcudart_handle, "cudaGetTextureObjectTextureDesc");
			fprintf(stderr, "cudaGetTextureObjectTextureDesc:%p\n", wrapper_cudaGetTextureObjectTextureDesc);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGetTextureObjectTextureDesc():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGetTextureObjectTextureDesc(pTexDesc, texObject);
		return retval;
	}
}

