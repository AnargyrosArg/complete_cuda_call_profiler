#include <cudnn_backend.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnBackendFinalize)(cudnnBackendDescriptor_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnBackendFinalize(cudnnBackendDescriptor_t descriptor) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnBackendFinalize)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnBackendFinalize = (cudnnStatus_t (*)(cudnnBackendDescriptor_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnBackendFinalize");
			fprintf(stderr, "wrapper_cudnnBackendFinalize:%p\n", wrapper_cudnnBackendFinalize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnBackendFinalize():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnBackendFinalize(descriptor);
		return retval;
	}
}
