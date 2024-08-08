#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCreateRNNDataDescriptor)(cudnnRNNDataDescriptor_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCreateRNNDataDescriptor(cudnnRNNDataDescriptor_t *rnnDataDesc){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCreateRNNDataDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCreateRNNDataDescriptor = (cudnnStatus_t (*)(cudnnRNNDataDescriptor_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCreateRNNDataDescriptor");
			fprintf(stderr, "wrapper_cudnnCreateRNNDataDescriptor:%p\n", wrapper_cudnnCreateRNNDataDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCreateRNNDataDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCreateRNNDataDescriptor(rnnDataDesc);
		return retval;
	}
}

