#include <cudnn_backend.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnBackendCreateDescriptor)(cudnnBackendDescriptorType_t, cudnnBackendDescriptor_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnBackendCreateDescriptor(cudnnBackendDescriptorType_t descriptorType, cudnnBackendDescriptor_t *descriptor{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnBackendCreateDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnBackendCreateDescriptor = (cudnnStatus_t (*)(cudnnBackendDescriptorType_t, cudnnBackendDescriptor_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnBackendCreateDescriptor");
			fprintf(stderr, "wrapper_cudnnBackendCreateDescriptor:%p\n", wrapper_cudnnBackendCreateDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnBackendCreateDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnBackendCreateDescriptor(descriptorType, descriptor);
		return retval;
	}
}

