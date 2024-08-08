#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXcoo2csr)(cusparseHandle_t, const int *, int, int, int *, cusparseIndexBase_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXcoo2csr(cusparseHandle_t handle, const int *cooRowInd, int nnz, int m, int *csrSortedRowPtr, cusparseIndexBase_t idxBase) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXcoo2csr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXcoo2csr = (cusparseStatus_t (*)(cusparseHandle_t, const int *, int, int, int *, cusparseIndexBase_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXcoo2csr");
			fprintf(stderr, "wrapper_cusparseXcoo2csr:%p\n", wrapper_cusparseXcoo2csr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXcoo2csr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXcoo2csr(handle, cooRowInd, nnz, m, csrSortedRowPtr, idxBase);
		return retval;
	}
}