#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnRestoreAlgorithm)(cudnnHandle_t, void *, size_t, cudnnAlgorithmDescriptor_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnRestoreAlgorithm(cudnnHandle_t handle, void *algoSpace, size_t algoSpaceSizeInBytes, cudnnAlgorithmDescriptor_t algoDesc{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnRestoreAlgorithm)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnRestoreAlgorithm = (cudnnStatus_t (*)(cudnnHandle_t, void *, size_t, cudnnAlgorithmDescriptor_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnRestoreAlgorithm");
			fprintf(stderr, "wrapper_cudnnRestoreAlgorithm:%p\n", wrapper_cudnnRestoreAlgorithm);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnRestoreAlgorithm():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnRestoreAlgorithm(handle, algoSpace, algoSpaceSizeInBytes, algoDesc);
		return retval;
	}
}

