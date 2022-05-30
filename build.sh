if [ $DOCKER ];then
	cd /work
	cmake .
	make
else
	docker build -t wa .
	docker run --rm -v $PWD:/work wa
	docker image rm wa
fi
