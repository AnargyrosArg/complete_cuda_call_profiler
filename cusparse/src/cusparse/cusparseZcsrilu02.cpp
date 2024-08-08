#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZcsrilu02)(cusparseHandle_t, int, int, const cusparseMatDescr_t, cuDoubleComplex *, const int *, const int *, csrilu02Info_t, cusparseSolvePolicy_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZcsrilu02(cusparseHandle_t handle, int m, int nnz, const cusparseMatDescr_t descrA, cuDoubleComplex *csrSortedValA_valM, const int *csrSortedRowPtrA, const int *csrSortedColIndA, csrilu02Info_t info, cusparseSolvePolicy_t policy, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZcsrilu02)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZcsrilu02 = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cusparseMatDescr_t, cuDoubleComplex *, const int *, const int *, csrilu02Info_t, cusparseSolvePolicy_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZcsrilu02");
			fprintf(stderr, "wrapper_cusparseZcsrilu02:%p\n", wrapper_cusparseZcsrilu02);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZcsrilu02():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZcsrilu02(handle, m, nnz, descrA, csrSortedValA_valM, csrSortedRowPtrA, csrSortedColIndA, info, policy, pBuffer);
		return retval;
	}
}