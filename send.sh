echo "Configuring serial port..."
stty 1000000 -F /dev/ttyUSB0 raw -echo
echo "Linking the file descriptor to the board..."
exec 3<>/dev/ttyUSB0
sleep 4
previous_time=0
fps=0
current_frame=0

echo "Sending binary data..."
for (( frame=0; frame < 6572; frame++ ))
do
	for (( shift=0; shift < 16; shift++ ))
	do
		clear
		echo -e "Frame: $frame\nPart: $shift"
		echo "FPS: $fps"
		dd bs=44 obs=44 count=1 skip=$(( $frame * 16 + $shift )) if=frames of=/dev/fd/3 status=none
		read -N 1 -s -u 3
	done
	
	(( current_frame++ ))
	current_time=`date +"%S"`
	if (( current_time != $previous_time ))
	then
		previous_time=$current_time
		fps=$current_frame
		current_frame=0
	fi
done

echo "Exiting..."
exec 3>&-

