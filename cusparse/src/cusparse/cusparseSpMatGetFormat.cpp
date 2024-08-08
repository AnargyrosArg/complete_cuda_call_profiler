#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpMatGetFormat)(cusparseSpMatDescr_t, cusparseFormat_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpMatGetFormat(cusparseSpMatDescr_t spMatDescr, cusparseFormat_t *format) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpMatGetFormat)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpMatGetFormat = (cusparseStatus_t (*)(cusparseSpMatDescr_t, cusparseFormat_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpMatGetFormat");
			fprintf(stderr, "wrapper_cusparseSpMatGetFormat:%p\n", wrapper_cusparseSpMatGetFormat);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpMatGetFormat():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpMatGetFormat(spMatDescr, format);
		return retval;
	}
}