#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZcsrcolor)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const cuDoubleComplex *, const int *, const int *, const double *, int *, int *, int *, const cusparseColorInfo_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZcsrcolor(cusparseHandle_t handle, int m, int nnz, const cusparseMatDescr_t descrA, const cuDoubleComplex *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, const double *fractionToColor, int *ncolors, int *coloring, int *reordering, const cusparseColorInfo_t info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZcsrcolor)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZcsrcolor = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const cuDoubleComplex *, const int *, const int *, const double *, int *, int *, int *, const cusparseColorInfo_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZcsrcolor");
			fprintf(stderr, "wrapper_cusparseZcsrcolor:%p\n", wrapper_cusparseZcsrcolor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZcsrcolor():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZcsrcolor(handle, m, nnz, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, fractionToColor, ncolors, coloring, reordering, info);
		return retval;
	}
}