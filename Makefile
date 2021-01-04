all: monitor/prog matrices/prog

monitor/prog:
	cd ./monitor && make
matrices/prog:
	cd ./matrices && make

.PHONY: all
