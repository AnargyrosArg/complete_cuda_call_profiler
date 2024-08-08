#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetRNNDescriptor_v6)(cudnnHandle_t, cudnnRNNDescriptor_t, const int, const int, cudnnDropoutDescriptor_t, cudnnRNNInputMode_t, cudnnDirectionMode_t, cudnnRNNMode_t, cudnnRNNAlgo_t, cudnnDataType_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetRNNDescriptor_v6(cudnnHandle_t handle, cudnnRNNDescriptor_t rnnDesc, const int hiddenSize, const int numLayers, cudnnDropoutDescriptor_t dropoutDesc, cudnnRNNInputMode_t inputMode, cudnnDirectionMode_t direction, cudnnRNNMode_t cellMode, cudnnRNNAlgo_t algo, cudnnDataType_t mathPrec{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetRNNDescriptor_v6)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetRNNDescriptor_v6 = (cudnnStatus_t (*)(cudnnHandle_t, cudnnRNNDescriptor_t, const int, const int, cudnnDropoutDescriptor_t, cudnnRNNInputMode_t, cudnnDirectionMode_t, cudnnRNNMode_t, cudnnRNNAlgo_t, cudnnDataType_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetRNNDescriptor_v6");
			fprintf(stderr, "wrapper_cudnnSetRNNDescriptor_v6:%p\n", wrapper_cudnnSetRNNDescriptor_v6);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetRNNDescriptor_v6():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetRNNDescriptor_v6(handle, rnnDesc, hiddenSize, numLayers, dropoutDesc, inputMode, direction, cellMode, algo, mathPrec);
		return retval;
	}
}

