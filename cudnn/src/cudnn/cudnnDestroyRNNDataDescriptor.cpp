#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDestroyRNNDataDescriptor)(cudnnRNNDataDescriptor_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDestroyRNNDataDescriptor(cudnnRNNDataDescriptor_t rnnDataDesc{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDestroyRNNDataDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDestroyRNNDataDescriptor = (cudnnStatus_t (*)(cudnnRNNDataDescriptor_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDestroyRNNDataDescriptor");
			fprintf(stderr, "wrapper_cudnnDestroyRNNDataDescriptor:%p\n", wrapper_cudnnDestroyRNNDataDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDestroyRNNDataDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDestroyRNNDataDescriptor(rnnDataDesc);
		return retval;
	}
}

