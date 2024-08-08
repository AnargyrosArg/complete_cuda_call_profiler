#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDestroyReduceTensorDescriptor)(cudnnReduceTensorDescriptor_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDestroyReduceTensorDescriptor(cudnnReduceTensorDescriptor_t reduceTensorDesc){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDestroyReduceTensorDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDestroyReduceTensorDescriptor = (cudnnStatus_t (*)(cudnnReduceTensorDescriptor_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDestroyReduceTensorDescriptor");
			fprintf(stderr, "wrapper_cudnnDestroyReduceTensorDescriptor:%p\n", wrapper_cudnnDestroyReduceTensorDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDestroyReduceTensorDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDestroyReduceTensorDescriptor(reduceTensorDesc);
		return retval;
	}
}

