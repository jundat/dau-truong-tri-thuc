/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package webservlet;

import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import model.MultiResultModel;

/**
 *
 * @author Mrkupi
 */
public class MultiScoreController extends webservlet.ServerServlet{
    
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doProcess(req, resp);
    }

    private void doProcess(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String  reqMethod   =   req.getParameter( "method" );
        // Client send score to save db
        MultiResultModel multiModel   =   new MultiResultModel();
        if( reqMethod.equals("set") ) {
            Boolean bResult;
            bResult = multiModel.setScore(req, resp);
            try (PrintWriter pw = resp.getWriter()) 
            {
                String strResult    =   String.format("{ \"isSuccess\" : %s }", bResult );
                pw.println( strResult );
                pw.flush();
            }
        }
        // Client request user single score
        else {
            multiModel.getScore(req, resp);
        }
    }
}
