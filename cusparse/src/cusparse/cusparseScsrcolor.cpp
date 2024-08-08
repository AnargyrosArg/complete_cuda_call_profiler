#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseScsrcolor)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const float *, const int *, const int *, const float *, int *, int *, int *, const cusparseColorInfo_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseScsrcolor(cusparseHandle_t handle, int m, int nnz, const cusparseMatDescr_t descrA, const float *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, const float *fractionToColor, int *ncolors, int *coloring, int *reordering, const cusparseColorInfo_t info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseScsrcolor)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseScsrcolor = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const float *, const int *, const int *, const float *, int *, int *, int *, const cusparseColorInfo_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseScsrcolor");
			fprintf(stderr, "wrapper_cusparseScsrcolor:%p\n", wrapper_cusparseScsrcolor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseScsrcolor():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseScsrcolor(handle, m, nnz, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, fractionToColor, ncolors, coloring, reordering, info);
		return retval;
	}
}