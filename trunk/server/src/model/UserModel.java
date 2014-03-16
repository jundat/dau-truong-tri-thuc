/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import db.MySqlConnection_Rd;
import db.MySqlConnection_W;
import db.Utils.*;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import libCore.Util;
import org.json.simple.JSONValue;
import share.ShareConstants;

import java.lang.Comparable;

/**
 *
 * @author Mrkupi
 */
public class UserModel implements BaseModel {
    
    public String uid;
    public String name;
    public String avatar;
    public SingleResultModel singleResult;
    public MultiResultModel multiResult;
    public int jewelry;
    
    public UserModel() {
        singleResult    =   new SingleResultModel();
        multiResult     =   new MultiResultModel();
    }

    @Override
    public void getData() {
        
        DataTable dt    =   MySqlConnection_Rd.getInstance().selectCmdWhere( ShareConstants.TABLE_USER, "userid = " + Util.toStringDB(uid), "name", "avatar", "singleresultid", "multiresultid", "jewelry" );
        if( dt != null && dt.size() > 0 )
        {
            DataRow row         =   dt.get( 0 );
            name                =   row.get( "name" );
            avatar              =   row.get( "avatar" );
            jewelry             =   Integer.parseInt(row.get( "jewelry" ).toString());
            
            singleResult.result.setId( row.get("singleresultid"));
            multiResult.result.setId( row.get("multiresultid"));
            
            singleResult.getData();
            multiResult.getData();
        }
    }
    
    @Override
    public String toData() {
        Map<String, Object> data    =   new HashMap<String, Object>();
        
        data.put( ShareConstants.USER_ID, uid );
        data.put( ShareConstants.USER_NAME, name );
        data.put( ShareConstants.USER_AVATAR, avatar );
        data.put( ShareConstants.USER_SINGLE, singleResult.toData() );
        data.put( ShareConstants.USER_MULTI, multiResult.toData() );
        data.put( ShareConstants.USER_JEWELRY, jewelry );
        
        String dataStr  =   Util.obj2String( data );
        
        return dataStr;
    }

    @Override
    public void parseData(Object data) {
        
        Map<String, Object> mData   =   (Map<String, Object>) data;
        uid     =   String.valueOf( mData.get( ShareConstants.USER_ID ) );
        name    =   String.valueOf( mData.get( ShareConstants.USER_NAME ) );
        avatar  =   String.valueOf( mData.get( ShareConstants.USER_AVATAR ) );
        jewelry =   Integer.parseInt(String.valueOf( mData.get( ShareConstants.USER_JEWELRY ) ));
        
        singleResult.parseData( mData.get( ShareConstants.USER_SINGLE) );
        multiResult.parseData( mData.get( ShareConstants.USER_MULTI) );
    }
    
    public Boolean acceptNewUser( HttpServletRequest req, HttpServletResponse resp ) {
        
        String data     =   req.getParameter ( ShareConstants.DATA );
        Map<String, String> mData   =   (HashMap<String, String>) JSONValue.parse(data);
        uid     =   mData.get( ShareConstants.FID ).toString();
        name    =   mData.get( ShareConstants.FNAME ).toString();
        //avatar  =   mData.get("fbAvatar").toString();
        avatar  =   "";
        jewelry =   Integer.parseInt( libCore.Config.getParam( "MutilConfig", "DefaultJewelry") );
        
        singleResult.defaultResult( uid );
        multiResult.defaultResult( uid );
        
        int result  =   MySqlConnection_W.getInstance().insertTable( ShareConstants.TABLE_USER, Util.toStringDB(uid),  Util.toStringDB(name), 
                 Util.toStringDB(avatar),  Util.toStringDB(singleResult.result.getId()),  Util.toStringDB(multiResult.result.getId()), String.valueOf(jewelry) );
        if( result <= 0 )
            return false;
        
        if( singleResult.setDB() || multiResult.setDB() )
            return false;
        
        return true;
    }
 
    public Boolean getUserData( HttpServletRequest req, HttpServletResponse resp ) {
        
        String data     =   req.getParameter ( ShareConstants.DATA );
        Map<String, String> mData   =   (HashMap<String, String>) JSONValue.parse(data);
        uid     =   mData.get("fbId").toString();
        if( uid.equals("") )
            return false;
        
        // Query data from mysql
        getData();
        
        Map<String, Object> returnData  =   new HashMap<String, Object>();
        returnData.put( ShareConstants.USER_ID, uid );
        returnData.put( ShareConstants.USER_NAME, name );
        returnData.put( ShareConstants.USER_AVATAR, avatar );
        
        String dataStr  =   libCore.Util.obj2String( returnData );
        
        // Response
        PrintWriter pw;
        try {
            pw = resp.getWriter();
            pw.println(dataStr);
            pw.flush();
            pw.close();
        } catch (IOException ex) {
            Logger.getLogger(UserModel.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        return true;
    }
}