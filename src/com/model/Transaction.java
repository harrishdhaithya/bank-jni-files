package com.model;

import java.time.LocalDate;
import java.time.LocalTime;
import java.util.Random;

public class Transaction {
    private String id;
    private String src;
    private String dest;
    private double amount;
    private String date;
    private String time;
    private static String createID(){
		String accno = "";
		Random rand = new Random();
		for(int i=0;i<10;i++){
			accno+=rand.nextInt(10);
		}
		return accno;
	}
    public Transaction(String src,String dest,double amount){
        this.id=createID();
        this.src=src;
        this.dest=dest;
        this.amount=amount;
        this.date = LocalDate.now().toString();
        this.time = LocalTime.now().toString();
    }
    public Transaction(String id,String src,String dest,double amount,String date,String time){
        this.id=id;
        this.src=src;
        this.dest=dest;
        this.amount=amount;
        this.date=date;
        this.time=time;
    }
    public void setId(String id){
        this.id=id;
    }
    public void setSrc(String u){
        this.src=u;
    }
    public void setDest(String u){
        this.src=u;
    }
    public void setAmount(double amount){
        this.amount=amount;
    }
    public void setDate(String date){
        this.date=date;
    }
    public void setTime(String time){
        this.time=time;
    }
    public String getId(){
        return id;
    }
    public String getSrc(){
        return src;
    }
    public String getDest(){
        return dest;
    }
    public double getAmount(){
        return amount;
    }
    public String getDate(){
        return date;
    }
    public String getTime(){
        return time;
    }
    @Override
    public String toString(){
        return "Source Account: " + src+"\n"+
                "Destination Account: " + dest+"\n"+
                "Transaction Amount: "+ amount +"\n"+
                "Date: "+date+"\n"+
                "Time: "+time;
    }
}
