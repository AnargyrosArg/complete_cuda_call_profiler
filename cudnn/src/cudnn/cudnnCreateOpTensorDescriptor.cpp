#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCreateOpTensorDescriptor)(cudnnOpTensorDescriptor_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCreateOpTensorDescriptor(cudnnOpTensorDescriptor_t *opTensorDesc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCreateOpTensorDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCreateOpTensorDescriptor = (cudnnStatus_t (*)(cudnnOpTensorDescriptor_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCreateOpTensorDescriptor");
			fprintf(stderr, "wrapper_cudnnCreateOpTensorDescriptor:%p\n", wrapper_cudnnCreateOpTensorDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCreateOpTensorDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCreateOpTensorDescriptor(opTensorDesc);
		return retval;
	}
}

