#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCsr2cscEx2_bufferSize)(cusparseHandle_t, int, int, int, const void *, const int *, const int *, void *, int *, int *, cudaDataType, cusparseAction_t, cusparseIndexBase_t, cusparseCsr2CscAlg_t, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCsr2cscEx2_bufferSize(cusparseHandle_t handle, int m, int n, int nnz, const void *csrVal, const int *csrRowPtr, const int *csrColInd, void *cscVal, int *cscColPtr, int *cscRowInd, cudaDataType valType, cusparseAction_t copyValues, cusparseIndexBase_t idxBase, cusparseCsr2CscAlg_t alg, size_t *bufferSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCsr2cscEx2_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCsr2cscEx2_bufferSize = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, const void *, const int *, const int *, void *, int *, int *, cudaDataType, cusparseAction_t, cusparseIndexBase_t, cusparseCsr2CscAlg_t, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCsr2cscEx2_bufferSize");
			fprintf(stderr, "wrapper_cusparseCsr2cscEx2_bufferSize:%p\n", wrapper_cusparseCsr2cscEx2_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCsr2cscEx2_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCsr2cscEx2_bufferSize(handle, m, n, nnz, csrVal, csrRowPtr, csrColInd, cscVal, cscColPtr, cscRowInd, valType, copyValues, idxBase, alg, bufferSize);
		return retval;
	}
}