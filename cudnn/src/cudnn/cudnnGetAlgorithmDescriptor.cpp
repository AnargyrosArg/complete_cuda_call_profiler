#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetAlgorithmDescriptor)(const cudnnAlgorithmDescriptor_t, cudnnAlgorithm_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetAlgorithmDescriptor(const cudnnAlgorithmDescriptor_t algoDesc, cudnnAlgorithm_t *algorithm{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetAlgorithmDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetAlgorithmDescriptor = (cudnnStatus_t (*)(const cudnnAlgorithmDescriptor_t, cudnnAlgorithm_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetAlgorithmDescriptor");
			fprintf(stderr, "wrapper_cudnnGetAlgorithmDescriptor:%p\n", wrapper_cudnnGetAlgorithmDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetAlgorithmDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetAlgorithmDescriptor(algoDesc, algorithm);
		return retval;
	}
}

