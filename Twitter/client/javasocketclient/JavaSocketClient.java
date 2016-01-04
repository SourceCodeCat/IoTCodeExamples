/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javasocketclient;

import java.net.*;
import java.io.*;
/**
 *
 * @author marco antonio salgado martinez
 * @email ing.marco@gmail.com
 */
public class JavaSocketClient
{
   /*
	The client receives two arguments:
        -server IP
        -server PORT
   */
   public static void main(String [] args)
   {
      String serverName = args[0];//"192.168.1.75";//
      int port = Integer.parseInt(args[1]);//2125;//
      String message = args[2];
      try
      {
         System.out.println("Connecting to " + serverName +
		 " on port " + port);
         Socket client = new Socket(serverName, port);
         System.out.println("Just connected to " 
		 + client.getRemoteSocketAddress());
         OutputStream outToServer = client.getOutputStream();
         DataOutputStream out = new DataOutputStream(outToServer);
         out.writeUTF(message);
         //out.writeUTF("Hello from "
         //             + client.getLocalSocketAddress());
         InputStream inFromServer = client.getInputStream();
         DataInputStream in =
                        new DataInputStream(inFromServer);
         System.out.println("Server says " + in.readUTF());
         client.close();
      }catch(IOException e)
      {
         e.printStackTrace();
      }
   }
}
