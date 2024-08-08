#include <cudnn_backend.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnBackendInitialize)(cudnnBackendDescriptor_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnBackendInitialize(cudnnBackendDescriptor_t descriptor{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnBackendInitialize)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnBackendInitialize = (cudnnStatus_t (*)(cudnnBackendDescriptor_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnBackendInitialize");
			fprintf(stderr, "wrapper_cudnnBackendInitialize:%p\n", wrapper_cudnnBackendInitialize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnBackendInitialize():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnBackendInitialize(descriptor);
		return retval;
	}
}

