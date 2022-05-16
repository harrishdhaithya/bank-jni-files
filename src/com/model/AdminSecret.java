package com.model;

public class AdminSecret {
    private String empid;
    private String secret;
    public AdminSecret(String empid,String secret){
        this.empid=empid;
        this.secret=secret;
    }
    public void setEmpid(String empid){
        this.empid=empid;
    }
    public void setSecret(String secret){
        this.secret=secret;
    }
    public String getEmpid(){
        return empid;
    }
    public String getSecret(){
        return secret;
    }
}
