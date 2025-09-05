# test player output 
echo "5" > input.txt
echo "Invalid number of players. Using 3 instead." > expectedoutput.txt
./lrc < input.txt > output.txt

if diff output.txt expectedoutput expectedoutput.txt; then
	echo "Passed"
else
	echo "Failed"
fi

rm -f input.txt output.txt expectedoutput.txt
exit 0 

