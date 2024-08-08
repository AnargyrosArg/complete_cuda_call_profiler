#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCscSetPointers)(cusparseSpMatDescr_t, void *, void *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCscSetPointers(cusparseSpMatDescr_t spMatDescr, void *cscColOffsets, void *cscRowInd, void *cscValues) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCscSetPointers)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCscSetPointers = (cusparseStatus_t (*)(cusparseSpMatDescr_t, void *, void *, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCscSetPointers");
			fprintf(stderr, "wrapper_cusparseCscSetPointers:%p\n", wrapper_cusparseCscSetPointers);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCscSetPointers():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCscSetPointers(spMatDescr, cscColOffsets, cscRowInd, cscValues);
		return retval;
	}
}