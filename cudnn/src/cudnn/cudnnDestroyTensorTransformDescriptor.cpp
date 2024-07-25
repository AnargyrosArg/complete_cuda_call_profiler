#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDestroyTensorTransformDescriptor)(cudnnTensorTransformDescriptor_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDestroyTensorTransformDescriptor(cudnnTensorTransformDescriptor_t transformDesc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDestroyTensorTransformDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDestroyTensorTransformDescriptor = (cudnnStatus_t (*)(cudnnTensorTransformDescriptor_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDestroyTensorTransformDescriptor");
			fprintf(stderr, "wrapper_cudnnDestroyTensorTransformDescriptor:%p\n", wrapper_cudnnDestroyTensorTransformDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDestroyTensorTransformDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDestroyTensorTransformDescriptor(transformDesc);
		return retval;
	}
}
