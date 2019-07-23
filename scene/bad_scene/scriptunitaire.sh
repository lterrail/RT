for f in *.rt
do
	echo $f
	../../rt $f
	echo
done
