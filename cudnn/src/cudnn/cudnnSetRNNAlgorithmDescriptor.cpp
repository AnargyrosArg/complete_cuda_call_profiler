#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetRNNAlgorithmDescriptor)(cudnnHandle_t, cudnnRNNDescriptor_t, cudnnAlgorithmDescriptor_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetRNNAlgorithmDescriptor(cudnnHandle_t handle, cudnnRNNDescriptor_t rnnDesc, cudnnAlgorithmDescriptor_t algoDesc){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetRNNAlgorithmDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetRNNAlgorithmDescriptor = (cudnnStatus_t (*)(cudnnHandle_t, cudnnRNNDescriptor_t, cudnnAlgorithmDescriptor_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetRNNAlgorithmDescriptor");
			fprintf(stderr, "wrapper_cudnnSetRNNAlgorithmDescriptor:%p\n", wrapper_cudnnSetRNNAlgorithmDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetRNNAlgorithmDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetRNNAlgorithmDescriptor(handle, rnnDesc, algoDesc);
		return retval;
	}
}

