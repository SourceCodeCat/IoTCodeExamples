/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javatwitterserver;
import java.io.*;
import java.net.*;

/**
 *
 * @author marco antonio salgado martinez
   @email ing.marco@gmail.com
 */
public class JavaTwitterServer extends Thread{
    
    private ServerSocket serverSocket;
    private static JavaTwitter javaTwitter;
    private String msg="";
    public JavaTwitterServer(int port) throws IOException
    {
        serverSocket = new ServerSocket(port);
        //serverSocket.setSoTimeout(10000);
    }    

    /**
     * @param args the command line arguments
	receives are Parameter the desired port that is going to be used and where clients will connect


	REMEMBER:
 	To replace consumerKeyStr,consumerSecretStr,accessTokenStr,accessTokenSecretStr below with your own strings... 

     */
    public static void main(String[] args) {
        // TODO code application logic here
      int port = Integer.parseInt(args[0]);
      try
      {
         javaTwitter= new JavaTwitter(
                 "------------------------", //reaplce dashes with own consumerKeyStr
                 "------------------------", //reaplce dashes with own consumerSecretStr
                 "------------------------", //reaplce dashes with own accessTokenStr
                 "------------------------"  //reaplce dashes with own accessTokenSecretStr
         ); 
         Thread t = new JavaTwitterServer(port);
         t.start();
      }
      catch(IOException e)
      {
         e.printStackTrace();
      }        
    }

   public void run()
   {
      while(true)
      {
         try
         {
            System.out.println("Waiting for client on port " +
            serverSocket.getLocalPort() + "...");
            Socket server = serverSocket.accept();
            System.out.println("Accepted connection from: "
                  + server.getRemoteSocketAddress());
            DataInputStream in =
                  new DataInputStream(server.getInputStream());
            msg = in.readUTF();
            System.out.println("Received Message: "+msg);
            javaTwitter.postTweet(msg);            
            DataOutputStream out = new DataOutputStream(server.getOutputStream());
            out.writeUTF("Thank you for connecting  "
              + server.getLocalSocketAddress() + "\nGoodbye!");
            server.close();
             System.out.println("Message Posted!");
         }catch(SocketTimeoutException s)
         {
            System.out.println("Socket timed out!");
            break;
         }catch(IOException e)
         {
            e.printStackTrace();
            break;
         }
      }
   }


    
    
}
