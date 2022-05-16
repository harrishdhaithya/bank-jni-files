#include<iostream>
#include<fstream>
#include "com_fileaccess_FileAccess.h"
#include<vector>
#include<string.h>
/*
 * Class:     com_fileaccess_FileAccess
 * Method:    saveUsers
 * Signature: ([Lcom/model/User;)Z
 */
using namespace std;
JNIEXPORT jboolean JNICALL Java_com_fileaccess_FileAccess_saveUsers(JNIEnv *env, jobject jo, jobjectArray users){
    int len = env->GetArrayLength(users);
    jclass cls = env->FindClass("com/model/User");
    ofstream f("files/user.txt");
    if(!f.is_open()){
        cout<<"Not able to open the file";
        return false;
    }
    for(int i=0;i<len;i++){
        jobject o = env->GetObjectArrayElement(users,i);
        jmethodID getAccno = env->GetMethodID(cls,"getAccno","()Ljava/lang/String;");
        jstring acc_o = (jstring)(env->CallObjectMethod(o,getAccno));
        const char* accno = env->GetStringUTFChars(acc_o,NULL);
        jmethodID getFname = env->GetMethodID(cls,"getFname","()Ljava/lang/String;");
        jstring fo = (jstring)env->CallObjectMethod(o,getFname);
        const char* fname = env->GetStringUTFChars(fo,NULL);
        jmethodID getLname = env->GetMethodID(cls,"getLname","()Ljava/lang/String;");
        jstring lo = (jstring)env->CallObjectMethod(o,getLname);
        const char* lname = env->GetStringUTFChars(lo,NULL);
        jmethodID getPhone = env->GetMethodID(cls,"getPhone","()Ljava/lang/String;");
        jstring po = (jstring)env->CallObjectMethod(o,getPhone);
        const char* phone = env->GetStringUTFChars(po,NULL);
        jmethodID getEmail = env->GetMethodID(cls,"getEmail","()Ljava/lang/String;");
        jstring eo = (jstring)env->CallObjectMethod(o,getEmail);
        const char* email = env->GetStringUTFChars(eo,NULL);
        jmethodID getBalance = env->GetMethodID(cls,"getBalance","()D");
        jdouble balance = env->CallDoubleMethod(o,getBalance);
        jmethodID getPasswordHash = env->GetMethodID(cls,"getPasswordHash","()Ljava/lang/String;");
        jstring pho =(jstring)env->CallObjectMethod(o,getPasswordHash);
        const char* passwordHash = env->GetStringUTFChars(pho,NULL);
        f<<accno<<"\n";
        f<<fname<<"\n";
        f<<lname<<"\n";
        f<<phone<<"\n";
        f<<email<<"\n";
        f<<balance<<"\n";
        f<<passwordHash<<"\n";
        f<<"---------------------------------------------------------------------------------------------------------------"<<"\n";
    }
    f.close();
    return true;
}

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getUsers
 * Signature: ()[Lcom/model/User;
 */
JNIEXPORT jobjectArray JNICALL Java_com_fileaccess_FileAccess_getUsers(JNIEnv *env, jobject obj){
    jclass cls = env->FindClass("com/model/User");
    vector<jobject> v;
    ifstream f("files/user.txt",ios::in);
    if(!f.is_open()){
        cout<<"Not able to open the file...";
        return NULL;
    }
    string saccno;
    while(getline(f,saccno)){
        jstring accno = env->NewStringUTF(saccno.c_str());
        string sfname;
        getline(f,sfname);
        jstring fname = env->NewStringUTF(sfname.c_str());
        string slname;
        getline(f,slname);
        jstring lname = env->NewStringUTF(slname.c_str());
        string sphone;
        getline(f,sphone);
        jstring phone = env->NewStringUTF(sphone.c_str());
        string semail;
        getline(f,semail);
        jstring email = env->NewStringUTF(semail.c_str());
        double balance;
        f>>balance;
        string s;
        getline(f,s);
        string spasswordHash;
        getline(f,spasswordHash);
        jstring passwordHash = env->NewStringUTF(spasswordHash.c_str());
        getline(f,s);
        jmethodID cid = env->GetMethodID(cls,"<init>","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;D)V");
        jobject user = env->NewObject(cls,cid,accno,fname,lname,phone,email,passwordHash,balance);
        v.push_back(user);
    }
    jobjectArray jarr = env->NewObjectArray(v.size(),cls,NULL);
    for(int i=0;i<v.size();i++){
        jmethodID jm = env->GetMethodID(cls,"getBalance","()D");
        double val = env->CallDoubleMethod(v[i],jm);
        env->SetObjectArrayElement(jarr,i,v[i]);
    }
    f.close();
    return jarr;
}
/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getUserByAccno
 * Signature: (Ljava/lang/String;)Lcom/model/User;
 */
JNIEXPORT jobject JNICALL Java_com_fileaccess_FileAccess_getUserByAccno(JNIEnv *env, jobject obj, jstring accno1){
    jclass cls = env->FindClass("com/model/User");
    vector<jobject> v;
    ifstream f("files/user.txt",ios::in);
    if(!f.is_open()){
        cout<<"Not able to open the file...";
        return NULL;
    }
    string saccno;
    while(getline(f,saccno)){
        jstring accno = env->NewStringUTF(saccno.c_str());
        string sfname;
        getline(f,sfname);
        jstring fname = env->NewStringUTF(sfname.c_str());
        string slname;
        getline(f,slname);
        jstring lname = env->NewStringUTF(slname.c_str());
        string sphone;
        getline(f,sphone);
        jstring phone = env->NewStringUTF(sphone.c_str());
        string semail;
        getline(f,semail);
        jstring email = env->NewStringUTF(semail.c_str());
        double balance;
        f>>balance;
        string s;
        getline(f,s);
        string spasswordHash;
        getline(f,spasswordHash);
        jstring passwordHash = env->NewStringUTF(spasswordHash.c_str());
        getline(f,s);
        if(strcmp(saccno.c_str(),env->GetStringUTFChars(accno1,NULL))==0){
            jmethodID cid = env->GetMethodID(cls,"<init>","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;D)V");
            jobject user = env->NewObject(cls,cid,accno,fname,lname,phone,email,passwordHash,balance);
            return env->NewGlobalRef(user);
        }
    }
    return NULL;
}
/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getUserByEmail
 * Signature: (Ljava/lang/String;)Lcom/model/User;
 */
JNIEXPORT jobject JNICALL Java_com_fileaccess_FileAccess_getUserByEmail(JNIEnv *env, jobject obj, jstring email1){
    jclass cls = env->FindClass("com/model/User");
    vector<jobject> v;
    ifstream f("files/user.txt",ios::in);
    if(!f.is_open()){
        cout<<"Not able to open the file...";
        return NULL;
    }
    string saccno;
    while(getline(f,saccno)){
        jstring accno = env->NewStringUTF(saccno.c_str());
        string sfname;
        getline(f,sfname);
        jstring fname = env->NewStringUTF(sfname.c_str());
        string slname;
        getline(f,slname);
        jstring lname = env->NewStringUTF(slname.c_str());
        string sphone;
        getline(f,sphone);
        jstring phone = env->NewStringUTF(sphone.c_str());
        string semail;
        getline(f,semail);
        jstring email = env->NewStringUTF(semail.c_str());
        double balance;
        f>>balance;
        string s;
        getline(f,s);
        string spasswordHash;
        getline(f,spasswordHash);
        jstring passwordHash = env->NewStringUTF(spasswordHash.c_str());
        getline(f,s);
        if(strcmp(semail.c_str(),env->GetStringUTFChars(email1,NULL))==0){
            jmethodID cid = env->GetMethodID(cls,"<init>","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;D)V");
            jobject user = env->NewObject(cls,cid,accno,fname,lname,phone,email,passwordHash,balance);
            return env->NewGlobalRef(user);
        }
    }
    return NULL;
}

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    addUser
 * Signature: (Lcom/model/User;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_fileaccess_FileAccess_addUser(JNIEnv *env, jobject obj, jobject user){
    jclass cls = env->FindClass("com/model/User");
    ofstream f("files/user.txt",ios::app);
    if(!f.is_open()){
        cout<<"Not able to open the file";
        return false;
    }
    jmethodID getAccno = env->GetMethodID(cls,"getAccno","()Ljava/lang/String;");
    jstring acc_o = (jstring)(env->CallObjectMethod(user,getAccno));
    const char* accno = env->GetStringUTFChars(acc_o,NULL);
    jmethodID getFname = env->GetMethodID(cls,"getFname","()Ljava/lang/String;");
    jstring fo = (jstring)env->CallObjectMethod(user,getFname);
    const char* fname = env->GetStringUTFChars(fo,NULL);
    jmethodID getLname = env->GetMethodID(cls,"getLname","()Ljava/lang/String;");
    jstring lo = (jstring)env->CallObjectMethod(user,getLname);
    const char* lname = env->GetStringUTFChars(lo,NULL);
    jmethodID getPhone = env->GetMethodID(cls,"getPhone","()Ljava/lang/String;");
    jstring po = (jstring)env->CallObjectMethod(user,getPhone);
    const char* phone = env->GetStringUTFChars(po,NULL);
    jmethodID getEmail = env->GetMethodID(cls,"getEmail","()Ljava/lang/String;");
    jstring eo = (jstring)env->CallObjectMethod(user,getEmail);
    const char* email = env->GetStringUTFChars(eo,NULL);
    jmethodID getBalance = env->GetMethodID(cls,"getBalance","()D");
    jdouble balance = env->CallDoubleMethod(user,getBalance);
    jmethodID getPasswordHash = env->GetMethodID(cls,"getPasswordHash","()Ljava/lang/String;");
    jstring pho =(jstring)env->CallObjectMethod(user,getPasswordHash);
    const char* passwordHash = env->GetStringUTFChars(pho,NULL);
    f<<accno<<"\n";
    f<<fname<<"\n";
    f<<lname<<"\n";
    f<<phone<<"\n";
    f<<email<<"\n";
    f<<balance<<"\n";
    f<<passwordHash<<"\n";
    f<<"---------------------------------------------------------------------------------------------------------------"<<"\n";
    f.close();
    return true;
}

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getAdmins
 * Signature: ()[Lcom/model/Admin;
 */
JNIEXPORT jobjectArray JNICALL Java_com_fileaccess_FileAccess_getAdmins(JNIEnv *env, jobject obj){
    jclass cls = env->FindClass("com/model/Admin");
    vector<jobject> v;
    ifstream f("files/admin.txt");
    if(!f.is_open()){
        cout<<"Not able to open the file...";
        return NULL;
    }
    string sempid;
    while(getline(f,sempid)){
        jstring empid = env->NewStringUTF(sempid.c_str());
        string sname;
        getline(f,sname);
        jstring name = env->NewStringUTF(sname.c_str());
        string sphone;
        getline(f,sphone);
        jstring phone = env->NewStringUTF(sphone.c_str());
        string semail;
        getline(f,semail);
        jstring email = env->NewStringUTF(semail.c_str());
        string spasswordHash;
        getline(f,spasswordHash);
        string empty;
        getline(f,empty);
        jstring passwordHash = env->NewStringUTF(semail.c_str());
        jmethodID cid = env->GetMethodID(cls,"<init>","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
        jobject admin = env->NewObject(cls,cid,empid,name,phone,email,passwordHash);
        v.push_back(admin);
    }
    jobjectArray jarr = env->NewObjectArray(v.size(),cls,NULL);
    for(int i=0;i<v.size();i++){
        env->SetObjectArrayElement(jarr,i,v[i]);
    }
    f.close();
    return jarr;
}
/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getAdminByEmail
 * Signature: (Ljava/lang/String;)Lcom/model/Admin;
 */
JNIEXPORT jobject JNICALL Java_com_fileaccess_FileAccess_getAdminByEmail(JNIEnv *env, jobject obj, jstring email1){
    jclass cls = env->FindClass("com/model/Admin");
    ifstream f("files/admin.txt");
    if(!f.is_open()){
        cout<<"Not able to open the file...";
        return NULL;
    }
    string sempid;
    while(getline(f,sempid)){
        jstring empid = env->NewStringUTF(sempid.c_str());
        string sname;
        getline(f,sname);
        jstring name = env->NewStringUTF(sname.c_str());
        string sphone;
        getline(f,sphone);
        jstring phone = env->NewStringUTF(sphone.c_str());
        string semail;
        getline(f,semail);
        jstring email = env->NewStringUTF(semail.c_str());
        string spasswordHash;
        getline(f,spasswordHash);
        jstring passwordHash = env->NewStringUTF(spasswordHash.c_str());
        string empty;
        getline(f,empty);
        if(strcmp(semail.c_str(),env->GetStringUTFChars(email1,NULL))==0){
            jmethodID cid = env->GetMethodID(cls,"<init>","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
            jobject admin = env->NewObject(cls,cid,empid,name,phone,email,passwordHash);
            return admin;
        }
    }
    return NULL;
}
/*
 * Class:     com_fileaccess_FileAccess
 * Method:    addAdminSecret
 * Signature: (Lcom/model/AdminSecret;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_fileaccess_FileAccess_addAdminSecret(JNIEnv *env, jobject obj, jobject adminSecret){
    jclass cls = env->FindClass("com/model/AdminSecret");
    ofstream f("files/adminsecrets.txt",ios::app);
    if(!f.is_open()){
        cout<<"could not open file...";
        return false;
    }
    jmethodID getEmpid = env->GetMethodID(cls,"getEmpid","()Ljava/lang/String;");
    jstring sempid = (jstring)env->CallObjectMethod(adminSecret,getEmpid);
    const char* empid = env->GetStringUTFChars(sempid,NULL);
    jmethodID getSecret = env->GetMethodID(cls,"getSecret","()Ljava/lang/String;");
    jstring ssecret = (jstring)env->CallObjectMethod(adminSecret,getSecret);
    const char* secret = env->GetStringUTFChars(ssecret,NULL);
    f<<empid<<"\n";
    f<<secret<<"\n";
    f<<"---------------------------------------------------------------------------------------------------------------"<<"\n";
    f.close();
    return true;
}
/*
 * Class:     com_fileaccess_FileAccess
 * Method:    addUserSecret
 * Signature: (Lcom/model/UserSecret;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_fileaccess_FileAccess_addUserSecret(JNIEnv *env, jobject obj, jobject userSecret){
    jclass cls = env->FindClass("com/model/UserSecret");
    ofstream f("files/usersecrets.txt",ios::app);
    if(!f.is_open()){
        cout<<"could not open file...";
        return false;
    }
    jmethodID getAccno = env->GetMethodID(cls,"getAccno","()Ljava/lang/String;");
    jstring saccno = (jstring)env->CallObjectMethod(userSecret,getAccno);
    const char* accno = env->GetStringUTFChars(saccno,NULL);
    jmethodID getSecret = env->GetMethodID(cls,"getSecret","()Ljava/lang/String;");
    jstring ssecret = (jstring)env->CallObjectMethod(userSecret,getSecret);
    const char* secret = env->GetStringUTFChars(ssecret,NULL);
    f<<accno<<"\n";
    f<<secret<<"\n";
    f<<"---------------------------------------------------------------------------------------------------------------"<<"\n";
    f.close();
    return true;
}
/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getAdminSecrets
 * Signature: ()[Lcom/model/AdminSecret;
 */
JNIEXPORT jobjectArray JNICALL Java_com_fileaccess_FileAccess_getAdminSecrets(JNIEnv *env, jobject obj){
    jclass cls = env->FindClass("com/model/AdminSecret");
    vector<jobject> v;
    ifstream f("files/adminsecrets.txt");
    if(!f.is_open()){
        cout<<"Could not open file...";
        return NULL;
    }
    string sempid;
    while(getline(f,sempid)){
        jstring empid = env->NewStringUTF(sempid.c_str());
        string ssecret;
        getline(f,ssecret);
        jstring secret = env->NewStringUTF(ssecret.c_str());
        jmethodID cid = env->GetMethodID(cls,"<init>","(Ljava/lang/String;Ljava/lang/String;)V");
        jobject obj = env->NewObject(cls,cid,empid,secret);
        v.push_back(obj);
    }
    jobjectArray jarr = env->NewObjectArray(v.size(),cls,NULL);
    for(int i=0;i<v.size();i++){
        env->SetObjectArrayElement(jarr,i,v[i]);
    }
    return jarr;
}
/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getAdminSecret
 * Signature: (Ljava/lang/String;)Lcom/model/AdminSecret;
 */
JNIEXPORT jobject JNICALL Java_com_fileaccess_FileAccess_getAdminSecret(JNIEnv *env, jobject obj, jstring empid1){
    jclass cls = env->FindClass("com/model/AdminSecret");
    ifstream f("files/adminsecrets.txt");
    if(!f.is_open()){
        cout<<"Could not open file...";
        return NULL;
    }
    string sempid;
    while(getline(f,sempid)){
        jstring empid = env->NewStringUTF(sempid.c_str());
        string ssecret;
        getline(f,ssecret);
        jstring secret = env->NewStringUTF(ssecret.c_str());
        string empty;
        getline(f,empty);
        if(strcmp(sempid.c_str(),env->GetStringUTFChars(empid1,NULL))==0){
            jmethodID cid = env->GetMethodID(cls,"<init>","(Ljava/lang/String;Ljava/lang/String;)V");
            jobject obj = env->NewObject(cls,cid,empid,secret);
            return obj;
        }
    }
    return NULL;
}
/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getUserSecrets
 * Signature: ()[Lcom/model/UserSecret;
 */
JNIEXPORT jobjectArray JNICALL Java_com_fileaccess_FileAccess_getUserSecrets(JNIEnv *env, jobject o){
    jclass cls = env->FindClass("com/model/UserSecret");
    vector<jobject> v;
    ifstream f("files/usersecrets.txt");
    if(!f.is_open()){
        cout<<"Could not open file...";
        return NULL;
    }
    string saccno;
    while(getline(f,saccno)){
        jstring accno = env->NewStringUTF(saccno.c_str());
        string ssecret;
        getline(f,ssecret);
        jstring secret = env->NewStringUTF(ssecret.c_str());
        string empty;
        getline(f,empty);
        jmethodID cid = env->GetMethodID(cls,"<init>","(Ljava/lang/String;Ljava/lang/String;)V");
        jobject obj = env->NewObject(cls,cid,accno,secret);
        v.push_back(obj);
    }
    jobjectArray jarr = env->NewObjectArray(v.size(),cls,NULL);
    for(int i=0;i<v.size();i++){
        env->SetObjectArrayElement(jarr,i,v[i]);
    }
    return jarr;
}
/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getUserSecret
 * Signature: (Ljava/lang/String;)Lcom/model/UserSecret;
 */
JNIEXPORT jobject JNICALL Java_com_fileaccess_FileAccess_getUserSecret(JNIEnv *env, jobject o, jstring accno1){
    jclass cls = env->FindClass("com/model/UserSecret");
    ifstream f("files/usersecrets.txt");
    if(!f.is_open()){
        cout<<"Could not open file...";
        return NULL;
    }
    string saccno;
    while(getline(f,saccno)){
        jstring accno = env->NewStringUTF(saccno.c_str());
        string ssecret;
        getline(f,ssecret);
        jstring secret = env->NewStringUTF(ssecret.c_str());
        string empty;
        getline(f,empty);
        if(strcmp(saccno.c_str(),env->GetStringUTFChars(accno1,NULL))==0){
            jmethodID cid = env->GetMethodID(cls,"<init>","(Ljava/lang/String;Ljava/lang/String;)V");
            jobject obj = env->NewObject(cls,cid,accno,secret);
            return obj;
        }
    }
    return NULL;
}
/*
 * Class:     com_fileaccess_FileAccess
 * Method:    writeTransaction
 * Signature: (Lcom/model/Transaction;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_fileaccess_FileAccess_writeTransaction(JNIEnv *env, jobject obj, jobject transaction){
    jclass cls = env->FindClass("com/model/Transaction");
    ofstream f("files/transaction.txt",ios::app);
    if(!f.is_open()){
        cout<<"Not able to open the file..."<<endl;
        return false;
    }
    jmethodID getId = env->GetMethodID(cls,"getId","()Ljava/lang/String;");
    jstring jid = (jstring)env->CallObjectMethod(transaction,getId);
    const char* id = env->GetStringUTFChars(jid,NULL);
    jmethodID getSrc = env->GetMethodID(cls,"getSrc","()Ljava/lang/String;");
    jstring jsrc = (jstring)env->CallObjectMethod(transaction,getSrc);
    const char* src = env->GetStringUTFChars(jsrc,NULL);
    jmethodID getDest = env->GetMethodID(cls,"getDest","()Ljava/lang/String;");
    jstring jdest = (jstring)env->CallObjectMethod(transaction,getDest);
    const char* dest = env->GetStringUTFChars(jdest,NULL);
    jmethodID getAmount = env->GetMethodID(cls,"getAmount","()D");
    double amount = env->CallDoubleMethod(transaction,getAmount);
    jmethodID getDate = env->GetMethodID(cls,"getDate","()Ljava/lang/String;");
    jstring jdate = (jstring)env->CallObjectMethod(transaction,getDate);
    const char* date = env->GetStringUTFChars(jdate,NULL);
    jmethodID getTime = env->GetMethodID(cls,"getTime","()Ljava/lang/String;");
    jstring jtime = (jstring)env->CallObjectMethod(transaction,getTime);
    const char* time = env->GetStringUTFChars(jtime,NULL);
    f<<id<<endl;
    f<<src<<endl;
    f<<dest<<endl;
    f<<amount<<endl;
    f<<date<<endl;
    f<<time<<endl;
    f<<"---------------------------------------------------------------------------------------------------------------"<<endl;
    return true;
}

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getTransactions
 * Signature: ()[Lcom/model/Transaction;
 */
JNIEXPORT jobjectArray JNICALL Java_com_fileaccess_FileAccess_getTransactions(JNIEnv *env, jobject obj){
    jclass cls = env->FindClass("com/model/Transaction");
    vector<jobject> v;
    ifstream f("files/transaction.txt");
    if(!f.is_open()){
        cout<<"Could not open the file";
    }
    string cid;
    while(getline(f,cid)){
        jstring id = env->NewStringUTF(cid.c_str());
        string csrc;
        getline(f,csrc);
        jstring src = env->NewStringUTF(csrc.c_str());
        string cdest;
        getline(f,cdest);
        jstring dest = env->NewStringUTF(cdest.c_str());
        double amount;
        f>>amount;
        string empty;
        getline(f,empty);
        string cdate;
        getline(f,cdate);
        jstring date = env->NewStringUTF(cdate.c_str());
        string ctime;
        getline(f,ctime);
        jstring time = env->NewStringUTF(ctime.c_str());
        getline(f,empty);
        jmethodID constructor = env->GetMethodID(cls,"<init>","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;DLjava/lang/String;Ljava/lang/String;)V");
        jobject o = env->NewObject(cls,constructor,id,src,dest,amount,date,time);
        v.push_back(o);
    }
    jobjectArray jarr = env->NewObjectArray(v.size(),cls,NULL);
    for(int i=0;i<v.size();i++){
        env->SetObjectArrayElement(jarr,i,v[i]);
    }
    return jarr;
}

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getTransactionsByDate
 * Signature: (Ljava/lang/String;)[Lcom/model/Transaction;
 */
JNIEXPORT jobjectArray JNICALL Java_com_fileaccess_FileAccess_getTransactionsByDate(JNIEnv *env, jobject obj, jstring date1){
    jclass cls = env->FindClass("com/model/Transaction");
    vector<jobject> v;
    ifstream f("files/transaction.txt");
    if(!f.is_open()){
        cout<<"Could not open the file";
    }
    string cid;
    while(getline(f,cid)){
        jstring id = env->NewStringUTF(cid.c_str());
        string csrc;
        getline(f,csrc);
        jstring src = env->NewStringUTF(csrc.c_str());
        string cdest;
        getline(f,cdest);
        jstring dest = env->NewStringUTF(cdest.c_str());
        double amount;
        f>>amount;
        string empty;
        getline(f,empty);
        string cdate;
        getline(f,cdate);
        jstring date = env->NewStringUTF(cdate.c_str());
        string ctime;
        getline(f,ctime);
        jstring time = env->NewStringUTF(ctime.c_str());
        getline(f,empty);
        if(strcmp(cdate.c_str(),env->GetStringUTFChars(date1,NULL))==0){
            jmethodID constructor = env->GetMethodID(cls,"<init>","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;DLjava/lang/String;Ljava/lang/String;)V");
            jobject o = env->NewObject(cls,constructor,id,src,dest,amount,date,time);
            v.push_back(o);
        }
    }
    jobjectArray jarr = env->NewObjectArray(v.size(),cls,NULL);
    for(int i=0;i<v.size();i++){
        env->SetObjectArrayElement(jarr,i,v[i]);
    }
    return jarr;
}

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getTransactionsByAccno
 * Signature: (Ljava/lang/String;)[Lcom/model/Transaction;
 */
JNIEXPORT jobjectArray JNICALL Java_com_fileaccess_FileAccess_getTransactionsByAccno(JNIEnv *env, jobject obj, jstring accno){
    jclass cls = env->FindClass("com/model/Transaction");
    vector<jobject> v;
    ifstream f("files/transaction.txt");
    if(!f.is_open()){
        cout<<"Could not open the file";
    }
    string cid;
    while(getline(f,cid)){
        jstring id = env->NewStringUTF(cid.c_str());
        string csrc;
        getline(f,csrc);
        jstring src = env->NewStringUTF(csrc.c_str());
        string cdest;
        getline(f,cdest);
        jstring dest = env->NewStringUTF(cdest.c_str());
        double amount;
        f>>amount;
        string empty;
        getline(f,empty);
        string cdate;
        getline(f,cdate);
        jstring date = env->NewStringUTF(cdate.c_str());
        string ctime;
        getline(f,ctime);
        jstring time = env->NewStringUTF(ctime.c_str());
        getline(f,empty);
        if(strcmp(csrc.c_str(),env->GetStringUTFChars(accno,NULL))==0){
            jmethodID constructor = env->GetMethodID(cls,"<init>","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;DLjava/lang/String;Ljava/lang/String;)V");
            jobject o = env->NewObject(cls,constructor,id,src,dest,amount,date,time);
            v.push_back(o);
        }
    }
    jobjectArray jarr = env->NewObjectArray(v.size(),cls,NULL);
    for(int i=0;i<v.size();i++){
        env->SetObjectArrayElement(jarr,i,v[i]);
    }
    return jarr;
}

