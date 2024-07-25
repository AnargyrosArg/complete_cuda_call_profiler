#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetRNNMatrixMathType)(cudnnRNNDescriptor_t, cudnnMathType_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetRNNMatrixMathType(cudnnRNNDescriptor_t rnnDesc, cudnnMathType_t *mType) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetRNNMatrixMathType)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetRNNMatrixMathType = (cudnnStatus_t (*)(cudnnRNNDescriptor_t, cudnnMathType_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetRNNMatrixMathType");
			fprintf(stderr, "wrapper_cudnnGetRNNMatrixMathType:%p\n", wrapper_cudnnGetRNNMatrixMathType);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetRNNMatrixMathType():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetRNNMatrixMathType(rnnDesc, mType);
		return retval;
	}
}

