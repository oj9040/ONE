add_nnfw_custom_op_kernel(FillFrom ON kernels/FillFromKernel.cc)
add_nnfw_custom_op_app(FillFrom_runner
                       SOURCES FillFrom_runner.cc
                       KERNELS FillFrom)
install(TARGETS FillFrom_runner DESTINATION tests)
install(DIRECTORY nnpkgs/FillFrom DESTINATION tests/nnpkgs)
install_nnfw_custom_op_kernel(FillFrom tests/nnpkgs/FillFrom)
