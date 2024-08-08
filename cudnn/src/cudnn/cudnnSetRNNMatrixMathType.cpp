#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetRNNMatrixMathType)(cudnnRNNDescriptor_t, cudnnMathType_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetRNNMatrixMathType(cudnnRNNDescriptor_t rnnDesc, cudnnMathType_t mType{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetRNNMatrixMathType)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetRNNMatrixMathType = (cudnnStatus_t (*)(cudnnRNNDescriptor_t, cudnnMathType_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetRNNMatrixMathType");
			fprintf(stderr, "wrapper_cudnnSetRNNMatrixMathType:%p\n", wrapper_cudnnSetRNNMatrixMathType);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetRNNMatrixMathType():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetRNNMatrixMathType(rnnDesc, mType);
		return retval;
	}
}

