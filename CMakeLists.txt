cmake_minimum_required(VERSION 3.13...3.27)

set(PICO_PLATFORM rp2040)
set(PICO_BOARD pico)
set(PICO_COMPILER pico_arm_cortex_m0plus_gcc)
set(PICOTOOL_FETCH_FROM_GIT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/picotool)

# initialize pico-sdk from submodule
# note: this must happen before project()
include(pico-sdk/pico_sdk_init.cmake)
include(FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# set the project name
project(bfs)

set(CMAKE_C_STANDARD 11)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# add the project source files
add_executable(${CMAKE_PROJECT_NAME} src/main.c)

# add the project include directory
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ./src/)

# add stdlib
target_link_libraries(${CMAKE_PROJECT_NAME} pico_stdlib pico_async_context_freertos FreeRTOS-Kernel-Heap4)

# include custom linker script
# pico_set_linker_script(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/memmap_custom.ld)

# enable USB output, disable UART output
pico_enable_stdio_usb(${CMAKE_PROJECT_NAME} 0)
pico_enable_stdio_uart(${CMAKE_PROJECT_NAME} 1)

# create map/bin/hex/s/uf2 file in addition to ELF.
pico_add_extra_outputs(${CMAKE_PROJECT_NAME})

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex -R .eeprom -R .fuse -R .lock -R .signature $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O srec -R .eeprom -R .fuse -R .lock -R .signature $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.srec
    COMMENT "Copying ${CMAKE_PROJECT_NAME} files"
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    ADDITIONAL_CLEAN_FILES "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.hex;${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.srec"
)
