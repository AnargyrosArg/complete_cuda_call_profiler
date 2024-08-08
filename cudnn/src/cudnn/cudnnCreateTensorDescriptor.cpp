#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCreateTensorDescriptor)(cudnnTensorDescriptor_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCreateTensorDescriptor(cudnnTensorDescriptor_t *tensorDesc){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCreateTensorDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCreateTensorDescriptor = (cudnnStatus_t (*)(cudnnTensorDescriptor_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCreateTensorDescriptor");
			fprintf(stderr, "wrapper_cudnnCreateTensorDescriptor:%p\n", wrapper_cudnnCreateTensorDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCreateTensorDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCreateTensorDescriptor(tensorDesc);
		return retval;
	}
}

