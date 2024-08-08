#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCsrSetPointers)(cusparseSpMatDescr_t, void *, void *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCsrSetPointers(cusparseSpMatDescr_t spMatDescr, void *csrRowOffsets, void *csrColInd, void *csrValues) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCsrSetPointers)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCsrSetPointers = (cusparseStatus_t (*)(cusparseSpMatDescr_t, void *, void *, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCsrSetPointers");
			fprintf(stderr, "wrapper_cusparseCsrSetPointers:%p\n", wrapper_cusparseCsrSetPointers);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCsrSetPointers():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCsrSetPointers(spMatDescr, csrRowOffsets, csrColInd, csrValues);
		return retval;
	}
}