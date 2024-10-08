#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDestroyAlgorithmDescriptor)(cudnnAlgorithmDescriptor_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDestroyAlgorithmDescriptor(cudnnAlgorithmDescriptor_t algoDesc){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDestroyAlgorithmDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDestroyAlgorithmDescriptor = (cudnnStatus_t (*)(cudnnAlgorithmDescriptor_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDestroyAlgorithmDescriptor");
			fprintf(stderr, "wrapper_cudnnDestroyAlgorithmDescriptor:%p\n", wrapper_cudnnDestroyAlgorithmDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDestroyAlgorithmDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDestroyAlgorithmDescriptor(algoDesc);
		return retval;
	}
}

