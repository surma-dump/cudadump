#include <stdio.h>
#include <cuda.h>

int checkFail(CUresult e) {
	if(e != CUDA_SUCCESS) {
		printf("***Failed!***");
		return 1;
	}
	return 0;
}

int main() {
	int i, devCount;
	CUdevice dev;
	CUdevprop prop;
	CUresult e;

	cuInit(0);
	cuDeviceGetCount(&devCount);
	for(i = 0; i < devCount; i++) {
		e = cuDeviceGet(&dev, i);
		if(e != CUDA_SUCCESS) {
			printf("cuDeviceGet(%d) failed\n", i);
			continue;
		}
		e = cuDeviceGetProperties(&prop, dev);
		if(e != CUDA_SUCCESS) {
			printf("Could not get device properties");
			continue;
		}

		printf("Card #%02d:\n", i);

		printf("\tName: ");
		{
			char buf[1024];
			e = cuDeviceGetName(buf, 1024, dev);
			checkFail(e) ||
			printf("%s", buf);
			printf("\n");
		}

		printf("\tCompute capability: ");
		{
			int major, minor;
			e = cuDeviceComputeCapability(&major, &minor, dev);
			checkFail(e) ||
			printf("%d.%d", major, minor);
			printf("\n");
		}

		printf("\tTotal memory: ");
		{
			size_t mem;
			e = cuDeviceTotalMem(&mem, dev);
			checkFail(e) ||
			printf("%lu bytes", mem);
			printf("\n");
		}

		printf("\tClock rate: ");
		{
			printf("%d kHz", prop.clockRate);
			printf("\n");
		}

		printf("\tGrid dimensions: ");
		{
			printf("%d x %d x %d", prop.maxGridSize[0], prop.maxGridSize[1], prop.maxGridSize[2]);
			printf("\n");
		}

		printf("\tThread dimensions: ");
		{
			printf("%d x %d x %d", prop.maxThreadsDim[0], prop.maxThreadsDim[1], prop.maxThreadsDim[2]);
			printf("\n");
		}

		printf("\tThreads per block: ");
		{
			printf("%d", prop.maxThreadsPerBlock);
			printf("\n");
		}

		printf("\tShared memory per block: ");
		{
			printf("%d bytes", prop.sharedMemPerBlock);
			printf("\n");
		}

		printf("\tConstant memory: ");
		{
			printf("%d bytes", prop.totalConstantMemory);
			printf("\n");
		}

		printf("\tWarp size: ");
		{
			int attr;
			e = cuDeviceGetAttribute(&attr, CU_DEVICE_ATTRIBUTE_WARP_SIZE, dev);
			checkFail(e) ||
			printf("%d", attr);
			printf("\n");
		}

		printf("\tNumber of multiprocessors: ");
		{
			int attr;
			e = cuDeviceGetAttribute(&attr, CU_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT, dev);
			checkFail(e) ||
			printf("%d", attr);
			printf("\n");
		}

		printf("\tIs integrated: ");
		{
			int attr;
			e = cuDeviceGetAttribute(&attr, CU_DEVICE_ATTRIBUTE_INTEGRATED, dev);
			checkFail(e) ||
			printf("%s", attr!=0?"yes":"no");
			printf("\n");
		}

		printf("\tCan map host memory: ");
		{
			int attr;
			e = cuDeviceGetAttribute(&attr, CU_DEVICE_ATTRIBUTE_CAN_MAP_HOST_MEMORY, dev);
			checkFail(e) ||
			printf("%s", attr!=0?"yes":"no");
			printf("\n");
		}

		printf("\tCan execute multiple kernels: ");
		{
			int attr;
			e = cuDeviceGetAttribute(&attr, CU_DEVICE_ATTRIBUTE_CONCURRENT_KERNELS, dev);
			checkFail(e) ||
			printf("%s", attr!=0?"yes":"no");
			printf("\n");
		}

		printf("\tThreads per multiprocessor: ");
		{
			int attr;
			e = cuDeviceGetAttribute(&attr, CU_DEVICE_ATTRIBUTE_MAX_THREADS_PER_MULTIPROCESSOR, dev);
			checkFail(e) ||
			printf("%d", attr);
			printf("\n");
		}

		printf("\tAsynchronous engines: ");
		{
			int attr;
			e = cuDeviceGetAttribute(&attr, CU_DEVICE_ATTRIBUTE_ASYNC_ENGINE_COUNT, dev);
			checkFail(e) ||
			printf("%d", attr);
			printf("\n");
		}

		printf("\tShares address space with host: ");
		{
			int attr;
			e = cuDeviceGetAttribute(&attr, CU_DEVICE_ATTRIBUTE_UNIFIED_ADDRESSING, dev);
			checkFail(e) ||
			printf("%s", attr!=0?"yes":"no");
			printf("\n");
		}

		printf("\tL2 cache: ");
		{
			int attr;
			e = cuDeviceGetAttribute(&attr, CU_DEVICE_ATTRIBUTE_L2_CACHE_SIZE, dev);
			checkFail(e) ||
			printf("%d bytes", attr);
			printf("\n");
		}
	}
}
