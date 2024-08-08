#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetLRNDescriptor)(cudnnLRNDescriptor_t, unsigned, double, double, double);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetLRNDescriptor(cudnnLRNDescriptor_t normDesc, unsigned lrnN, double lrnAlpha, double lrnBeta, double lrnK{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetLRNDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetLRNDescriptor = (cudnnStatus_t (*)(cudnnLRNDescriptor_t, unsigned, double, double, double)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetLRNDescriptor");
			fprintf(stderr, "wrapper_cudnnSetLRNDescriptor:%p\n", wrapper_cudnnSetLRNDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetLRNDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetLRNDescriptor(normDesc, lrnN, lrnAlpha, lrnBeta, lrnK);
		return retval;
	}
}

