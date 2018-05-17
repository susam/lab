test: build
	java -cp .:junit3.jar junit.textui.TestRunner JUnit3Demo
	java -cp .:junit4.jar:hamcrest-core.jar org.junit.runner.JUnitCore JUnit4Demo
	#
	# By default ConsoleLauncher looks for class names that begin
	# with "Test" or end with "Test" or "Tests", so the -n option is
	# necessary.
	java -cp .:junit5.jar org.junit.platform.console.ConsoleLauncher -n "JUnit.*" --scan-classpath
	java -jar junit5.jar -cp . -n "JUnit.*" --scan-classpath
	#
	# Without the -n option, only classes with names that begin with
	# "Test" or end with "Test" or "Tests" are run.
	java -cp .:junit5.jar org.junit.platform.console.ConsoleLauncher --scan-classpath
	java -jar junit5.jar -cp . --scan-classpath

build:
	javac -cp junit3.jar JUnit3Demo.java
	javac -cp junit4.jar JUnit4Demo.java
	javac -cp junit5.jar JUnit5Demo.java
	javac -cp junit5.jar JUnit5DemoTest.java

download:
	wget -O junit3.jar http://search.maven.org/remotecontent?filepath=junit/junit/3.8.2/junit-3.8.2.jar
	wget -O junit4.jar http://search.maven.org/remotecontent?filepath=junit/junit/4.12/junit-4.12.jar
	wget -O hamcrest-core.jar http://search.maven.org/remotecontent?filepath=org/hamcrest/hamcrest-core/1.3/hamcrest-core-1.3.jar
	wget -O junit5.jar http://search.maven.org/remotecontent?filepath=org/junit/platform/junit-platform-console-standalone/1.2.0/junit-platform-console-standalone-1.2.0.jar
