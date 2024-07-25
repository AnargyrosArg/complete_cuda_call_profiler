#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCreateSpVec)(cusparseSpVecDescr_t *, int64_t, int64_t, void *, void *, cusparseIndexType_t, cusparseIndexBase_t, cudaDataType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCreateSpVec(cusparseSpVecDescr_t *spVecDescr, int64_t size, int64_t nnz, void *indices, void *values, cusparseIndexType_t idxType, cusparseIndexBase_t idxBase, cudaDataType valueType) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCreateSpVec)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCreateSpVec = (cusparseStatus_t (*)(cusparseSpVecDescr_t *, int64_t, int64_t, void *, void *, cusparseIndexType_t, cusparseIndexBase_t, cudaDataType)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCreateSpVec");
			fprintf(stderr, "wrapper_cusparseCreateSpVec:%p\n", wrapper_cusparseCreateSpVec);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCreateSpVec():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCreateSpVec(spVecDescr, size, nnz, indices, values, idxType, idxBase, valueType);
		return retval;
	}
}