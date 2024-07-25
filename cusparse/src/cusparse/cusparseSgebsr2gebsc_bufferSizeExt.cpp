#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSgebsr2gebsc_bufferSizeExt)(cusparseHandle_t, int, int, int, const float *, const int *, const int *, int, int, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSgebsr2gebsc_bufferSizeExt(cusparseHandle_t handle, int mb, int nb, int nnzb, const float *bsrSortedVal, const int *bsrSortedRowPtr, const int *bsrSortedColInd, int rowBlockDim, int colBlockDim, size_t *pBufferSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSgebsr2gebsc_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSgebsr2gebsc_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, const float *, const int *, const int *, int, int, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSgebsr2gebsc_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseSgebsr2gebsc_bufferSizeExt:%p\n", wrapper_cusparseSgebsr2gebsc_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSgebsr2gebsc_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSgebsr2gebsc_bufferSizeExt(handle, mb, nb, nnzb, bsrSortedVal, bsrSortedRowPtr, bsrSortedColInd, rowBlockDim, colBlockDim, pBufferSize);
		return retval;
	}
}