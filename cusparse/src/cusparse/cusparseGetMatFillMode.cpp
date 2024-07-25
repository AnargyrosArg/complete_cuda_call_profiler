#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseFillMode_t (*wrapper_cusparseGetMatFillMode)(const cusparseMatDescr_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseFillMode_t cusparseGetMatFillMode(const cusparseMatDescr_t descrA) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseGetMatFillMode)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseGetMatFillMode = (cusparseFillMode_t (*)(const cusparseMatDescr_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseGetMatFillMode");
			fprintf(stderr, "wrapper_cusparseGetMatFillMode:%p\n", wrapper_cusparseGetMatFillMode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseGetMatFillMode():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseFillMode_t retval = wrapper_cusparseGetMatFillMode(descrA);
		return retval;
	}
}