/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javatwitterserver;

/**
 *
 * @author marco
 */
import twitter4j.Twitter;
import twitter4j.TwitterException;
import twitter4j.TwitterFactory;
import twitter4j.auth.AccessToken;

public class JavaTwitter {   

    private String consumerKeyStr;// = "0PQVCVzW7teE9YICgja6yA";
    private String consumerSecretStr;// = "RFQqYGGVQyI7yIkwenHBlIyZgGCvRhrlCFX1mQedkqY";
    private String accessTokenStr; //= "366625255-LcJ23aWvYinNasqBdnaMpfBBsDnQmSE81oQcL433";
    private String accessTokenSecretStr;// = "qVFIMnnO6e6cugVNlmB48vwp3QWhzGANEUKztMXH3y7YM";  
    private Twitter twitter;
    AccessToken accessToken;

    public JavaTwitter(String consumerKeyStr, String consumerSecretStr, String accessTokenStr,String accessTokenSecretStr) {
        this.consumerKeyStr=consumerKeyStr;
        this.consumerSecretStr=consumerSecretStr;
        this.accessTokenStr=accessTokenStr;
        this.accessTokenSecretStr=accessTokenSecretStr;
        twitter = null;
        accessToken = null;
        
        try {
                twitter = new TwitterFactory().getInstance();                
                twitter.setOAuthConsumer(
                        this.consumerKeyStr, 
                        this.consumerSecretStr);                
                accessToken = new AccessToken(
                        this.accessTokenStr,
                        this.accessTokenSecretStr);
                twitter.setOAuthAccessToken(accessToken);
        } 
        catch (Exception e)
        {
            e.printStackTrace();
        }    
    }
    public void postTweet(String Message)
    {
        try
        {
            twitter.updateStatus(Message);
            System.out.println("Successfully updated the status in Twitter.");
        }
        catch (TwitterException te)
        {
            te.printStackTrace();
        }   
    }
    
    

    
}
