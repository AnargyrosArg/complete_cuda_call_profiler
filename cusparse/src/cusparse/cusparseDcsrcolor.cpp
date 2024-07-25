#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDcsrcolor)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const double *, const int *, const int *, const double *, int *, int *, int *, const cusparseColorInfo_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDcsrcolor(cusparseHandle_t handle, int m, int nnz, const cusparseMatDescr_t descrA, const double *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, const double *fractionToColor, int *ncolors, int *coloring, int *reordering, const cusparseColorInfo_t info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDcsrcolor)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDcsrcolor = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const double *, const int *, const int *, const double *, int *, int *, int *, const cusparseColorInfo_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDcsrcolor");
			fprintf(stderr, "wrapper_cusparseDcsrcolor:%p\n", wrapper_cusparseDcsrcolor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDcsrcolor():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDcsrcolor(handle, m, nnz, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, fractionToColor, ncolors, coloring, reordering, info);
		return retval;
	}
}