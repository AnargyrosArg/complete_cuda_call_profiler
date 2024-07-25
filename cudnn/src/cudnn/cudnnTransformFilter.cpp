#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnTransformFilter)(cudnnHandle_t, const cudnnTensorTransformDescriptor_t, const void *, const cudnnFilterDescriptor_t, const void *, const void *, const cudnnFilterDescriptor_t, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnTransformFilter(cudnnHandle_t handle, const cudnnTensorTransformDescriptor_t transDesc, const void *alpha, const cudnnFilterDescriptor_t srcDesc, const void *srcData, const void *beta, const cudnnFilterDescriptor_t destDesc, void *destData) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnTransformFilter)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnTransformFilter = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnTensorTransformDescriptor_t, const void *, const cudnnFilterDescriptor_t, const void *, const void *, const cudnnFilterDescriptor_t, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnTransformFilter");
			fprintf(stderr, "wrapper_cudnnTransformFilter:%p\n", wrapper_cudnnTransformFilter);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnTransformFilter():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnTransformFilter(handle, transDesc, alpha, srcDesc, srcData, beta, destDesc, destData);
		return retval;
	}
}

