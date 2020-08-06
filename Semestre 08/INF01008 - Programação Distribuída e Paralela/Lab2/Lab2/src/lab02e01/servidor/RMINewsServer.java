package lab02e01.servidor;

import java.rmi.Remote;
import java.rmi.RemoteException;

/**
 * INTERFACE REMOTA
 *
 * 1) Extende java.rmi.Remote
 *
 * 2) Todos métodos lançam java.rmi.RemoteException
 *
 * 3) Tipos de retorno primitivos ou serializáveis
 *
 * @author fkrahe
 */
public interface RMINewsServer extends Remote {

    public void registerClient(String feedURI) throws RemoteException;

    public void addNews(String news) throws RemoteException;
}
