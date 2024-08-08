#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDestroyMatDescr)(cusparseMatDescr_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDestroyMatDescr(cusparseMatDescr_t descrA) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDestroyMatDescr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDestroyMatDescr = (cusparseStatus_t (*)(cusparseMatDescr_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDestroyMatDescr");
			fprintf(stderr, "wrapper_cusparseDestroyMatDescr:%p\n", wrapper_cusparseDestroyMatDescr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDestroyMatDescr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDestroyMatDescr(descrA);
		return retval;
	}
}