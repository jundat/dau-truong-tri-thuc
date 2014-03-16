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
import model.MultiReportModel;

/**
 *
 * @author Mrkupi
 */
public class MultiReportController extends webservlet.ServerServlet{
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doProcess(req, resp);
    }

    private void doProcess(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        MultiReportModel single    =   MultiReportModel.getInstance();
        String dataStr              =   single.toData();
        try (PrintWriter pw = resp.getWriter()) 
        {
            pw.println( dataStr );
            pw.flush();
        }
    }
}
