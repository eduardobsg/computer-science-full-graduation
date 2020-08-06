package lab02e01.servidor;

import java.rmi.AlreadyBoundException;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author fkrahe
 */
public class MainServer {

    public static void main(String[] args) {
        NewsServer newsServer;
        Remote newsServerStub;

        // Obtém o stub através de UnicastRemoteObject.export();
        try {
            newsServer = new NewsServer();
            newsServerStub =
                    UnicastRemoteObject.exportObject(newsServer, 0);

            // cria o RMIREGISTRY e insere a instância no registro
            Registry registry = LocateRegistry.createRegistry(1099);
            registry.bind("NewsServer", newsServerStub);

            System.out.println("Servidor registrado");
        } catch (AlreadyBoundException | RemoteException ex) {
            Logger.getLogger(MainServer.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
