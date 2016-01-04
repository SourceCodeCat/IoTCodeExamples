all:	javatwitterserver/JavaTwitterServer.class  

javatwitterserver/JavaTwitterServer.class:	
	@echo "Compiling code..."
	@javac -classpath libs/twitter4j-core-4.0.4.jar javatwitterserver/JavaTwitter.java javatwitterserver/JavaTwitterServer.java
	@echo "Creating GoServer launcher..."
	@echo "Server when executed will listen to port 1982"
	@echo "java -cp .:libs/twitter4j-core-4.0.4.jar javatwitterserver/JavaTwitterServer 1982" > GoServer
	@chmod +x GoServer
	@echo "Done, you can now execute ./GoServer"
        
        	
clean:	
	@echo "Cleansing..."
	@rm javatwitterserver/*.class GoServer
	@echo "Done"
