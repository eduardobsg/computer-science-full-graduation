package lab02e01.cliente;

import java.rmi.Remote;
import java.rmi.RemoteException;
import lab02e01.INews;

/**
 *
 * @author fkrahe
 */
public interface RMINewsClient extends Remote {
    public void feedMe(INews news) throws RemoteException;
}
