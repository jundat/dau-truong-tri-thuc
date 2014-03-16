/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import db.MySqlConnection_Rd;
import db.MySqlConnection_W;
import db.Utils.DataRow;
import db.Utils.DataTable;
import entities.SingleResult;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import libCore.Util;
import org.json.simple.JSONValue;
import share.KeysDefinition;
import share.ShareConstants;

/**
 *
 * @author Mrkupi
 */
public class SingleResultModel implements BaseModel{

    public SingleResult result;
    
    public SingleResultModel() {
        result  =   new SingleResult();
    }
    
    public void defaultResult( String uid ) {
        result.setId( uid + KeysDefinition.randomKeySTR() );
        result.setWins( 0 );
        result.setLoses( 0 );
        result.setScore( 0 );
    }
    
    public Boolean setDB() {
        return MySqlConnection_W.getInstance().insertTable( ShareConstants.TABLE_SINGLERESULT,  Util.toStringDB(result.getId()), String.valueOf(result.getWins()),
                String.valueOf(result.getLoses()), String.valueOf(result.getScore() )) <= 0;
    }
    
    @Override
    public void getData() {
        DataTable dt    =   MySqlConnection_Rd.getInstance().selectCmdWhere( ShareConstants.TABLE_SINGLERESULT, 
                ShareConstants.SINGLERESULT_ID + " = " + Util.toStringDB(result.getId()), ShareConstants.SINGLERESULT_ID, ShareConstants.RESULT_WIN, ShareConstants.RESULT_LOSE, ShareConstants.RESULT_SCORE );
        if( dt != null && dt.size() > 0 )
        {
            DataRow row         =   dt.get( 0 );
            result.setId( row.get(ShareConstants.SINGLERESULT_ID) );
            result.setWins( Integer.parseInt(row.get(ShareConstants.RESULT_WIN) ));
            result.setLoses( Integer.parseInt(row.get(ShareConstants.RESULT_LOSE) ));
            result.setScore( Integer.parseInt(row.get(ShareConstants.RESULT_SCORE) ));
        }
    }
    
    @Override
    public void parseData(Object data) {
        Map<String, Object> mData   =   (Map<String, Object>) data;
        
        result.setId( String.valueOf( mData.get( ShareConstants.SINGLERESULT_ID ) ) );
        result.setWins(Integer.parseInt(String.valueOf( mData.get( ShareConstants.RESULT_WIN ) )));
        result.setLoses(Integer.parseInt(String.valueOf( mData.get( ShareConstants.RESULT_LOSE ) )));
        result.setScore(Integer.parseInt(String.valueOf( mData.get( ShareConstants.RESULT_SCORE ) )));
    }

    @Override
    public String toData() {
        Map<String, Object> data    =   new HashMap<String, Object>();
        
        data.put( ShareConstants.SINGLERESULT_ID, result.getId() );
        data.put( ShareConstants.RESULT_WIN, result.getWins() );
        data.put( ShareConstants.RESULT_LOSE, result.getLoses() );
        data.put( ShareConstants.RESULT_SCORE, result.getScore() );
        
        String dataStr  =   Util.obj2String( data );
        
        return dataStr;
    }
    
    public void getScore( HttpServletRequest req, HttpServletResponse resp ) throws IOException {
        
        String data     =   req.getParameter ( ShareConstants.DATA );
        Map<String, String> mData   =   (HashMap<String, String>) JSONValue.parse(data);
        String uid     =   mData.get( ShareConstants.FID ).toString();

        // Get correctly user
        UserModel um    =   new UserModel();
        um.uid          =   uid;
        um.getData();

        // Retrieve single result row of user
        this.result.setId( um.singleResult.result.getId() );
        this.result.setWins( um.singleResult.result.getWins() );
        this.result.setLoses( um.singleResult.result.getLoses() );
        this.result.setScore( um.singleResult.result.getScore() );
        
        try (PrintWriter pw = resp.getWriter()) 
        {
            String dataStr      =   this.toData();
            pw.println( dataStr );
            pw.flush();
        }
    }
    
    public Boolean setScore( HttpServletRequest req, HttpServletResponse resp ) {
        Boolean bResult  =   false;
        try {
            String data     =   req.getParameter ( ShareConstants.DATA );
            Map<String, String> mData   =   (HashMap<String, String>) JSONValue.parse(data);
            String uid     =   mData.get( ShareConstants.FID ).toString();

            // Get correctly user
            UserModel um    =   new UserModel();
            um.uid          =   uid;
            um.getData();

            // Retrieve single result row of user
            this.result.setId( um.singleResult.result.getId() );
            this.result.setWins( um.singleResult.result.getWins() );
            this.result.setLoses( um.singleResult.result.getLoses() );
            this.result.setScore( um.singleResult.result.getScore() );
            
            int clientScore =   Integer.parseInt(mData.get( ShareConstants.RESULT_SCORE ).toString());
            if( this.result.getScore() < clientScore ) {
                // Update score database
                this.result.setScore( clientScore );
                
                String[] colums =   { ShareConstants.RESULT_SCORE };
                String[] types  =   { String.valueOf(clientScore) };
                if(MySqlConnection_W.getInstance().updateTable( ShareConstants.TABLE_SINGLERESULT, colums, types, ShareConstants.SINGLERESULT_ID + " = " + libCore.Util.toStringDB(result.getId())) > 0)
                    bResult     =   true;
            }
        }
        catch( Exception e ) {
            System.out.println( "Set score on user, error was happen" );
        }
        
        return bResult;
    }
}
