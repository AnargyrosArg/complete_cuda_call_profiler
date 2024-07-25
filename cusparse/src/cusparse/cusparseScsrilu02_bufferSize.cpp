#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseScsrilu02_bufferSize)(cusparseHandle_t, int, int, const cusparseMatDescr_t, float *, const int *, const int *, csrilu02Info_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseScsrilu02_bufferSize(cusparseHandle_t handle, int m, int nnz, const cusparseMatDescr_t descrA, float *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, csrilu02Info_t info, int *pBufferSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseScsrilu02_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseScsrilu02_bufferSize = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cusparseMatDescr_t, float *, const int *, const int *, csrilu02Info_t, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseScsrilu02_bufferSize");
			fprintf(stderr, "wrapper_cusparseScsrilu02_bufferSize:%p\n", wrapper_cusparseScsrilu02_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseScsrilu02_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseScsrilu02_bufferSize(handle, m, nnz, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, info, pBufferSizeInBytes);
		return retval;
	}
}