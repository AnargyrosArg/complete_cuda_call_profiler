#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetMultiHeadAttnBuffers)(cudnnHandle_t, const cudnnAttnDescriptor_t, size_t *, size_t *, size_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetMultiHeadAttnBuffers(cudnnHandle_t handle, const cudnnAttnDescriptor_t attnDesc, size_t *weightSizeInBytes, size_t *workSpaceSizeInBytes, size_t *reserveSpaceSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetMultiHeadAttnBuffers)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetMultiHeadAttnBuffers = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnAttnDescriptor_t, size_t *, size_t *, size_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetMultiHeadAttnBuffers");
			fprintf(stderr, "wrapper_cudnnGetMultiHeadAttnBuffers:%p\n", wrapper_cudnnGetMultiHeadAttnBuffers);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetMultiHeadAttnBuffers():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetMultiHeadAttnBuffers(handle, attnDesc, weightSizeInBytes, workSpaceSizeInBytes, reserveSpaceSizeInBytes);
		return retval;
	}
}

