################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ball.cpp \
../circle.cpp \
../constants.cpp \
../cue.cpp \
../main.cpp \
../point2D.cpp \
../scene.cpp \
../segment.cpp \
../vector2D.cpp 

OBJS += \
./ball.o \
./circle.o \
./constants.o \
./cue.o \
./main.o \
./point2D.o \
./scene.o \
./segment.o \
./vector2D.o 

CPP_DEPS += \
./ball.d \
./circle.d \
./constants.d \
./cue.d \
./main.d \
./point2D.d \
./scene.d \
./segment.d \
./vector2D.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


