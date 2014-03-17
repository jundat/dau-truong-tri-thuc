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
import model.UserModel;

/**
 *
 * @author Mrkupi
 */
public class ProfileController extends ServerServlet {
    
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doProcess(req, resp);
    }

    private void doProcess(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        
        String  reqMethod   =   req.getParameter( "method" );
        UserModel uModel    =   new UserModel();
        if( reqMethod.equals("get") ) {
            uModel.getUserData(req, resp);
        }
        else {
            Boolean result      =   uModel.acceptNewUser(req, resp);
            
            String resultStr    =   String.format("{ \"isSuccess\" : %s }", result );
            try (PrintWriter pw = resp.getWriter()) 
            {
                pw.println( resultStr );
                pw.flush();
            }
        }
    }
}
