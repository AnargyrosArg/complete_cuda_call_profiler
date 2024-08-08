#include <cudnn_backend.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnBackendDestroyDescriptor)(cudnnBackendDescriptor_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnBackendDestroyDescriptor(cudnnBackendDescriptor_t descriptor{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnBackendDestroyDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnBackendDestroyDescriptor = (cudnnStatus_t (*)(cudnnBackendDescriptor_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnBackendDestroyDescriptor");
			fprintf(stderr, "wrapper_cudnnBackendDestroyDescriptor:%p\n", wrapper_cudnnBackendDestroyDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnBackendDestroyDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnBackendDestroyDescriptor(descriptor);
		return retval;
	}
}

