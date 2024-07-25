
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaCreateTextureObject)(cudaTextureObject_t *, const struct cudaResourceDesc *, const struct cudaTextureDesc *, const struct cudaResourceViewDesc *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaCreateTextureObject(cudaTextureObject_t *pTexObject, const struct cudaResourceDesc *pResDesc, const struct cudaTextureDesc *pTexDesc, const struct cudaResourceViewDesc *pResViewDesc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaCreateTextureObject)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaCreateTextureObject = (cudaError_t (*)(cudaTextureObject_t *, const struct cudaResourceDesc *, const struct cudaTextureDesc *, const struct cudaResourceViewDesc *)) dlsym(libcudart_handle, "cudaCreateTextureObject");
			fprintf(stderr, "cudaCreateTextureObject:%p\n", wrapper_cudaCreateTextureObject);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaCreateTextureObject():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaCreateTextureObject(pTexObject, pResDesc, pTexDesc, pResViewDesc);
		return retval;
	}
}

