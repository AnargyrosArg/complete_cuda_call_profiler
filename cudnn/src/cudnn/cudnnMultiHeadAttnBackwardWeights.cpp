#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnMultiHeadAttnBackwardWeights)(cudnnHandle_t, const cudnnAttnDescriptor_t, cudnnWgradMode_t, const cudnnSeqDataDescriptor_t, const void *, const cudnnSeqDataDescriptor_t, const void *, const cudnnSeqDataDescriptor_t, const void *, const cudnnSeqDataDescriptor_t, const void *, size_t, const void *, void *, size_t, void *, size_t, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnMultiHeadAttnBackwardWeights(cudnnHandle_t handle, const cudnnAttnDescriptor_t attnDesc, cudnnWgradMode_t addGrad, const cudnnSeqDataDescriptor_t qDesc, const void *queries, const cudnnSeqDataDescriptor_t kDesc, const void *keys, const cudnnSeqDataDescriptor_t vDesc, const void *values, const cudnnSeqDataDescriptor_t doDesc, const void *dout, size_t weightSizeInBytes, const void *weights, void *dweights, size_t workSpaceSizeInBytes, void *workSpace, size_t reserveSpaceSizeInBytes, void *reserveSpace) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnMultiHeadAttnBackwardWeights)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnMultiHeadAttnBackwardWeights = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnAttnDescriptor_t, cudnnWgradMode_t, const cudnnSeqDataDescriptor_t, const void *, const cudnnSeqDataDescriptor_t, const void *, const cudnnSeqDataDescriptor_t, const void *, const cudnnSeqDataDescriptor_t, const void *, size_t, const void *, void *, size_t, void *, size_t, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnMultiHeadAttnBackwardWeights");
			fprintf(stderr, "wrapper_cudnnMultiHeadAttnBackwardWeights:%p\n", wrapper_cudnnMultiHeadAttnBackwardWeights);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnMultiHeadAttnBackwardWeights():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnMultiHeadAttnBackwardWeights(handle, attnDesc, addGrad, qDesc, queries, kDesc, keys, vDesc, values, doDesc, dout, weightSizeInBytes, weights, dweights, workSpaceSizeInBytes, workSpace, reserveSpaceSizeInBytes, reserveSpace);
		return retval;
	}
}

