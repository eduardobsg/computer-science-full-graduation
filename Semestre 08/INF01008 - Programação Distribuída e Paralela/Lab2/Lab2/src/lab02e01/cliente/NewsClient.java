/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package lab02e01.cliente;

import java.io.Serializable;
import java.rmi.Remote;
import java.rmi.RemoteException;
import lab02e01.INews;

/**
 *
 * @author aluno
 */
public class NewsClient implements RMINewsClient, Remote, Serializable {

    public NewsClient() throws RemoteException {
    }

    @Override
    public void feedMe(INews news) {
        news.show();
    }
}
