#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCreateRNNDescriptor)(cudnnRNNDescriptor_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCreateRNNDescriptor(cudnnRNNDescriptor_t *rnnDesc{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCreateRNNDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCreateRNNDescriptor = (cudnnStatus_t (*)(cudnnRNNDescriptor_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCreateRNNDescriptor");
			fprintf(stderr, "wrapper_cudnnCreateRNNDescriptor:%p\n", wrapper_cudnnCreateRNNDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCreateRNNDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCreateRNNDescriptor(rnnDesc);
		return retval;
	}
}

