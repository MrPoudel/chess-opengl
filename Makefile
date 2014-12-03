all:
	mkdir -p bin/genfiles
	cd src; qmake qmake.pro; make

docs:
	cd report; make

clean:
	cd src; qmake qmake.pro; make clean
	cd report; make clean