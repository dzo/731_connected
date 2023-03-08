
#########################################################
# Source Files
#########################################################

SET(sources	"main.cpp")

add_executable(main ${sources})

# Link with OpenCV Library
target_link_libraries(main PRIVATE ${OpenCV_LIBS})