#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnInitTransformDest)(const cudnnTensorTransformDescriptor_t, const cudnnTensorDescriptor_t, cudnnTensorDescriptor_t, size_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnInitTransformDest(const cudnnTensorTransformDescriptor_t transformDesc, const cudnnTensorDescriptor_t srcDesc, cudnnTensorDescriptor_t destDesc, size_t *destSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnInitTransformDest)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnInitTransformDest = (cudnnStatus_t (*)(const cudnnTensorTransformDescriptor_t, const cudnnTensorDescriptor_t, cudnnTensorDescriptor_t, size_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnInitTransformDest");
			fprintf(stderr, "wrapper_cudnnInitTransformDest:%p\n", wrapper_cudnnInitTransformDest);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnInitTransformDest():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnInitTransformDest(transformDesc, srcDesc, destDesc, destSizeInBytes);
		return retval;
	}
}

