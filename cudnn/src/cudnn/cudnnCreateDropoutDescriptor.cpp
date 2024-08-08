#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCreateDropoutDescriptor)(cudnnDropoutDescriptor_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCreateDropoutDescriptor(cudnnDropoutDescriptor_t *dropoutDesc{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCreateDropoutDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCreateDropoutDescriptor = (cudnnStatus_t (*)(cudnnDropoutDescriptor_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCreateDropoutDescriptor");
			fprintf(stderr, "wrapper_cudnnCreateDropoutDescriptor:%p\n", wrapper_cudnnCreateDropoutDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCreateDropoutDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCreateDropoutDescriptor(dropoutDesc);
		return retval;
	}
}

