include_guard()
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

  target_link_libraries(${EXE_NAME} PUBLIC spdlog::spdlog Game)
  target_link_libraries(Game PUBLIC spdlog::spdlog)
endfunction()

function(practice)
  message("-- Reading Practice Function...")
  set(newList "")
  set(index 1)

  # Read and print index value
  while(index LESS 10)
    message("-- index = ${index}")
    
    # Perform index + 10 then add to newList
    math(EXPR varToNewList "${index} + 10")
    list(APPEND newList ${varToNewList})

    # Increment index variable
    math(EXPR incremented "${index} + 1")
    set(index ${incremented})
  endwhile()

  # Read and print newList
  foreach(number IN LISTS newList)
    message("-- newList: ${number}")
  endforeach()
endfunction()
