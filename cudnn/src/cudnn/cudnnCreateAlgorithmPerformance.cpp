#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCreateAlgorithmPerformance)(cudnnAlgorithmPerformance_t *, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCreateAlgorithmPerformance(cudnnAlgorithmPerformance_t *algoPerf, int numberToCreate) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCreateAlgorithmPerformance)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCreateAlgorithmPerformance = (cudnnStatus_t (*)(cudnnAlgorithmPerformance_t *, int)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCreateAlgorithmPerformance");
			fprintf(stderr, "wrapper_cudnnCreateAlgorithmPerformance:%p\n", wrapper_cudnnCreateAlgorithmPerformance);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCreateAlgorithmPerformance():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCreateAlgorithmPerformance(algoPerf, numberToCreate);
		return retval;
	}
}

