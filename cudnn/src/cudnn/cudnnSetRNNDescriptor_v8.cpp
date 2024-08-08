#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetRNNDescriptor_v8)(cudnnRNNDescriptor_t, cudnnRNNAlgo_t, cudnnRNNMode_t, cudnnRNNBiasMode_t, cudnnDirectionMode_t, cudnnRNNInputMode_t, cudnnDataType_t, cudnnDataType_t, cudnnMathType_t, int32_t, int32_t, int32_t, int32_t, cudnnDropoutDescriptor_t, uint32_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetRNNDescriptor_v8(cudnnRNNDescriptor_t rnnDesc, cudnnRNNAlgo_t algo, cudnnRNNMode_t cellMode, cudnnRNNBiasMode_t biasMode, cudnnDirectionMode_t dirMode, cudnnRNNInputMode_t inputMode, cudnnDataType_t dataType, cudnnDataType_t mathPrec, cudnnMathType_t mathType, int32_t inputSize, int32_t hiddenSize, int32_t projSize, int32_t numLayers, cudnnDropoutDescriptor_t dropoutDesc, uint32_t auxFlags){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetRNNDescriptor_v8)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetRNNDescriptor_v8 = (cudnnStatus_t (*)(cudnnRNNDescriptor_t, cudnnRNNAlgo_t, cudnnRNNMode_t, cudnnRNNBiasMode_t, cudnnDirectionMode_t, cudnnRNNInputMode_t, cudnnDataType_t, cudnnDataType_t, cudnnMathType_t, int32_t, int32_t, int32_t, int32_t, cudnnDropoutDescriptor_t, uint32_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetRNNDescriptor_v8");
			fprintf(stderr, "wrapper_cudnnSetRNNDescriptor_v8:%p\n", wrapper_cudnnSetRNNDescriptor_v8);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetRNNDescriptor_v8():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetRNNDescriptor_v8(rnnDesc, algo, cellMode, biasMode, dirMode, inputMode, dataType, mathPrec, mathType, inputSize, hiddenSize, projSize, numLayers, dropoutDesc, auxFlags);
		return retval;
	}
}

