#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnOpsInferVersionCheck)();
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnOpsInferVersionCheck({
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnOpsInferVersionCheck)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnOpsInferVersionCheck = (cudnnStatus_t (*)()) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnOpsInferVersionCheck");
			fprintf(stderr, "wrapper_cudnnOpsInferVersionCheck:%p\n", wrapper_cudnnOpsInferVersionCheck);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnOpsInferVersionCheck():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnOpsInferVersionCheck();
		return retval;
	}
}

