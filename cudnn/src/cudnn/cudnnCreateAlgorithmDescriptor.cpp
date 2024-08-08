#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCreateAlgorithmDescriptor)(cudnnAlgorithmDescriptor_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCreateAlgorithmDescriptor(cudnnAlgorithmDescriptor_t *algoDesc{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCreateAlgorithmDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCreateAlgorithmDescriptor = (cudnnStatus_t (*)(cudnnAlgorithmDescriptor_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCreateAlgorithmDescriptor");
			fprintf(stderr, "wrapper_cudnnCreateAlgorithmDescriptor:%p\n", wrapper_cudnnCreateAlgorithmDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCreateAlgorithmDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCreateAlgorithmDescriptor(algoDesc);
		return retval;
	}
}

