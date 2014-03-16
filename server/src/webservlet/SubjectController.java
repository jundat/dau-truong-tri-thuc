/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package webservlet;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import model.SubjectModel;

/**
 *
 * @author Mrkupi
 */
public class SubjectController extends webservlet.ServerServlet{
    
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doProcess(req, resp);
    }

    private void doProcess(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String  reqMethod   =   req.getParameter( "method" );
        
        SubjectModel sm     =   new SubjectModel();
        if( reqMethod.equals("get") ) {
            sm.getSubject(req, resp);
        }
    }
}
