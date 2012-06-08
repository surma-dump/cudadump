`cudadump` dumps information about all your CUDA-enabled GPUs to screen via the CUDA driver API.

# Compiling and running

```bash
	make
	./cudadump
```

If you want to choose a different compiler than `clang` or adjust the path to the CUDA tree, you can use the `CC` and `CUDAPATH` environment variables.
