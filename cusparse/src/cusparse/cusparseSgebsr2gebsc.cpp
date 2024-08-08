#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSgebsr2gebsc)(cusparseHandle_t, int, int, int, const float *, const int *, const int *, int, int, float *, int *, int *, cusparseAction_t, cusparseIndexBase_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSgebsr2gebsc(cusparseHandle_t handle, int mb, int nb, int nnzb, const float *bsrSortedVal, const int *bsrSortedRowPtr, const int *bsrSortedColInd, int rowBlockDim, int colBlockDim, float *bscVal, int *bscRowInd, int *bscColPtr, cusparseAction_t copyValues, cusparseIndexBase_t idxBase, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSgebsr2gebsc)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSgebsr2gebsc = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, const float *, const int *, const int *, int, int, float *, int *, int *, cusparseAction_t, cusparseIndexBase_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSgebsr2gebsc");
			fprintf(stderr, "wrapper_cusparseSgebsr2gebsc:%p\n", wrapper_cusparseSgebsr2gebsc);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSgebsr2gebsc():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSgebsr2gebsc(handle, mb, nb, nnzb, bsrSortedVal, bsrSortedRowPtr, bsrSortedColInd, rowBlockDim, colBlockDim, bscVal, bscRowInd, bscColPtr, copyValues, idxBase, pBuffer);
		return retval;
	}
}