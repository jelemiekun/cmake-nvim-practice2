include_guard()
message(STATUS "Loading ${CMAKE_CURRENT_LIST_FILE}")

function(loop init_index)
  set(local_index ${init_index})

  while(local_index LESS 10)
    message(STATUS "Local index: ${local_index}")
    math(EXPR local_index "${local_index} + 1")
  endwhile()
endfunction()



set(init_index 1)

message(STATUS "Initial index before the loop: ${init_index}")
loop(${init_index})
message(STATUS "Initial index after the loop: ${init_index}")


