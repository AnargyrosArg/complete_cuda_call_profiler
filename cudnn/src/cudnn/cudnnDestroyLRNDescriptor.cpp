#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDestroyLRNDescriptor)(cudnnLRNDescriptor_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDestroyLRNDescriptor(cudnnLRNDescriptor_t lrnDesc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDestroyLRNDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDestroyLRNDescriptor = (cudnnStatus_t (*)(cudnnLRNDescriptor_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDestroyLRNDescriptor");
			fprintf(stderr, "wrapper_cudnnDestroyLRNDescriptor:%p\n", wrapper_cudnnDestroyLRNDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDestroyLRNDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDestroyLRNDescriptor(lrnDesc);
		return retval;
	}
}

