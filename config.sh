echo "Please provide your password if and when prompted"
$PKGs=$(dpkg-query -W -f='${Status}\n' sysvbanner|grep "install ok installed")
if ["$PKGs" == ""]; then
	sudo apt-get install sysvbanner
else
	echo "Required packages installed"
fi
