if (TARGET absl::base)
    return()
endif()

include(FetchContent)
FetchContent_Declare(
    absl
    GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
    GIT_TAG 20210324.2
    )

set(OLD_CXX_STANDARD ${CMAKE_CXX_STANDARD})
set(CMAKE_CXX_STANDARD 17)
FetchContent_MakeAvailable(absl)
set(CMAKE_CXX_STANDARD ${OLD_CXX_STANDARD})
