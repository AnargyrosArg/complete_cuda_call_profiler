#include <cudnn_backend.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnBackendExecute)(cudnnHandle_t, cudnnBackendDescriptor_t, cudnnBackendDescriptor_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnBackendExecute(cudnnHandle_t handle, cudnnBackendDescriptor_t executionPlan, cudnnBackendDescriptor_t variantPack{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnBackendExecute)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnBackendExecute = (cudnnStatus_t (*)(cudnnHandle_t, cudnnBackendDescriptor_t, cudnnBackendDescriptor_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnBackendExecute");
			fprintf(stderr, "wrapper_cudnnBackendExecute:%p\n", wrapper_cudnnBackendExecute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnBackendExecute():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnBackendExecute(handle, executionPlan, variantPack);
		return retval;
	}
}

