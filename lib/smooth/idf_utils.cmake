function(verify_idf_path)
    if (NOT EXISTS "$ENV{IDF_PATH}/Kconfig")
        message(FATAL_ERROR "Environment IDF_PATH must be set to an existing IDF-installation. IDF_PATH: '$ENV{IDF_PATH}'")
    else ()
        message(STATUS "IDF_PATH appears valid.")
    endif ()
endfunction()