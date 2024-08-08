#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCopyMatDescr)(cusparseMatDescr_t, const cusparseMatDescr_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCopyMatDescr(cusparseMatDescr_t dest, const cusparseMatDescr_t src) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCopyMatDescr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCopyMatDescr = (cusparseStatus_t (*)(cusparseMatDescr_t, const cusparseMatDescr_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCopyMatDescr");
			fprintf(stderr, "wrapper_cusparseCopyMatDescr:%p\n", wrapper_cusparseCopyMatDescr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCopyMatDescr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCopyMatDescr(dest, src);
		return retval;
	}
}