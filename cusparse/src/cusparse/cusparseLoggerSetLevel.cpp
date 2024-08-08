#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseLoggerSetLevel)(int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseLoggerSetLevel(int level) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseLoggerSetLevel)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseLoggerSetLevel = (cusparseStatus_t (*)(int)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseLoggerSetLevel");
			fprintf(stderr, "wrapper_cusparseLoggerSetLevel:%p\n", wrapper_cusparseLoggerSetLevel);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseLoggerSetLevel():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseLoggerSetLevel(level);
		return retval;
	}
}