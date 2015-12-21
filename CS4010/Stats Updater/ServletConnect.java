

import java.io.*;
import java.net.URI;
import java.net.URLEncoder;
import java.util.Iterator;
import java.util.Map;
import org.apache.http.client.methods.CloseableHttpResponse;  
import org.apache.http.client.methods.HttpUriRequest; 
import org.apache.http.client.methods.RequestBuilder;
import org.apache.http.impl.client.CloseableHttpClient;  
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;

public class ServletConnect {
	
	public static void main(String args[]){
		 //new ServletConnect().addDataServlet("Stars","Joe Jones","3","2","Add");
		 
	}
	
	public ServletConnect(){
		
	}
	
	//ADD
	public String addDataServlet(String team, String player, String goals, String assists, String function){
		CloseableHttpClient httpclient;
		
		String response_string="";
		
		try{
			CloseableHttpResponse httpresponse;
			httpclient = HttpClients.createDefault();
			HttpUriRequest httpuri = null;
			
			httpuri = RequestBuilder.post()
					.setUri(new URI("http://hoare.cs.umsl.edu/servlet/j-kedge/Servlet"))
					.addParameter("team", URLEncoder.encode(team, "UTF-8"))
					.addParameter("player", URLEncoder.encode(player, "UTF-8"))
					.addParameter("goals", URLEncoder.encode(goals, "UTF-8"))
					.addParameter("assists", URLEncoder.encode(assists, "UTF-8"))
					.addParameter("function", URLEncoder.encode(function, "UTF-8"))
					.build();
			
                
                
               httpresponse = httpclient.execute(httpuri);
               
               response_string = EntityUtils.toString(httpresponse.getEntity());
               System.out.println(response_string);
               return response_string;

                
                //System.out.println("ADD");
				//printresults = "<html><body><center><h2>" +team+ " "+player+ " " +goals+ " " +assists+ "</h2></center></body></html>";
				//textPane.setText(printresults);
			}catch(Exception exc){
				System.out.println(response_string);
				return response_string;
			}
	}
	
	//DELETE
	public String deleteDataServlet(String team, String player, String goals, String assists, String function){
		CloseableHttpClient httpclient;
		
		String response_string="";
		
		try{
			CloseableHttpResponse httpresponse;
			httpclient = HttpClients.createDefault();
			HttpUriRequest httpuri = null;
			
			httpuri = RequestBuilder.post()
					.setUri(new URI("http://hoare.cs.umsl.edu/servlet/j-kedge/Servlet"))
					.addParameter("team", URLEncoder.encode(team, "UTF-8"))
					.addParameter("player", URLEncoder.encode(player, "UTF-8"))
					.addParameter("goals", URLEncoder.encode(goals, "UTF-8"))
					.addParameter("assists", URLEncoder.encode(assists, "UTF-8"))
					.addParameter("function", URLEncoder.encode(function, "UTF-8"))
					.build();
			
                
                
               httpresponse = httpclient.execute(httpuri);
               
               response_string = EntityUtils.toString(httpresponse.getEntity());
               System.out.println(response_string);
               return response_string;

                
                //System.out.println("ADD");
				//printresults = "<html><body><center><h2>" +team+ " "+player+ " " +goals+ " " +assists+ "</h2></center></body></html>";
				//textPane.setText(printresults);
			}catch(Exception exc){
				System.out.println(response_string);
				return response_string;
			}
		
	}
	
	//DISPLAY
	public String displayDataServlet(String team, String player, String goals, String assists, String function){
		CloseableHttpClient httpclient;
		
		String response_string="";
		
		try{
			CloseableHttpResponse httpresponse;
			httpclient = HttpClients.createDefault();
			HttpUriRequest httpuri = null;
			
			httpuri = RequestBuilder.post()
					.setUri(new URI("http://hoare.cs.umsl.edu/servlet/j-kedge/Servlet"))
					.addParameter("team", URLEncoder.encode(team, "UTF-8"))
					.addParameter("player", URLEncoder.encode(player, "UTF-8"))
					.addParameter("goals", URLEncoder.encode(goals, "UTF-8"))
					.addParameter("assists", URLEncoder.encode(assists, "UTF-8"))
					.addParameter("function", URLEncoder.encode(function, "UTF-8"))
					.build();
			
                
                
               httpresponse = httpclient.execute(httpuri);
               
               response_string = EntityUtils.toString(httpresponse.getEntity());
               System.out.println(response_string);
               return response_string;

                
                //System.out.println("ADD");
				//printresults = "<html><body><center><h2>" +team+ " "+player+ " " +goals+ " " +assists+ "</h2></center></body></html>";
				//textPane.setText(printresults);
			}catch(Exception exc){
				System.out.println(response_string);
				return response_string;
			}
	}
	
	//UPDATE
	public String updateDataServlet(String team, String player, String goals, String assists, String function){
		CloseableHttpClient httpclient;
		
		String response_string="";
		
		try{
			CloseableHttpResponse httpresponse;
			httpclient = HttpClients.createDefault();
			HttpUriRequest httpuri = null;
			
			httpuri = RequestBuilder.post()
					.setUri(new URI("http://hoare.cs.umsl.edu/servlet/j-kedge/Servlet"))
					.addParameter("team", URLEncoder.encode(team, "UTF-8"))
					.addParameter("player", URLEncoder.encode(player, "UTF-8"))
					.addParameter("goals", URLEncoder.encode(goals, "UTF-8"))
					.addParameter("assists", URLEncoder.encode(assists, "UTF-8"))
					.addParameter("function", URLEncoder.encode(function, "UTF-8"))
					.build();
			
                
                
               httpresponse = httpclient.execute(httpuri);
               
               response_string = EntityUtils.toString(httpresponse.getEntity());
               System.out.println(response_string);
               return response_string;

                
                //System.out.println("ADD");
				//printresults = "<html><body><center><h2>" +team+ " "+player+ " " +goals+ " " +assists+ "</h2></center></body></html>";
				//textPane.setText(printresults);
			}catch(Exception exc){
				System.out.println(response_string);
				return response_string;
			}
	}
	
	
	

}
