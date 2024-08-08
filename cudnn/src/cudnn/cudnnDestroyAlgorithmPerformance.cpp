#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDestroyAlgorithmPerformance)(cudnnAlgorithmPerformance_t *, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDestroyAlgorithmPerformance(cudnnAlgorithmPerformance_t *algoPerf, int numberToDestroy{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDestroyAlgorithmPerformance)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDestroyAlgorithmPerformance = (cudnnStatus_t (*)(cudnnAlgorithmPerformance_t *, int)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDestroyAlgorithmPerformance");
			fprintf(stderr, "wrapper_cudnnDestroyAlgorithmPerformance:%p\n", wrapper_cudnnDestroyAlgorithmPerformance);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDestroyAlgorithmPerformance():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDestroyAlgorithmPerformance(algoPerf, numberToDestroy);
		return retval;
	}
}

