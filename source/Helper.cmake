message("-- Loading file ${CMAKE_CURRENT_LIST_FILE}")

function(find_packages packages)
  message("-- Finding packages...")

  foreach(package IN LISTS packages)
    find_package(${package})

    if (TARGET ${package}::${package})
      message("-- Package ${package} successfully found.")
      list(APPEND PACKAGES_FOUND ${package})
    else()
      message("-- Package ${package} failed to find.")
    endif()
  endforeach()

  message("-- Packages that currently found:")
  foreach(package IN LISTS PACKAGES_FOUND)
   message("-- ${package}") 
  endforeach()
endfunction()

function(link_all)
  message("-- Linking all targets...")

  target_link_libraries(${EXE_NAME} PUBLIC spdlog)
endfunction()















function(print_list_details user_list)
  list(LENGTH user_list length)

  message("---- List Values: ${user_list}")
  message("---- List Length: ${length}")
endfunction()

function(prac new_list)
  set(myVar A B C D E)
  list(LENGTH myVar myVarLength)
  print_list_details("${myVar}")
  list(APPEND myVar "${ARGV}")
  print_list_details("${myVar}")
endfunction()
