#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseMatrixType_t (*wrapper_cusparseGetMatType)(const cusparseMatDescr_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseMatrixType_t cusparseGetMatType(const cusparseMatDescr_t descrA) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseGetMatType)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseGetMatType = (cusparseMatrixType_t (*)(const cusparseMatDescr_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseGetMatType");
			fprintf(stderr, "wrapper_cusparseGetMatType:%p\n", wrapper_cusparseGetMatType);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseGetMatType():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseMatrixType_t retval = wrapper_cusparseGetMatType(descrA);
		return retval;
	}
}