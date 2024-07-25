#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXcoosortByRow)(cusparseHandle_t, int, int, int, int *, int *, int *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXcoosortByRow(cusparseHandle_t handle, int m, int n, int nnz, int *cooRowsA, int *cooColsA, int *P, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXcoosortByRow)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXcoosortByRow = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, int *, int *, int *, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXcoosortByRow");
			fprintf(stderr, "wrapper_cusparseXcoosortByRow:%p\n", wrapper_cusparseXcoosortByRow);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXcoosortByRow():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXcoosortByRow(handle, m, n, nnz, cooRowsA, cooColsA, P, pBuffer);
		return retval;
	}
}