include_guard()

if (NOT CGAL::CGAL)
    FetchContent_Declare(
        CGAL
        GIT_REPOSITORY https://github.com/CGAL/cgal.git
        GIT_TAG        v5.4
        GIT_SHALLOW TRUE
    )
    if (NOT cgal_POPULATED)
        FetchContent_Populate(CGAL)
        find_package(CGAL CONFIG COMPONENTS Core PATHS ${cgal_SOURCE_DIR}
            NO_DEFAULT_PATH REQUIRED)
    endif()
endif()
