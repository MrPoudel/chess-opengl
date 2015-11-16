#Description

This project was developed during my subject "Visual Computing" in Aveiro University.

The objective of the subject was to develop a project that would represent our knowledge that we learnt during all semester, then I choose to make a game (I really like to develop games for fun), in this case, a Chess game in OpenGL, the result is pretty interesting, I hope you enjoy.

#Installation

This was tested and developed on Ubuntu 14.10, it might work easily in any other debian distros but you will need to look better at dependencies names if you want to install in any other distro. It is also possible to install in Windows, but you will have to look closely at the includes and fix them. I had no time to worry about that.

Dependencies name:
* build-essential
* qt4-qmake
* libglew-dev
* freeglut3-dev

Use the following command to install the dependencies name:
```
sudo apt-get install <dependency>
```

After install all the dependencies you will be able to run the Makefile without any erros.
Execute ``` make ``` at the root folder of the repository.

Now to execute the program go to the folder bin and run the file chess.
Running the following line in bin folder: ``` ./chess ```

There's already an executable pre-generated in Ubuntu 14.04 (it might not work in other version), you might give it a try if you want to use it without compiling all the source code. The file name is ``` chess_bin64 ``` in the same folder.

All the code is also available on folder src.
