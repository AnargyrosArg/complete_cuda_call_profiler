#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDestroyCsru2csrInfo)(csru2csrInfo_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDestroyCsru2csrInfo(csru2csrInfo_t info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDestroyCsru2csrInfo)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDestroyCsru2csrInfo = (cusparseStatus_t (*)(csru2csrInfo_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDestroyCsru2csrInfo");
			fprintf(stderr, "wrapper_cusparseDestroyCsru2csrInfo:%p\n", wrapper_cusparseDestroyCsru2csrInfo);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDestroyCsru2csrInfo():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDestroyCsru2csrInfo(info);
		return retval;
	}
}