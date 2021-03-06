#ifndef __GPU_H__
#define __GPU_H__

#define OUTPUT_SIZE 16
#define MAX_WORK_SIZE 1024*1024

#include <stdbool.h>
#include <stdio.h>
#include <CL/cl.h>

typedef struct {
	cl_device_id device;
	cl_context context;
	cl_command_queue commandQueue;
	cl_kernel kernel;
	cl_kernel initKernel;
	cl_kernel init2Kernel;
	cl_kernel rndKernel;
	cl_kernel mixinKernel;
	cl_kernel resultKernel;

	cl_program program;
	cl_mem inputBuffer;
	cl_mem outputBuffer;
	cl_mem scratchpadBuffer;
	cl_mem stateBuffer;

	uint32_t type;
	uint64_t *output;
	uint32_t threadNumber;
	uint32_t scratchpad_size;
	bool update_scratchpad;
} GPU;

int scanhash_wildkeccak_gpu(int thr_id, GPU *gpu, uint32_t *pdata, const uint32_t *ptarget, uint32_t max_nonce, unsigned long *hashes_done);
void update_scratchpad_gpu(GPU *gpu, void* scratchpad, size_t size, int hashSize);

GPU* initGPU(uint32_t device_index, uint32_t id, uint32_t type);
void runGPU(GPU* gpu, uint32_t work_size, size_t offset, cl_ulong target);
void releaseGPU(GPU* gpu);
void CopyBufferToDevice(cl_command_queue queue, cl_mem buffer, void* h_Buffer, size_t size);
void CopyBufferToHost  (cl_command_queue queue, cl_mem buffer, void* h_Buffer, size_t size);

#endif /* __MINER_H__ */
