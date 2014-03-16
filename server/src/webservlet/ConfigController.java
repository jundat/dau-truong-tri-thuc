/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package webservlet;

import config.ConfigServerModel;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author Mrkupi
 */
public class ConfigController extends ServerServlet {

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doProcess(req, resp);
    }

    private void doProcess(HttpServletRequest req, HttpServletResponse resp) throws IOException{
        
        ConfigServerModel.getInst().getConfig(req, resp);
        System.out.print(req.getRequestURI() + " Get config data");
    }
}
