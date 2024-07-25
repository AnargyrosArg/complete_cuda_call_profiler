#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnMultiHeadAttnBackwardData)(cudnnHandle_t, const cudnnAttnDescriptor_t, const int *, const int *, const int *, const int *, const cudnnSeqDataDescriptor_t, const void *, const cudnnSeqDataDescriptor_t, void *, const void *, const cudnnSeqDataDescriptor_t, void *, const void *, const cudnnSeqDataDescriptor_t, void *, const void *, size_t, const void *, size_t, void *, size_t, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnMultiHeadAttnBackwardData(cudnnHandle_t handle, const cudnnAttnDescriptor_t attnDesc, const int loWinIdx[], const int hiWinIdx[], const int devSeqLengthsDQDO[], const int devSeqLengthsDKDV[], const cudnnSeqDataDescriptor_t doDesc, const void *dout, const cudnnSeqDataDescriptor_t dqDesc, void *dqueries, const void *queries, const cudnnSeqDataDescriptor_t dkDesc, void *dkeys, const void *keys, const cudnnSeqDataDescriptor_t dvDesc, void *dvalues, const void *values, size_t weightSizeInBytes, const void *weights, size_t workSpaceSizeInBytes, void *workSpace, size_t reserveSpaceSizeInBytes, void *reserveSpace) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnMultiHeadAttnBackwardData)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnMultiHeadAttnBackwardData = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnAttnDescriptor_t, const int *, const int *, const int *, const int *, const cudnnSeqDataDescriptor_t, const void *, const cudnnSeqDataDescriptor_t, void *, const void *, const cudnnSeqDataDescriptor_t, void *, const void *, const cudnnSeqDataDescriptor_t, void *, const void *, size_t, const void *, size_t, void *, size_t, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnMultiHeadAttnBackwardData");
			fprintf(stderr, "wrapper_cudnnMultiHeadAttnBackwardData:%p\n", wrapper_cudnnMultiHeadAttnBackwardData);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnMultiHeadAttnBackwardData():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnMultiHeadAttnBackwardData(handle, attnDesc, loWinIdx, hiWinIdx, devSeqLengthsDQDO, devSeqLengthsDKDV, doDesc, dout, dqDesc, dqueries, queries, dkDesc, dkeys, keys, dvDesc, dvalues, values, weightSizeInBytes, weights, workSpaceSizeInBytes, workSpace, reserveSpaceSizeInBytes, reserveSpace);
		return retval;
	}
}

