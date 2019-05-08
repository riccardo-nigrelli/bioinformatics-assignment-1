if [[ "$OSTYPE" == "linux-gnu" ]]; then
	if ! [ -x "$(command -v dot)" ]; then
  	apt-get install graphviz
	fi

	mkdir out/
	
elif [[ "$OSTYPE" == "darwin"* ]]; then
	which -s brew
	if [[ $? != 0 ]] ; then
		ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
	fi
	which -s dot
	if [[ $? != 0 ]] ; then
		brew install graphviz
	fi

	mkdir out/
fi
