#!/bin/tcsh
if ($# != 1) then
	echo "Usage: input_generator.sh <number of elements to generate and test>"
	exit 1
endif

foreach x (`seq 1 $1`) #`seq 0 2` = 0 1 2
	set y = `bash -c 'echo "$RANDOM"'`
	echo "INSERT $y";
	echo "SEARCH $y";
end
echo "QUIT"
