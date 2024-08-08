#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnAdvInferVersionCheck)();
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnAdvInferVersionCheck({
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnAdvInferVersionCheck)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnAdvInferVersionCheck = (cudnnStatus_t (*)()) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnAdvInferVersionCheck");
			fprintf(stderr, "wrapper_cudnnAdvInferVersionCheck:%p\n", wrapper_cudnnAdvInferVersionCheck);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnAdvInferVersionCheck():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnAdvInferVersionCheck();
		return retval;
	}
}

