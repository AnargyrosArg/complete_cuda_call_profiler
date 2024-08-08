#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDestroyAttnDescriptor)(cudnnAttnDescriptor_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDestroyAttnDescriptor(cudnnAttnDescriptor_t attnDesc{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDestroyAttnDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDestroyAttnDescriptor = (cudnnStatus_t (*)(cudnnAttnDescriptor_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDestroyAttnDescriptor");
			fprintf(stderr, "wrapper_cudnnDestroyAttnDescriptor:%p\n", wrapper_cudnnDestroyAttnDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDestroyAttnDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDestroyAttnDescriptor(attnDesc);
		return retval;
	}
}

