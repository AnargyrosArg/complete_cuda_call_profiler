#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDestroyFilterDescriptor)(cudnnFilterDescriptor_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDestroyFilterDescriptor(cudnnFilterDescriptor_t filterDesc{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDestroyFilterDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDestroyFilterDescriptor = (cudnnStatus_t (*)(cudnnFilterDescriptor_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDestroyFilterDescriptor");
			fprintf(stderr, "wrapper_cudnnDestroyFilterDescriptor:%p\n", wrapper_cudnnDestroyFilterDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDestroyFilterDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDestroyFilterDescriptor(filterDesc);
		return retval;
	}
}

