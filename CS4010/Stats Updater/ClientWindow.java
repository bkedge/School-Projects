

import java.awt.BorderLayout;
import java.awt.EventQueue;

import java.io.*;
import java.net.URI;
import java.net.URISyntaxException;
import org.apache.http.client.methods.CloseableHttpResponse;  
import org.apache.http.client.methods.HttpUriRequest; 
import org.apache.http.client.methods.RequestBuilder;
import org.apache.http.impl.client.CloseableHttpClient;  
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;
import java.util.regex.Pattern;
import java.util.regex.Matcher;
import java.net.URLEncoder;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.apache.http.ParseException;
import javax.swing.*;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JTextField;
import javax.swing.JLabel;
import javax.swing.SwingConstants;
import java.awt.Font;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import java.sql.*;
import java.awt.Color;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;


public class ClientWindow extends JFrame {

	private JPanel contentPane;
	private JTextField textFieldTeam;
	private JTextField textFieldPlayer;
	private JTextField textFieldGoals;
	private JTextField textFieldAssists;
	private final ButtonGroup buttonGroup = new ButtonGroup();

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					ClientWindow frame = new ClientWindow();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public ClientWindow() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 626, 771);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		//TITLE
		JLabel lblNewLabel = new JLabel("Stats Updater");
		lblNewLabel.setFont(new Font("Tahoma", Font.PLAIN, 18));
		lblNewLabel.setHorizontalAlignment(SwingConstants.CENTER);
		lblNewLabel.setBounds(227, 11, 130, 34);
		contentPane.add(lblNewLabel);
		
		//TEXTFIELDS
		textFieldTeam = new JTextField();
		textFieldTeam.setBounds(10, 157, 158, 34);
		contentPane.add(textFieldTeam);
		textFieldTeam.setColumns(10);
		
		textFieldPlayer = new JTextField();
		textFieldPlayer.setBounds(205, 157, 158, 34);
		contentPane.add(textFieldPlayer);
		textFieldPlayer.setColumns(10);
		
		textFieldGoals = new JTextField();
		textFieldGoals.setBounds(401, 157, 46, 34);
		contentPane.add(textFieldGoals);
		textFieldGoals.setColumns(10);
		
		textFieldAssists = new JTextField();
		textFieldAssists.setBounds(489, 157, 46, 34);
		contentPane.add(textFieldAssists);
		textFieldAssists.setColumns(10);
		
		//LABELS
		JLabel lblTeam = new JLabel("Team");
		lblTeam.setHorizontalAlignment(SwingConstants.CENTER);
		lblTeam.setBounds(70, 132, 46, 14);
		contentPane.add(lblTeam);
		
		JLabel lblPlayer = new JLabel("Player");
		lblPlayer.setHorizontalAlignment(SwingConstants.CENTER);
		lblPlayer.setBounds(264, 132, 46, 14);
		contentPane.add(lblPlayer);
		
		JLabel lblGoals = new JLabel("Goals");
		lblGoals.setHorizontalAlignment(SwingConstants.CENTER);
		lblGoals.setBounds(401, 132, 46, 14);
		contentPane.add(lblGoals);
		
		JLabel lblAssists = new JLabel("Assists");
		lblAssists.setHorizontalAlignment(SwingConstants.CENTER);
		lblAssists.setBounds(489, 132, 46, 14);
		contentPane.add(lblAssists);
		
		//BUTTONS
		JRadioButton rdbtnAdd = new JRadioButton("Add");
		buttonGroup.add(rdbtnAdd);
		rdbtnAdd.setBounds(174, 228, 68, 23);
		contentPane.add(rdbtnAdd);
		rdbtnAdd.setActionCommand("Add");
		
		JRadioButton rdbtnDelete = new JRadioButton("Delete");
		buttonGroup.add(rdbtnDelete);
		rdbtnDelete.setBounds(266, 228, 68, 23);
		contentPane.add(rdbtnDelete);
		rdbtnDelete.setActionCommand("Delete");
		
		JRadioButton rdbtnDisplay = new JRadioButton("Display");
		buttonGroup.add(rdbtnDisplay);
		rdbtnDisplay.setBounds(352, 228, 68, 23);
		contentPane.add(rdbtnDisplay);
		rdbtnDisplay.setActionCommand("Display");
		
		JRadioButton rdbtnUpdate = new JRadioButton("Update");
		buttonGroup.add(rdbtnUpdate);
		rdbtnUpdate.setBounds(439, 228, 109, 23);
		contentPane.add(rdbtnUpdate);
		rdbtnUpdate.setActionCommand("Update");
		
		JTextPane textPane = new JTextPane();
		textPane.setEditable(false);
		textPane.setBounds(10, 322, 577, 399);
		contentPane.add(textPane);
		
		
		JButton btnSubmit = new JButton("Submit");
		buttonGroup.add(btnSubmit);
		btnSubmit.setBounds(245, 276, 89, 23);
		contentPane.add(btnSubmit);
		
		JTextArea txtrAddFillAll = new JTextArea();
		txtrAddFillAll.setText("Add: Fill all fields \r\nDelete: Fill Team and Player fields. \r\nDisplay: Enter at least Player name   Update: Enter new data into all fields \r\n(Use display to find out stats, then add to this and enter new total)");
		txtrAddFillAll.setEditable(false);
		txtrAddFillAll.setBounds(10, 41, 577, 80);
		contentPane.add(txtrAddFillAll);
		
		//SUBMIT BUTTON -- ALL ACTION GOES ON HERE
		btnSubmit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				//add declarations
				
				
				String parts;
				String[] records;
				String results;
				
				String team;
				String player;
				String goals;
				String assists;
				String request1 = buttonGroup.getSelection().getActionCommand();
				String status;
				
				textPane.setContentType("text/html");//Sets Text pane to work with html tags
				
				
				
				String response = "";
				String printresults;
				
			//Cases	
			switch(request1){
					
				case("Add"):
					team = textFieldTeam.getText().trim();
					player = textFieldPlayer.getText().trim();
					goals = textFieldGoals.getText().trim();
					assists = textFieldAssists.getText().trim();
					request1 = buttonGroup.getSelection().getActionCommand();
					
					//Dont add data if a field is empty
					if(team.length()<1 || player.length()<1 || goals.length()<1 || assists.length()<1){
						textPane.setText("<html><body><center><h1>Could not Add</h1><br><h2>Make sure you are entering data into all the fields</h2></center></body></html>");
					}else{
					
					status = new ServletConnect().addDataServlet(team, player, goals, assists, "Add");
					results = "<html><body><center><h2>Added to Database: <table style=\"width:100%\"><tr><th>Team</th><th>Player</th><th>Goals</th><th>Assists</th></tr><tr>";
					records = status.split("-NeXt-");
					
					//Get strings
					for(int i=0; i<records.length; i++ ){
						System.out.println(records[i]);
						results = results + "<td><center>"+records[i]+"</center></td>";
					}
					
					results = results + "<tr></table></h2></center></body></html>";
					
					textPane.setText(results);
					
					}
					
					
					//textPane.setText("<html><body><center><h1>Added:</h1></center><br><center>"+status+"</center></body></html>");
				break;
				
				case("Delete"):
					team = textFieldTeam.getText().trim();
					player = textFieldPlayer.getText().trim();
					goals = textFieldGoals.getText().trim();
					assists = textFieldAssists.getText().trim();
					request1 = buttonGroup.getSelection().getActionCommand();
				
					//Dont delete data if team or player is empty or they enter goals or assists value
					if(team.isEmpty() || player.isEmpty()){
						textPane.setText("<html><body><center><h1>Could not Delete</h1><br><h2>Make sure you only enter in the team name and player for deleting</h2></center></body></html>");
					}
					else if(!goals.isEmpty() || !assists.isEmpty()){
						textPane.setText("<html><body><center><h1>Could not Delete</h1><br><h2>Make sure you only enter in the team name and player for deleting</h2></center></body></html>");
					}else{
				
						status = new ServletConnect().deleteDataServlet(team, player, goals, assists, "Delete");
						results = "<html><body><center><h2>Deleted Stats from Database: <table style=\"width:100%\"><tr><th>Team</th><th>Player</th></tr><tr>";
						records = status.split("-NeXt-");
				
				
						for(int i=0; i<records.length; i++ ){
							System.out.println(records[i]);
							results = results + "<td><center>"+records[i]+"</center></td>";
						}
				
						results = results + "<tr></table></h2></center></body></html>";
				
						textPane.setText(results);
				
					}
					System.out.println("DELETE");
				break;
				
				case("Display"):
					team = textFieldTeam.getText().trim();
					player = textFieldPlayer.getText().trim();
					goals = textFieldGoals.getText().trim();
					assists = textFieldAssists.getText().trim();
					request1 = buttonGroup.getSelection().getActionCommand();
				
					//Dont add data if a field is empty
					if(player.length()<1){
						textPane.setText("<html><body><center><h1>Could not Display</h1><br><h2>Make sure you are entering data into the team and player fields</h2></center></body></html>");
					}else{
				
						status = new ServletConnect().displayDataServlet(team, player, goals, assists, "Display");
						results = "<html><body><center><h2>DataBase Results: <table style=\"width:100%\"><tr><th>Team</th><th>Player</th><th>Goals</th><th>Assists</th></tr><tr>";
						records = status.split("-NeXt-");
				
				
						for(int i=0; i<records.length; i++ ){
							System.out.println(records[i]);
							results = results + "<td><center>"+records[i]+"</center></td>";
						}
				
						results = results + "<tr></table></h2></center></body></html>";
				
						textPane.setText(results);
				
					}
					System.out.println("DISPLAY");
				break;
				
				case("Update"):
					team = textFieldTeam.getText().trim();
					player = textFieldPlayer.getText().trim();
					goals = textFieldGoals.getText().trim();
					assists = textFieldAssists.getText().trim();
					request1 = buttonGroup.getSelection().getActionCommand();
			
					//Dont add data if a field is empty
					if(player.length()<1 || team.length()<1 || goals.isEmpty() || assists.isEmpty()){
						textPane.setText("<html><body><center><h1>Could not Display</h1><br><h2>Make sure you enter data into all fields</h2></center></body></html>");
					}else{
			
						status = new ServletConnect().updateDataServlet(team, player, goals, assists, "Update");
						results = "<html><body><center><h2>Updated Database, New values are: <table style=\"width:100%\"><tr><th>Team</th><th>Player</th><th>Goals</th><th>Assists</th></tr><tr>";
						records = status.split("-NeXt-");
			
			
						for(int i=0; i<records.length; i++ ){
							System.out.println(records[i]);
							results = results + "<td><center>"+records[i]+"</center></td>";
						}
			
						results = results + "<tr></table></h2></center></body></html>";
			
						textPane.setText(results);
			
					}
					System.out.println("UPDATE");
				break;
				
				default:
					textPane.setText("<html><body><center><h1>Error</h1><br><h2>Make sure you select a function</h2></center></body></html>");
					
				
				}
			
			
				
				
			}
		});
		
		
		
		
		
		
	}
}
