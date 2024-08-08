#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCgebsr2gebsc_bufferSizeExt)(cusparseHandle_t, int, int, int, const cuComplex *, const int *, const int *, int, int, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCgebsr2gebsc_bufferSizeExt(cusparseHandle_t handle, int mb, int nb, int nnzb, const cuComplex *bsrSortedVal, const int *bsrSortedRowPtr, const int *bsrSortedColInd, int rowBlockDim, int colBlockDim, size_t *pBufferSize) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCgebsr2gebsc_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCgebsr2gebsc_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, const cuComplex *, const int *, const int *, int, int, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCgebsr2gebsc_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseCgebsr2gebsc_bufferSizeExt:%p\n", wrapper_cusparseCgebsr2gebsc_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCgebsr2gebsc_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCgebsr2gebsc_bufferSizeExt(handle, mb, nb, nnzb, bsrSortedVal, bsrSortedRowPtr, bsrSortedColInd, rowBlockDim, colBlockDim, pBufferSize);
		return retval;
	}
}