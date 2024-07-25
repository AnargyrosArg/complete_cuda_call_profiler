#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseDiagType_t (*wrapper_cusparseGetMatDiagType)(const cusparseMatDescr_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseDiagType_t cusparseGetMatDiagType(const cusparseMatDescr_t descrA) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseGetMatDiagType)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseGetMatDiagType = (cusparseDiagType_t (*)(const cusparseMatDescr_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseGetMatDiagType");
			fprintf(stderr, "wrapper_cusparseGetMatDiagType:%p\n", wrapper_cusparseGetMatDiagType);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseGetMatDiagType():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseDiagType_t retval = wrapper_cusparseGetMatDiagType(descrA);
		return retval;
	}
}