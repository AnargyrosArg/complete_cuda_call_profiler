#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetAlgorithmDescriptor)(cudnnAlgorithmDescriptor_t, cudnnAlgorithm_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetAlgorithmDescriptor(cudnnAlgorithmDescriptor_t algoDesc, cudnnAlgorithm_t algorithm){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetAlgorithmDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetAlgorithmDescriptor = (cudnnStatus_t (*)(cudnnAlgorithmDescriptor_t, cudnnAlgorithm_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetAlgorithmDescriptor");
			fprintf(stderr, "wrapper_cudnnSetAlgorithmDescriptor:%p\n", wrapper_cudnnSetAlgorithmDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetAlgorithmDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetAlgorithmDescriptor(algoDesc, algorithm);
		return retval;
	}
}

