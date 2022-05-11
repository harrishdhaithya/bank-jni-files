import com.model.*;

import java.util.List;

import com.Singleton.Singleton;
import com.dao.*;
class dbtest{
       public static void main(String[] args){
              TransactionDao tdao = Singleton.getTransactionDao();
              List<Transaction> li = tdao.getTransactionsByAccno("7922076509");
              for(Transaction t:li){
                     System.out.println(t);
              }
       }
}