#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCcsric02_analysis)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, csric02Info_t, cusparseSolvePolicy_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCcsric02_analysis(cusparseHandle_t handle, int m, int nnz, const cusparseMatDescr_t descrA, const cuComplex *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, csric02Info_t info, cusparseSolvePolicy_t policy, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCcsric02_analysis)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCcsric02_analysis = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, csric02Info_t, cusparseSolvePolicy_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCcsric02_analysis");
			fprintf(stderr, "wrapper_cusparseCcsric02_analysis:%p\n", wrapper_cusparseCcsric02_analysis);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCcsric02_analysis():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCcsric02_analysis(handle, m, nnz, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, info, policy, pBuffer);
		return retval;
	}
}