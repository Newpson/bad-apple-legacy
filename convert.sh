FRAMES="apple_original/*"
i=0

for frame in $FRAMES
do
	(( i=i+1 ))
	output="apple64x88/frame88-${i}.png"
	convert $frame -resize 85x64 -threshold 50% -resize 88x64 -background white -gravity center -extent 88x64 -negate $output
done
