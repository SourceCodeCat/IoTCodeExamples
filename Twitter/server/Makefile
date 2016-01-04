all:	javatwitterserver/JavaTwitterServer.class  

javatwitterserver/JavaTwitterServer.class:	
	javac -classpath libs/twitter4j-core-4.0.4.jar javatwitterserver/JavaTwitter.java javatwitterserver/JavaTwitterServer.java
	echo "Creating GoServer launcher..."
	echo "java -cp .:libs/twitter4j-core-4.0.4.jar javatwitterserver/JavaTwitterServer 1982" > GoServer
	chmod +x GoServer
        echo "Launcher created and server when executed will listen to port 1982"
        	
clean:	
	rm javatwitterserver/*.class GoServer
