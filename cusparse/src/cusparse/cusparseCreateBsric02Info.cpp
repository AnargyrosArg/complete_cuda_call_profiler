#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCreateBsric02Info)(bsric02Info_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCreateBsric02Info(bsric02Info_t *info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCreateBsric02Info)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCreateBsric02Info = (cusparseStatus_t (*)(bsric02Info_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCreateBsric02Info");
			fprintf(stderr, "wrapper_cusparseCreateBsric02Info:%p\n", wrapper_cusparseCreateBsric02Info);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCreateBsric02Info():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCreateBsric02Info(info);
		return retval;
	}
}