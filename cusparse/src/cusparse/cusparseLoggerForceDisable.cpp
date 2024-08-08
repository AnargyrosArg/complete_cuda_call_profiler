#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseLoggerForceDisable)();
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseLoggerForceDisable() {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseLoggerForceDisable)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseLoggerForceDisable = (cusparseStatus_t (*)()) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseLoggerForceDisable");
			fprintf(stderr, "wrapper_cusparseLoggerForceDisable:%p\n", wrapper_cusparseLoggerForceDisable);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseLoggerForceDisable():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseLoggerForceDisable();
		return retval;
	}
}