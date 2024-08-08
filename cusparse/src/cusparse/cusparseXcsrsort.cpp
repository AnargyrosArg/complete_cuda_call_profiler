#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXcsrsort)(cusparseHandle_t, int, int, int, const cusparseMatDescr_t, const int *, int *, int *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXcsrsort(cusparseHandle_t handle, int m, int n, int nnz, const cusparseMatDescr_t descrA, const int *csrRowPtrA, int *csrColIndA, int *P, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXcsrsort)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXcsrsort = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, const cusparseMatDescr_t, const int *, int *, int *, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXcsrsort");
			fprintf(stderr, "wrapper_cusparseXcsrsort:%p\n", wrapper_cusparseXcsrsort);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXcsrsort():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXcsrsort(handle, m, n, nnz, descrA, csrRowPtrA, csrColIndA, P, pBuffer);
		return retval;
	}
}