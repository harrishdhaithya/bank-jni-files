package com.fileaccess;

import com.model.Admin;
import com.model.User;
import com.model.UserSecret;
import com.model.AdminSecret;
import com.model.Transaction;

public class FileAccess{
    static{
        System.loadLibrary("native");
    }
    public native boolean saveUsers(User[] u);
    public native User[] getUsers();
    public native User getUserByAccno(String accno);
    public native User getUserByEmail(String email);
    public native boolean addUser(User u);
    public native Admin[] getAdmins();
    public native Admin getAdminByEmail(String email);
    public native boolean addAdminSecret(AdminSecret as);
    public native boolean addUserSecret(UserSecret us);
    public native AdminSecret[] getAdminSecrets();
    public native AdminSecret getAdminSecret(String empid);
    public native UserSecret[] getUserSecrets();
    public native UserSecret getUserSecret(String accno);
    public native boolean writeTransaction(Transaction t);
    public native Transaction[] getTransactions();
    public native Transaction[] getTransactionsByDate(String date);
    public native Transaction[] getTransactionsByAccno(String accno);
}