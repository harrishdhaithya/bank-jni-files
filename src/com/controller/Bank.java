package com.controller;

import java.util.List;
import com.Singleton.Singleton;
import com.dao.AdminDao;
import com.dao.TransactionDao;
import com.dao.UserDao;
import com.dao.UserSecretDao;
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
		UserDao u = Singleton.getUserDao();
		UserSecretDao usdao = Singleton.getUserSecretDao();
		String secret = TwoFAAuth.generateSecretKey();
		if(Otp.evalOtp(email)) {
			user = new User(fname,lname,phone,email,password,balance);
			us = new UserSecret(user.getAccno(),secret);
			boolean success = u.saveUser(user);
			if(!success){
				return false;
			}
			System.out.println("Your Secret for Google Authenticator is "+secret);
			return success&&usdao.saveSecret(us);
		}
		return false;
	}
	public static User getAccDetails(String accno) {
		if(loggedInUser==null&&loggedInAdmin==null) {
			return null;
		}
		UserDao u = Singleton.getUserDao();
		User user = u.getUserByAccno(accno);
		return user;
	}
	public static List<User> getAllUsers(){
		UserDao u = Singleton.getUserDao();
		List<User> users = u.getAllUsers();
		return users;
	}
	public static List<Transaction> getAllTransaction(){
		if(loggedInAdmin==null){
			System.out.println("Illegal Access");
			return null;
		}
		TransactionDao td = Singleton.getTransactionDao();
		List<Transaction> t = td.getAllTransaction();
		return t;
	}
	public static boolean deposit(String accno,double amount) {
		if(loggedInUser==null) {
			return false;
		}
		UserDao u = Singleton.getUserDao();
		User user = u.getUserByAccno(accno);
		user.setBalance(user.getBalance()+amount);
		return u.saveUser(user);
	}
	public static boolean withdraw(String accno,double amount) {
		if(loggedInUser==null) {
			return false;
		}
		UserDao u = Singleton.getUserDao();
		User user = u.getUserByAccno(accno);
		if(user.getBalance()<amount){
			return false;
		}
		user.setBalance(user.getBalance()-amount);
		return u.saveUser(user);
	}
	public static boolean userlogin(String email,String password) {
		UserDao u = Singleton.getUserDao();
		User user = u.getUserByEmail(email);
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
		AdminDao a = Singleton.getAdminDao();
		Admin admin = a.getAdminByEmail(email);
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
		UserDao u = Singleton.getUserDao();
		User src = u.getUserByAccno(loggedInUser.getAccno());
		User dest = u.getUserByAccno(to);
		if(src==null||dest==null){
			return false;
		}
		TransactionDao tdao = Singleton.getTransactionDao();
		try{
			return tdao.performTransaction(src, dest, amount);
		}catch(Exception e){
			System.out.println(e);
			return false;
		}
	}
	public static void showBalance(String accno) {
		if(loggedInUser==null) {
			System.out.println("Illegal Access...");
			return;
		}
		UserDao u = Singleton.getUserDao();
		User user = u.getUserByAccno(accno);
		System.out.println(user);
	}
	public static void userLogout() {
		loggedInUser=null;
	}
	public static void adminLogout() {
		loggedInAdmin=null;
	}
}
