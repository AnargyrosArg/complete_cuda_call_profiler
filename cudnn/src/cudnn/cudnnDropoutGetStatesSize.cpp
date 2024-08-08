#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDropoutGetStatesSize)(cudnnHandle_t, size_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDropoutGetStatesSize(cudnnHandle_t handle, size_t *sizeInBytes{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDropoutGetStatesSize)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDropoutGetStatesSize = (cudnnStatus_t (*)(cudnnHandle_t, size_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDropoutGetStatesSize");
			fprintf(stderr, "wrapper_cudnnDropoutGetStatesSize:%p\n", wrapper_cudnnDropoutGetStatesSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDropoutGetStatesSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDropoutGetStatesSize(handle, sizeInBytes);
		return retval;
	}
}

