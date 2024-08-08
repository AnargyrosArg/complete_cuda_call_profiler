#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetOpTensorDescriptor)(cudnnOpTensorDescriptor_t, cudnnOpTensorOp_t, cudnnDataType_t, cudnnNanPropagation_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetOpTensorDescriptor(cudnnOpTensorDescriptor_t opTensorDesc, cudnnOpTensorOp_t opTensorOp, cudnnDataType_t opTensorCompType, cudnnNanPropagation_t opTensorNanOpt){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetOpTensorDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetOpTensorDescriptor = (cudnnStatus_t (*)(cudnnOpTensorDescriptor_t, cudnnOpTensorOp_t, cudnnDataType_t, cudnnNanPropagation_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetOpTensorDescriptor");
			fprintf(stderr, "wrapper_cudnnSetOpTensorDescriptor:%p\n", wrapper_cudnnSetOpTensorDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetOpTensorDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetOpTensorDescriptor(opTensorDesc, opTensorOp, opTensorCompType, opTensorNanOpt);
		return retval;
	}
}

