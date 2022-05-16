package com.controller;
import com.Singleton.Singleton;
import com.fileaccess.FileAccess;
import com.model.Admin;
import com.model.User;
import com.model.UserSecret;
import com.model.Transaction;

public class Bank {
	public static User loggedInUser=null;
	public static Admin loggedInAdmin=null;
	public static boolean signup(String fname, String lname, String phone, String email, String password,double balance) {
		if(phone.length()!=10) {
			return false;
		}
		User user = null;
		UserSecret us = null;
		FileAccess fa = Singleton.getFileAccess();
		String secret = TwoFAAuth.generateSecretKey();
		if(Otp.evalOtp(email)) {
			user = new User(fname,lname,phone,email,password,balance);
			us = new UserSecret(user.getAccno(),secret);
			boolean success = fa.addUser(user);
			if(!success){
				return false;
			}
			System.out.println("Your Secret for Google Authenticator is "+secret);
			return success&&fa.addUserSecret(us);
		}
		return false;
	}
	public static User getAccDetails(String accno) {
		if(loggedInUser==null&&loggedInAdmin==null) {
			return null;
		}
		FileAccess fa = Singleton.getFileAccess();
		User user = fa.getUserByAccno(accno);
		if(user==null){
			System.out.println("No Users found...");
		}
		return user;
	}
	public static User[] getAllUsers(){
		FileAccess fa = Singleton.getFileAccess();
		User[] users = fa.getUsers();
		return users;
	}
	public static Transaction[] getAllTransaction(){
		if(loggedInAdmin==null){
			System.out.println("Illegal Access");
			return null;
		}
		FileAccess fa = Singleton.getFileAccess();
		Transaction[] transactions = fa.getTransactions();
		return transactions;
	}
	public static User getUserByAccno(User[] users,String accno){
		for(User user:users){
			if(user.getAccno().equals(accno)){
				return user;
			}
		}
		return null;
	}
	public static boolean deposit(String accno,double amount) {
		if(loggedInUser==null) {
			System.out.println("Illegal Access...");
			return false;
		}
		FileAccess fa = Singleton.getFileAccess();
		User[] users = fa.getUsers();
		User user = getUserByAccno(users,accno);
		user.setBalance(user.getBalance()+amount);
		return fa.saveUsers(users);
	}
	public static boolean withdraw(String accno,double amount) {
		if(loggedInUser==null) {
			return false;
		}
		FileAccess fa = Singleton.getFileAccess();
		User[] users = fa.getUsers();
		User user = getUserByAccno(users,accno);
		if(user.getBalance()<amount){
			return false;
		}
		user.setBalance(user.getBalance()-amount);
		return fa.saveUsers(users);
	}
	public static boolean userlogin(String email,String password) {
		FileAccess fa = Singleton.getFileAccess();
		User user = fa.getUserByEmail(email);
		if(user==null){
			return false;
		}
		if(user.evalPassword(password)){
			if(TwoFAAuth.twoFA(user)){
				loggedInUser=user;
				return true;
			}
		}
		return false;
	}
	public static boolean adminLogin(String email,String password) {
		FileAccess fa = Singleton.getFileAccess();
		Admin admin = fa.getAdminByEmail(email);
		if(admin==null){
			return false;
		}
		if(admin.evalPassword(password)){
			if(TwoFAAuth.twoFA(admin)){
				loggedInAdmin=admin;
				return true;
			}
		}
		return false;
	}
	public static boolean makeTransaction(String to,double amount) {
		if(loggedInUser==null){
			return false;
		}
		FileAccess fa = Singleton.getFileAccess();
		User[] users = fa.getUsers();
		User src = getUserByAccno(users,loggedInUser.getAccno());
		User dest = getUserByAccno(users,to);
		if(src.getAccno().equals(to)){
			System.out.println("Transaction cannot be done within same account...");
			return false;
		}
		if(src==null||dest==null){
			return false;
		}
		if(src.getBalance()<amount){
			System.out.println("No Sufficient Balance...");
			return false;
		}
		src.setBalance(src.getBalance()+amount);
		dest.setBalance(dest.getBalance()+amount);
		Transaction t = new Transaction(src.getAccno(), to, amount);
		return fa.saveUsers(users)&&fa.writeTransaction(t);
	}
	public static Transaction[] getTransactionsByDate(String date){
		if(loggedInAdmin==null){
			System.out.println("Illegal Access...");
			return null;
		}
		FileAccess fa = Singleton.getFileAccess();
		Transaction[] transactions = fa.getTransactionsByDate(date);
		return transactions;
	}
	public static Transaction[] getTransactionByAccno(String accno){
		if(loggedInUser==null&&loggedInAdmin==null){
			System.out.println("Illegal Access...");
			return null;
		}
		FileAccess fa = Singleton.getFileAccess();
		Transaction[] transactions = fa.getTransactionsByAccno(accno);
		return transactions;
	}
	public static void showBalance(String accno) {
		if(loggedInUser==null) {
			System.out.println("Illegal Access...");
			return;
		}
		FileAccess fa = Singleton.getFileAccess();
		User u = fa.getUserByAccno(accno);
		System.out.println(u);
	}
	public static void userLogout() {
		loggedInUser=null;
	}
	public static void adminLogout() {
		loggedInAdmin=null;
	}
}
