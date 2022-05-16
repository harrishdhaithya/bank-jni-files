/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_fileaccess_FileAccess */

#ifndef _Included_com_fileaccess_FileAccess
#define _Included_com_fileaccess_FileAccess
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_fileaccess_FileAccess
 * Method:    saveUsers
 * Signature: ([Lcom/model/User;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_fileaccess_FileAccess_saveUsers
  (JNIEnv *, jobject, jobjectArray);

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getUsers
 * Signature: ()[Lcom/model/User;
 */
JNIEXPORT jobjectArray JNICALL Java_com_fileaccess_FileAccess_getUsers
  (JNIEnv *, jobject);

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getUserByAccno
 * Signature: (Ljava/lang/String;)Lcom/model/User;
 */
JNIEXPORT jobject JNICALL Java_com_fileaccess_FileAccess_getUserByAccno
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getUserByEmail
 * Signature: (Ljava/lang/String;)Lcom/model/User;
 */
JNIEXPORT jobject JNICALL Java_com_fileaccess_FileAccess_getUserByEmail
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    addUser
 * Signature: (Lcom/model/User;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_fileaccess_FileAccess_addUser
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getAdmins
 * Signature: ()[Lcom/model/Admin;
 */
JNIEXPORT jobjectArray JNICALL Java_com_fileaccess_FileAccess_getAdmins
  (JNIEnv *, jobject);

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getAdminByEmail
 * Signature: (Ljava/lang/String;)Lcom/model/Admin;
 */
JNIEXPORT jobject JNICALL Java_com_fileaccess_FileAccess_getAdminByEmail
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    addAdminSecret
 * Signature: (Lcom/model/AdminSecret;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_fileaccess_FileAccess_addAdminSecret
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    addUserSecret
 * Signature: (Lcom/model/UserSecret;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_fileaccess_FileAccess_addUserSecret
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getAdminSecrets
 * Signature: ()[Lcom/model/AdminSecret;
 */
JNIEXPORT jobjectArray JNICALL Java_com_fileaccess_FileAccess_getAdminSecrets
  (JNIEnv *, jobject);

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getAdminSecret
 * Signature: (Ljava/lang/String;)Lcom/model/AdminSecret;
 */
JNIEXPORT jobject JNICALL Java_com_fileaccess_FileAccess_getAdminSecret
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getUserSecrets
 * Signature: ()[Lcom/model/UserSecret;
 */
JNIEXPORT jobjectArray JNICALL Java_com_fileaccess_FileAccess_getUserSecrets
  (JNIEnv *, jobject);

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getUserSecret
 * Signature: (Ljava/lang/String;)Lcom/model/UserSecret;
 */
JNIEXPORT jobject JNICALL Java_com_fileaccess_FileAccess_getUserSecret
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    writeTransaction
 * Signature: (Lcom/model/Transaction;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_fileaccess_FileAccess_writeTransaction
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getTransactions
 * Signature: ()[Lcom/model/Transaction;
 */
JNIEXPORT jobjectArray JNICALL Java_com_fileaccess_FileAccess_getTransactions
  (JNIEnv *, jobject);

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getTransactionsByDate
 * Signature: (Ljava/lang/String;)[Lcom/model/Transaction;
 */
JNIEXPORT jobjectArray JNICALL Java_com_fileaccess_FileAccess_getTransactionsByDate
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_fileaccess_FileAccess
 * Method:    getTransactionsByAccno
 * Signature: (Ljava/lang/String;)[Lcom/model/Transaction;
 */
JNIEXPORT jobjectArray JNICALL Java_com_fileaccess_FileAccess_getTransactionsByAccno
  (JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif
