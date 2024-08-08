#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXcoosortByColumn)(cusparseHandle_t, int, int, int, int *, int *, int *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXcoosortByColumn(cusparseHandle_t handle, int m, int n, int nnz, int *cooRowsA, int *cooColsA, int *P, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXcoosortByColumn)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXcoosortByColumn = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, int *, int *, int *, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXcoosortByColumn");
			fprintf(stderr, "wrapper_cusparseXcoosortByColumn:%p\n", wrapper_cusparseXcoosortByColumn);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXcoosortByColumn():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXcoosortByColumn(handle, m, n, nnz, cooRowsA, cooColsA, P, pBuffer);
		return retval;
	}
}