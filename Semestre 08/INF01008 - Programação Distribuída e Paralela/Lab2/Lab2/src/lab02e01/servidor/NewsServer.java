package lab02e01.servidor;

import java.rmi.AccessException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.logging.Level;
import java.util.logging.Logger;
import lab02e01.News;
import lab02e01.cliente.RMINewsClient;

/**
 * IMPLEMENTAÇÃO REMOTA
 *
 * 1) Implementa a interface remota
 *
 * @author fkrahe
 */
public class NewsServer implements RMINewsServer {

    private static Registry registry;
    private static ArrayList<RMINewsClient> clients;

    public NewsServer() throws RemoteException {
        registry = LocateRegistry.getRegistry(1099);
        clients = new ArrayList<>();
    }

    @Override
    public void registerClient(String feedURI) throws RemoteException {
        try {
            //conecta ao cliente
            RMINewsClient clientStub = (RMINewsClient) registry.lookup(feedURI);
            //adiciona objeto remoto na lista de clientes
            clients.add(clientStub);
        } catch (NotBoundException | AccessException ex) {
            Logger.getLogger(NewsServer.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    @Override
    public void addNews(String news) throws RemoteException {
        News n = new News(new Date(), news);
        for (Iterator<RMINewsClient> it = clients.iterator(); it.hasNext();) {
            RMINewsClient client = it.next();
            client.feedMe(n);
            break;
        }
    }
}
