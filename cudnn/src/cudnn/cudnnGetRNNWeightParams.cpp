#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetRNNWeightParams)(cudnnHandle_t, cudnnRNNDescriptor_t, int32_t, size_t, const void *, int32_t, cudnnTensorDescriptor_t, void **, cudnnTensorDescriptor_t, void **);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetRNNWeightParams(cudnnHandle_t handle, cudnnRNNDescriptor_t rnnDesc, int32_t pseudoLayer, size_t weightSpaceSize, const void *weightSpace, int32_t linLayerID, cudnnTensorDescriptor_t mDesc, void **mAddr, cudnnTensorDescriptor_t bDesc, void **bAddr{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetRNNWeightParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetRNNWeightParams = (cudnnStatus_t (*)(cudnnHandle_t, cudnnRNNDescriptor_t, int32_t, size_t, const void *, int32_t, cudnnTensorDescriptor_t, void **, cudnnTensorDescriptor_t, void **)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetRNNWeightParams");
			fprintf(stderr, "wrapper_cudnnGetRNNWeightParams:%p\n", wrapper_cudnnGetRNNWeightParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetRNNWeightParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetRNNWeightParams(handle, rnnDesc, pseudoLayer, weightSpaceSize, weightSpace, linLayerID, mDesc, mAddr, bDesc, bAddr);
		return retval;
	}
}

