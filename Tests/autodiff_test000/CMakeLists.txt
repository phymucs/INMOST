project(autodiff_test000)
set(SOURCE main.cpp)

add_executable(autodiff_test000 ${SOURCE})
target_link_libraries(autodiff_test000 inmost)

if(USE_MPI)
  message("linking autodiff_test000 with MPI")
  target_link_libraries(autodiff_test000 ${MPI_LIBRARIES}) 
  if(MPI_LINK_FLAGS)
    set_target_properties(autodiff_test000 PROPERTIES LINK_FLAGS "${MPI_LINK_FLAGS}")
  endif() 
endif(USE_MPI)



add_test(NAME autodiff_test000_hessian_sin                 COMMAND $<TARGET_FILE:autodiff_test000> 0)
add_test(NAME autodiff_test000_hessian_sin_of_poly           COMMAND $<TARGET_FILE:autodiff_test000> 1)
add_test(NAME autodiff_test000_hessian_cos_of_poly           COMMAND $<TARGET_FILE:autodiff_test000> 2)
add_test(NAME autodiff_test000_hessian_sin_mult           COMMAND $<TARGET_FILE:autodiff_test000> 3)
add_test(NAME autodiff_test000_hessian_cos_mult           COMMAND $<TARGET_FILE:autodiff_test000> 4)
add_test(NAME autodiff_test000_hessian_sqrt_mixed           COMMAND $<TARGET_FILE:autodiff_test000> 5)
add_test(NAME autodiff_test000_hessian_poly           COMMAND $<TARGET_FILE:autodiff_test000> 6)
add_test(NAME autodiff_test000_hessian_sin_poly           COMMAND $<TARGET_FILE:autodiff_test000> 7)
add_test(NAME autodiff_test000_hessian_const_minus_sin_of_poly           COMMAND $<TARGET_FILE:autodiff_test000> 8)
add_test(NAME autodiff_test000_hessian_const_minus_cos_of_poly           COMMAND $<TARGET_FILE:autodiff_test000> 9)
