/*#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnQueryRuntimeError)(cudnnHandle_t, cudnnStatus_t *, cudnnErrQueryMode_t, cudnnRuntimeTag_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnQueryRuntimeError(cudnnHandle_t handle, cudnnStatus_t *rstatus, cudnnErrQueryMode_t mode, cudnnRuntimeTag_t *tag{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnQueryRuntimeError)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnQueryRuntimeError = (cudnnStatus_t (*)(cudnnHandle_t, cudnnStatus_t *, cudnnErrQueryMode_t, cudnnRuntimeTag_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnQueryRuntimeError");
			fprintf(stderr, "wrapper_cudnnQueryRuntimeError:%p\n", wrapper_cudnnQueryRuntimeError);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnQueryRuntimeError():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnQueryRuntimeError(handle, rstatus, mode, tag);
		return retval;
	}
}
*/


