
# 
# Target 'docs'
# 

if(NOT OPTION_BUILD_DOCS)
    return()
endif()

add_custom_target(docs)

add_custom_target(pitch COMMAND pandoc -t beamer -V theme=Warsaw -V colortheme=wolverine ${CMAKE_SOURCE_DIR}/PITCHME.md -o PITCHME.pdf  -H "${CMAKE_SOURCE_DIR}/PITCHME.header.tex")

# 
# Documentation
# 

add_subdirectory(api-docs)
