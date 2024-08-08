#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetAlgorithmPerformance)(const cudnnAlgorithmPerformance_t, cudnnAlgorithmDescriptor_t *, cudnnStatus_t *, float *, size_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetAlgorithmPerformance(const cudnnAlgorithmPerformance_t algoPerf, cudnnAlgorithmDescriptor_t *algoDesc, cudnnStatus_t *status, float *time, size_t *memory{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetAlgorithmPerformance)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetAlgorithmPerformance = (cudnnStatus_t (*)(const cudnnAlgorithmPerformance_t, cudnnAlgorithmDescriptor_t *, cudnnStatus_t *, float *, size_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetAlgorithmPerformance");
			fprintf(stderr, "wrapper_cudnnGetAlgorithmPerformance:%p\n", wrapper_cudnnGetAlgorithmPerformance);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetAlgorithmPerformance():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetAlgorithmPerformance(algoPerf, algoDesc, status, time, memory);
		return retval;
	}
}

