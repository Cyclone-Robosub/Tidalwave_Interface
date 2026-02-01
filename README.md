# Tidewave-Interface
 GUI for robot control and monitoring

## Build Enviornment
Bash Scripts are copy and paste friendly.

If on Macbook
	If on ros2 enviornment
		Starting in main folder
		```bash
		cd Backend
		cd custom_interfaces
		colcon build &
		source install/setup.bash
		cd ../../
		colcon build --cmake-args -DQTBuild=OFF & 
		cd build
		./tidalwave_ros2_only
		```
	else 
		```bash
		mkdir build
		cd build
		cmake ..
		./Tidalwave_InterfaceApp
else
	NOT DEVELOPED.
		