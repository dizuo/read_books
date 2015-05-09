
# compile java source files.

class_dir=./classes_out

if [ ! -d $class_dir ];
then
	mkdir $class_dir
fi

# move classes to class_dir
javac -d $class_dir JavaTest.java

cd $class_dir

# run java.
java dizuo.java.JavaTest

cd ../
