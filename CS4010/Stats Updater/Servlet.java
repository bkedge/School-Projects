

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.*;
import java.sql.*;
import java.util.regex.Pattern;
import java.util.regex.Matcher;
import java.net.URLDecoder;
import java.net.URLEncoder;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Servlet implementation class Servlet
 */
//@WebServlet("/Servlet")
public class Servlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
	
	//SQL
	String JDBC_DRIVER = "com.mysql.jdbc.Driver";
	String DB_URL = "jdbc:mysql://localhost/cs4010";
	String USR = "cs4010";
	String PASS = "cs4010";
	
	String requestTeam = "";
	String requestPlayer = "";
	String requestGoals = "";
	String requestAssists = "";
	String rfunction = "";
	
	String splitter = "-NeXt-";
	
       
    /**
     * @see HttpServlet#HttpServlet()
     */
	//This needs to stay for some reason? **DO NOT REMOVE**
    public Servlet() {
        //super();
        // TODO Auto-generated constructor stub
    }
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    	requestTeam = URLDecoder.decode(request.getParameter("team"), "UTF-8");
		requestPlayer = URLDecoder.decode(request.getParameter("player"), "UTF-8");
		requestGoals = URLDecoder.decode(request.getParameter("goals"), "UTF-8");
		requestAssists = URLDecoder.decode(request.getParameter("assists"), "UTF-8");
		rfunction = URLDecoder.decode(request.getParameter("function"), "UTF-8");
		
		response.setContentType("text/html;charset=UTF-8");
		PrintWriter out = response.getWriter();
		
		
		
		
		switch(rfunction){
		
		case("Add"):
			out.println(addData(requestTeam, requestPlayer, requestGoals, requestAssists));
			//out.println("Connected");
			out.println(requestTeam+splitter+requestPlayer+splitter+requestGoals+splitter+requestAssists);
		break;
		
		case("Delete"):
			out.println(deleteData(requestTeam, requestPlayer));
			out.println(requestTeam+splitter+requestPlayer);
			
		break;
		
		case("Display"):
			out.println(displayData(requestTeam, requestPlayer, requestGoals, requestAssists));
		break;
		
		case("Update"):
			out.println(updateData(requestTeam, requestPlayer, requestGoals, requestAssists));
		break;
			
		}
		
		//doGet(request, response);
	}
    
    //ADD TO DATABASE
    public String addData(String team, String player, String goals, String assists){
    
    	
    	   
    	   Connection conn = null;
    	   Statement stmt = null;
    	   try{
    		   
    	      //STEP 2: Register JDBC driver
    	      Class.forName(JDBC_DRIVER);

    	      //STEP 3: Open a connection
    	      System.out.println("Connecting to a selected database...");
    	      conn = DriverManager.getConnection(DB_URL, USR, PASS);
    	      System.out.println("Connected database successfully...");
    	      
    	      //STEP 4: Execute a query
    	      stmt = conn.createStatement();
    	      String this_query = "INSERT INTO kedge (team, player, goals, assists) VALUES (\""+team+"\",\""+player+"\",\""+goals+"\",\""+assists+"\");";
    	      stmt.executeUpdate(this_query);
    	      

    	   }catch(SQLException se){
    	      //Handle errors for JDBC
    	      se.printStackTrace();
    	   }catch(Exception e){
    	      //Handle errors for Class.forName
    	      e.printStackTrace();
    	   }finally{
    	      //finally block used to close resources
    	      try{
    	         if(stmt!=null)
    	            conn.close();
    	      }catch(SQLException se){
    	      }// do nothing
    	      try{
    	         if(conn!=null)
    	            conn.close();
    	      }catch(SQLException se){
    	         se.printStackTrace();
    	      }//end finally try
    	   }//end try
    	   //System.out.println("Goodbye!");
    	   return "";
    	
    }
    
    public String deleteData(String team, String player){
    	Connection conn = null;
 	   	Statement stmt = null;
 	   	try{
 		   
 	   		//STEP 2: Register JDBC driver
 	   		Class.forName(JDBC_DRIVER);

 	   		//STEP 3: Open a connection
 	   		System.out.println("Connecting to a selected database...");
 	   		conn = DriverManager.getConnection(DB_URL, USR, PASS);
 	   		System.out.println("Connected database successfully...");
 	      
 	   		//STEP 4: Execute a query
 	   		stmt = conn.createStatement();
	 	     String this_query = "DELETE FROM kedge WHERE team='"+team+"' AND player='"+player+"';";
	 	      stmt.executeUpdate(this_query);
	 	      
	
	 	   }catch(SQLException se){
	 	      //Handle errors for JDBC
	 	      se.printStackTrace();
	 	   }catch(Exception e){
	 	      //Handle errors for Class.forName
	 	      e.printStackTrace();
	 	   }finally{
	 	      //finally block used to close resources
	 	      try{
	 	         if(stmt!=null)
	 	            conn.close();
	 	      }catch(SQLException se){
	 	      }// do nothing
	 	      try{
	 	         if(conn!=null)
	 	            conn.close();
	 	      }catch(SQLException se){
	 	         se.printStackTrace();
	 	      }//end finally try
	 	   }//end try
	 	   //System.out.println("Goodbye!");
	 	   return "";
    }
    
    public String displayData(String team, String player, String goals, String assists){
        
    	
 	   StringBuilder displayresult = new StringBuilder();
 	   Connection conn = null;
 	   Statement stmt = null;
 	   
 	   String finalstring = null;
 	   try{
 		   
 	      //STEP 2: Register JDBC driver
 	      Class.forName(JDBC_DRIVER);

 	      //STEP 3: Open a connection
 	      System.out.println("Connecting to a selected database...");
 	      conn = DriverManager.getConnection(DB_URL, USR, PASS);
 	      System.out.println("Connected database successfully...");
 	      
 	      //STEP 4: Execute a query
 	      stmt = conn.createStatement();
 	      String this_query = "SELECT * FROM kedge WHERE player='"+player+"';";
 	      ResultSet rs = stmt.executeQuery(this_query);
 	      //stmt.executeUpdate(this_query);
 	      while(rs.next()){
 	    	 String sqlresult = rs.getString("team")+splitter+rs.getString("player")+splitter+rs.getString("goals")+splitter+rs.getString("assists");
 	    	 displayresult.append(sqlresult);
 	    	 
 	    	
 	      }
 	      
 	      finalstring = displayresult.toString();
 	      

 	   }catch(SQLException se){
 	      //Handle errors for JDBC
 	      se.printStackTrace();
 	   }catch(Exception e){
 	      //Handle errors for Class.forName
 	      e.printStackTrace();
 	   }finally{
 	      //finally block used to close resources
 	      try{
 	         if(stmt!=null)
 	            conn.close();
 	      }catch(SQLException se){
 	      }// do nothing
 	      try{
 	         if(conn!=null)
 	            conn.close();
 	      }catch(SQLException se){
 	         se.printStackTrace();
 	      }//end finally try
 	   }//end try
 	   //System.out.println("Goodbye!");
 	   return finalstring;
 	
 }
    
    public String updateData(String team, String player, String goals, String assists){
        
    	
  	   StringBuilder displayresult = new StringBuilder();
  	   Connection conn = null;
  	   Statement stmt = null;
  	   
  	   String finalstring = null;
  	   try{
  		   
  	      //STEP 2: Register JDBC driver
  	      Class.forName(JDBC_DRIVER);

  	      //STEP 3: Open a connection
  	      System.out.println("Connecting to a selected database...");
  	      conn = DriverManager.getConnection(DB_URL, USR, PASS);
  	      System.out.println("Connected database successfully...");
  	      
  	      //STEP 4: Execute a query
  	      stmt = conn.createStatement();
  	      
  	      String this_query = "UPDATE kedge SET team='"+team+"', goals='"+goals+"', assists='"+assists+"' WHERE player='"+player+"';";
  	      stmt.executeUpdate(this_query);
  	      
  	      //Store the data we just updated
  	      this_query = "SELECT * FROM kedge WHERE player='"+player+"';";
  	      ResultSet rs = stmt.executeQuery(this_query);
  	      //stmt.executeUpdate(this_query);
  	      while(rs.next()){
  	    	 String sqlresult = rs.getString("team")+splitter+rs.getString("player")+splitter+rs.getString("goals")+splitter+rs.getString("assists");
  	    	 displayresult.append(sqlresult);
  	    	 
  	    	
  	      }
  	      
  	      finalstring = displayresult.toString();
  	      

  	   }catch(SQLException se){
  	      //Handle errors for JDBC
  	      se.printStackTrace();
  	   }catch(Exception e){
  	      //Handle errors for Class.forName
  	      e.printStackTrace();
  	   }finally{
  	      //finally block used to close resources
  	      try{
  	         if(stmt!=null)
  	            conn.close();
  	      }catch(SQLException se){
  	      }// do nothing
  	      try{
  	         if(conn!=null)
  	            conn.close();
  	      }catch(SQLException se){
  	         se.printStackTrace();
  	      }//end finally try
  	   }//end try
  	   //System.out.println("Goodbye!");
  	   return finalstring;
  	
  }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		//response.getWriter().append("Served at: ").append(request.getContextPath());
		//response.setContentType("text/html");
        //PrintWriter printWriter  = response.getWriter();
        //printWriter.println("<h1>Potato</h1>");
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	

}
