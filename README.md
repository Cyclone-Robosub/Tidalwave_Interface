# Tidewave-Interface
 GUI for robot control and monitoring

## Build Enviornment
Bash Lines are copy and paste friendly.

If on Macbook \
&ensp;	If on ros2 enviornment \
&ensp;&ensp;		Starting in main folder \
&ensp;&ensp;&ensp;		```bash
		cd Backend
		cd custom_interfaces
		colcon build &
		source install/setup.bash
		cd ../../
		colcon build --cmake-args -DQTBuild=OFF & 
		cd build
		./tidalwave_ros2_only
		``` \
&ensp;&ensp; else \
&ensp;&ensp;&ensp;	```bash \
&ensp;&ensp;&ensp;		mkdir build \
&ensp;&ensp;&ensp;		cd build \
&ensp;&ensp;&ensp;		cmake .. \
&ensp;&ensp;&ensp;		./Tidalwave_InterfaceApp \
&ensp;&ensp; end-if \
else \
&ensp;	NOT DEVELOPED.
&ensp;&ensp; end-if \
