#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetAlgorithmPerformance)(cudnnAlgorithmPerformance_t, cudnnAlgorithmDescriptor_t, cudnnStatus_t, float, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetAlgorithmPerformance(cudnnAlgorithmPerformance_t algoPerf, cudnnAlgorithmDescriptor_t algoDesc, cudnnStatus_t status, float time, size_t memory{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetAlgorithmPerformance)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetAlgorithmPerformance = (cudnnStatus_t (*)(cudnnAlgorithmPerformance_t, cudnnAlgorithmDescriptor_t, cudnnStatus_t, float, size_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetAlgorithmPerformance");
			fprintf(stderr, "wrapper_cudnnSetAlgorithmPerformance:%p\n", wrapper_cudnnSetAlgorithmPerformance);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetAlgorithmPerformance():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetAlgorithmPerformance(algoPerf, algoDesc, status, time, memory);
		return retval;
	}
}

