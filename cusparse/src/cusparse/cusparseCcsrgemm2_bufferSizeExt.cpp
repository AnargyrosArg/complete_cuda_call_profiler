#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCcsrgemm2_bufferSizeExt)(cusparseHandle_t, int, int, int, const cuComplex *, const cusparseMatDescr_t, int, const int *, const int *, const cusparseMatDescr_t, int, const int *, const int *, const cuComplex *, const cusparseMatDescr_t, int, const int *, const int *, csrgemm2Info_t, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCcsrgemm2_bufferSizeExt(cusparseHandle_t handle, int m, int n, int k, const cuComplex *alpha, const cusparseMatDescr_t descrA, int nnzA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, const cusparseMatDescr_t descrB, int nnzB, const int *csrSortedRowPtrB, const int *csrSortedColIndB, const cuComplex *beta, const cusparseMatDescr_t descrD, int nnzD, const int *csrSortedRowPtrD, const int *csrSortedColIndD, csrgemm2Info_t info, size_t *pBufferSizeInBytes) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCcsrgemm2_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCcsrgemm2_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, const cuComplex *, const cusparseMatDescr_t, int, const int *, const int *, const cusparseMatDescr_t, int, const int *, const int *, const cuComplex *, const cusparseMatDescr_t, int, const int *, const int *, csrgemm2Info_t, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCcsrgemm2_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseCcsrgemm2_bufferSizeExt:%p\n", wrapper_cusparseCcsrgemm2_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCcsrgemm2_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCcsrgemm2_bufferSizeExt(handle, m, n, k, alpha, descrA, nnzA, csrSortedRowPtrA, csrSortedColIndA, descrB, nnzB, csrSortedRowPtrB, csrSortedColIndB, beta, descrD, nnzD, csrSortedRowPtrD, csrSortedColIndD, info, pBufferSizeInBytes);
		return retval;
	}
}