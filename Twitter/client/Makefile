all: javasocketclient/JavaSocketClient.class

javasocketclient/JavaSocketClient.class:
	@echo "Compiling code..."
	@javac javasocketclient/JavaSocketClient.java
	@echo "creating launcher..."
	@echo 'java -cp . javasocketclient.JavaSocketClient $$1 $$2 "$$3"' > GoClient
	@chmod +x GoClient
	@echo "READY!!.."
	@echo "Now you can execute the client like this: ./GoClient SERVER_IP SERVER_PORT \"MESSAGE\""

clean:
	@echo "Cleansing..."
	@rm javasocketclient/*.class GoClient
	@echo "Done."
