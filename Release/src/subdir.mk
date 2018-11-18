################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ApplicationModes.cpp \
../src/NetworkTemplate.cpp \
../src/UDPServer.cpp \
../src/configurationFile.cpp 

OBJS += \
./src/ApplicationModes.o \
./src/NetworkTemplate.o \
./src/UDPServer.o \
./src/configurationFile.o 

CPP_DEPS += \
./src/ApplicationModes.d \
./src/NetworkTemplate.d \
./src/UDPServer.d \
./src/configurationFile.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/ssl/include -I"/home/jdellaria/eclipse-workspace/DLiriumLib" -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


