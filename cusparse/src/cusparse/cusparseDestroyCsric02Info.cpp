#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDestroyCsric02Info)(csric02Info_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDestroyCsric02Info(csric02Info_t info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDestroyCsric02Info)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDestroyCsric02Info = (cusparseStatus_t (*)(csric02Info_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDestroyCsric02Info");
			fprintf(stderr, "wrapper_cusparseDestroyCsric02Info:%p\n", wrapper_cusparseDestroyCsric02Info);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDestroyCsric02Info():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDestroyCsric02Info(info);
		return retval;
	}
}