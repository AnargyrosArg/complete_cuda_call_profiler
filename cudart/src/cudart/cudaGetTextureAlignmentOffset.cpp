
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGetTextureAlignmentOffset)(size_t *, const struct textureReference *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGetTextureAlignmentOffset(size_t *offset, const struct textureReference *texref) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGetTextureAlignmentOffset)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGetTextureAlignmentOffset = (cudaError_t (*)(size_t *, const struct textureReference *)) dlsym(libcudart_handle, "cudaGetTextureAlignmentOffset");
			fprintf(stderr, "cudaGetTextureAlignmentOffset:%p\n", wrapper_cudaGetTextureAlignmentOffset);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGetTextureAlignmentOffset():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGetTextureAlignmentOffset(offset, texref);
		return retval;
	}
}

