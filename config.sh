echo "Please provide your password if and when prompted"
$PKGs = $(dpkg-query -W --showformat='${Status}\n' sysvbanner|grep "install ok installed")

echo $PKGs

if [ "$PKGs" == "install installed ok" ]; then
	sudo apt-get install sysvbanner
else
	echo "Required packages installed"
fi
