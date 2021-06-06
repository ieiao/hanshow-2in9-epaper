SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

PROJECT(hanshow-2in9-epaper C)

SET(CROSS_COMPILE "msp430-elf-")
SET(CMAKE_C_COMPILER ${CROSS_COMPILE}gcc)
SET(CMAKE_CXX_COMPILER ${CROSS_COMPILE}g++)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mmcu=msp430g2553")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffunction-sections")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdata-sections")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Xlinker --gc-sections")

set(EXECUTABLE_ELF ".elf")

add_executable(${PROJECT_NAME}.elf
               main.c epd-2in9.c)

add_custom_target(flash
                  COMMAND sudo mspdebug rf2500 "prog ${PROJECT_NAME}.elf"
                  DEPENDS ${EXECUTABLE})