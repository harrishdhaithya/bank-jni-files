package com.Singleton;

import com.fileaccess.FileAccess;

public class Singleton {
    private static final FileAccess fa = new FileAccess();
    public static FileAccess getFileAccess(){
        return fa;
    }     
}
