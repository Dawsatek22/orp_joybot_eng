cmake_minimum_required(VERSION 3.25.1)
project(orp_joybot.eng)

add_executable(dctest1 src/dctest1.cpp) # Code to test dc motor and direction.
add_executable(main src/main.cpp) # main code  direction.
add_executable(joytest src/testjoy.cpp) # code to test  the joystick  controls.
target_link_libraries(main -lwiringPi) # links wiringPi to main.
target_link_libraries(dctest1 -lwiringPi) # links wiringPi to dctest1.
