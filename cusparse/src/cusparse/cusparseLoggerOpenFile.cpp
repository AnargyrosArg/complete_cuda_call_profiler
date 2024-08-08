#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseLoggerOpenFile)(const char *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseLoggerOpenFile(const char *logFile) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseLoggerOpenFile)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseLoggerOpenFile = (cusparseStatus_t (*)(const char *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseLoggerOpenFile");
			fprintf(stderr, "wrapper_cusparseLoggerOpenFile:%p\n", wrapper_cusparseLoggerOpenFile);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseLoggerOpenFile():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseLoggerOpenFile(logFile);
		return retval;
	}
}