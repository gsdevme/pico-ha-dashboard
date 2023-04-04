cmake_minimum_required(VERSION 3.16)

include(pico-sdk/pico_sdk_init.cmake)

project(PicoHaDashboard)
set(PICO_BOARD pico_w)
set(CMAKE_C STANDARD 11)
set(CMAKE_CXX STANDARD 17)

pico_sdk_init()

add_executable(PicoHaDashboard main.cpp)

# Link with the pico stdlib
target_link_libraries(PicoHaDashboard pico_stdlib pico_cyw43_arch_none hardware_spi)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(PicoHaDashboard)

# Enable USB serial
pico_enable_stdio_usb(PicoHaDashboard 1)
# Disable UART
pico_enable_stdio_uart(PicoHaDashboard 0)