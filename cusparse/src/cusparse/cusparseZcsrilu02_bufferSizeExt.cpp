#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZcsrilu02_bufferSizeExt)(cusparseHandle_t, int, int, const cusparseMatDescr_t, cuDoubleComplex *, const int *, const int *, csrilu02Info_t, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZcsrilu02_bufferSizeExt(cusparseHandle_t handle, int m, int nnz, const cusparseMatDescr_t descrA, cuDoubleComplex *csrSortedVal, const int *csrSortedRowPtr, const int *csrSortedColInd, csrilu02Info_t info, size_t *pBufferSize) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZcsrilu02_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZcsrilu02_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cusparseMatDescr_t, cuDoubleComplex *, const int *, const int *, csrilu02Info_t, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZcsrilu02_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseZcsrilu02_bufferSizeExt:%p\n", wrapper_cusparseZcsrilu02_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZcsrilu02_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZcsrilu02_bufferSizeExt(handle, m, nnz, descrA, csrSortedVal, csrSortedRowPtr, csrSortedColInd, info, pBufferSize);
		return retval;
	}
}