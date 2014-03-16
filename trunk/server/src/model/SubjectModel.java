/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import db.MySqlConnection_Rd;
import db.Utils.DataRow;
import db.Utils.DataTable;
import entities.Subject;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import libCore.Util;
import org.json.simple.JSONValue;
import share.ShareConstants;

/**
 *
 * @author Mrkupi
 */
public class SubjectModel implements BaseModel{

    Subject subject;
    
    public SubjectModel() {
        subject      =   new Subject();
    }
    
    @Override
    public void getData() {
        DataTable dt    =   MySqlConnection_Rd.getInstance().selectCmdWhere( ShareConstants.TABLE_SUBJECT, ShareConstants.SUBJECT_ID+" = " + Util.toStringDB(subject.getId()), 
                ShareConstants.SUBJECT_ID, ShareConstants.SUBJECT_NAME, ShareConstants.SUBJECT_ACTIVE, ShareConstants.SUBJECT_NSENTENCE, ShareConstants.SUBJECT_PREFIX );
        if( dt != null && dt.size() > 0 )
        {
            DataRow row         =   dt.get( 0 );
            subject.setId( row.get( ShareConstants.SUBJECT_ID ) );
            subject.setName( row.get( ShareConstants.SUBJECT_NAME ) );
            subject.setActive(Boolean.valueOf( row.get( ShareConstants.SUBJECT_ACTIVE ) ));
            subject.setNumberSentence(Integer.parseInt(row.get( ShareConstants.SUBJECT_NSENTENCE ) ));
            subject.setPrefix( row.get( ShareConstants.SUBJECT_PREFIX ) );
        }
    }

    @Override
    public void parseData(Object data) {
        Map<String, Object> mData   =   (Map<String, Object>) data;
        
        subject.setId( String.valueOf( mData.get( ShareConstants.SUBJECT_ID ) ) );
        subject.setName( String.valueOf( mData.get( ShareConstants.SUBJECT_NAME ) ));
        subject.setActive( Boolean.valueOf(String.valueOf( mData.get( ShareConstants.SUBJECT_ACTIVE ) )));
        subject.setNumberSentence(Integer.parseInt(String.valueOf( mData.get( ShareConstants.SUBJECT_NSENTENCE ) )));
        subject.setId( String.valueOf( mData.get( ShareConstants.SUBJECT_PREFIX ) ) );
    }

    @Override
    public String toData() {
        Map<String, Object> data    =   new HashMap<>();
        
        data.put( ShareConstants.SUBJECT_ID, subject.getId() );
        data.put( ShareConstants.SUBJECT_NAME, subject.getName());
        data.put( ShareConstants.SUBJECT_ACTIVE, subject.isActive());
        data.put( ShareConstants.SUBJECT_NSENTENCE, subject.getNumberSentence());
        data.put( ShareConstants.SUBJECT_PREFIX, subject.getPrefix());
        
        String dataStr  =   Util.obj2String( data );
        
        return dataStr;
    }
    
    public void getSubject( HttpServletRequest req, HttpServletResponse resp ) throws IOException {
        
        int counter     =   0;
        DataTable dt = MySqlConnection_Rd.getInstance().selectAll( ShareConstants.TABLE_SUBJECT, ShareConstants.SUBJECT_ID, ShareConstants.SUBJECT_NAME, 
                ShareConstants.SUBJECT_ACTIVE, ShareConstants.SUBJECT_NSENTENCE, ShareConstants.SUBJECT_PREFIX );
        
        String dataStr  =   "{ list:[";
        if( dt != null && dt.size() > 0 ) {
            for( int i = 0; i < dt.size(); ++i )
            {
                DataRow dw  =   dt.get(i);
                SubjectModel sm =   new SubjectModel();
                sm.parseData(dw);
                dataStr     =   dataStr + sm.toData();
                counter++;
                
                if( i != dt.size() - 1 )
                {
                    dataStr =   dataStr + ",";
                }
            }
        }
        
        if( counter > 0 )
        {
            dataStr     +=  " ]}";
            try (PrintWriter pw = resp.getWriter()) 
            {
                pw.println( dataStr );
                pw.flush();
            }
        }
    }
}