#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCreateDnVec)(cusparseDnVecDescr_t *, int64_t, void *, cudaDataType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCreateDnVec(cusparseDnVecDescr_t *dnVecDescr, int64_t size, void *values, cudaDataType valueType) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCreateDnVec)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCreateDnVec = (cusparseStatus_t (*)(cusparseDnVecDescr_t *, int64_t, void *, cudaDataType)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCreateDnVec");
			fprintf(stderr, "wrapper_cusparseCreateDnVec:%p\n", wrapper_cusparseCreateDnVec);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCreateDnVec():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCreateDnVec(dnVecDescr, size, values, valueType);
		return retval;
	}
}