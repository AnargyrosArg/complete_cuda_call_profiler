#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDestroySpMat)(cusparseSpMatDescr_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDestroySpMat(cusparseSpMatDescr_t spMatDescr) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDestroySpMat)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDestroySpMat = (cusparseStatus_t (*)(cusparseSpMatDescr_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDestroySpMat");
			fprintf(stderr, "wrapper_cusparseDestroySpMat:%p\n", wrapper_cusparseDestroySpMat);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDestroySpMat():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDestroySpMat(spMatDescr);
		return retval;
	}
}