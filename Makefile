all:
	mkdir -p bin/genfiles
	cd src; make

docs:
	cd report; make

clean:
	cd src; make clean
	cd report; make clean