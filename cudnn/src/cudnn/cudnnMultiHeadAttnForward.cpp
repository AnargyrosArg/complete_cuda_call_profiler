#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnMultiHeadAttnForward)(cudnnHandle_t, const cudnnAttnDescriptor_t, int, const int *, const int *, const int *, const int *, const cudnnSeqDataDescriptor_t, const void *, const void *, const cudnnSeqDataDescriptor_t, const void *, const cudnnSeqDataDescriptor_t, const void *, const cudnnSeqDataDescriptor_t, void *, size_t, const void *, size_t, void *, size_t, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnMultiHeadAttnForward(cudnnHandle_t handle, const cudnnAttnDescriptor_t attnDesc, int currIdx, const int loWinIdx[], const int hiWinIdx[], const int devSeqLengthsQO[], const int devSeqLengthsKV[], const cudnnSeqDataDescriptor_t qDesc, const void *queries, const void *residuals, const cudnnSeqDataDescriptor_t kDesc, const void *keys, const cudnnSeqDataDescriptor_t vDesc, const void *values, const cudnnSeqDataDescriptor_t oDesc, void *out, size_t weightSizeInBytes, const void *weights, size_t workSpaceSizeInBytes, void *workSpace, size_t reserveSpaceSizeInBytes, void *reserveSpace) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnMultiHeadAttnForward)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnMultiHeadAttnForward = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnAttnDescriptor_t, int, const int *, const int *, const int *, const int *, const cudnnSeqDataDescriptor_t, const void *, const void *, const cudnnSeqDataDescriptor_t, const void *, const cudnnSeqDataDescriptor_t, const void *, const cudnnSeqDataDescriptor_t, void *, size_t, const void *, size_t, void *, size_t, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnMultiHeadAttnForward");
			fprintf(stderr, "wrapper_cudnnMultiHeadAttnForward:%p\n", wrapper_cudnnMultiHeadAttnForward);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnMultiHeadAttnForward():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnMultiHeadAttnForward(handle, attnDesc, currIdx, loWinIdx, hiWinIdx, devSeqLengthsQO, devSeqLengthsKV, qDesc, queries, residuals, kDesc, keys, vDesc, values, oDesc, out, weightSizeInBytes, weights, workSpaceSizeInBytes, workSpace, reserveSpaceSizeInBytes, reserveSpace);
		return retval;
	}
}

