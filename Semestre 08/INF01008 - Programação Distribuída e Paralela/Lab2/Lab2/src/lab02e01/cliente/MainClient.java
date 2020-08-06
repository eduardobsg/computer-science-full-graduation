package lab02e01.cliente;

import java.rmi.AlreadyBoundException;
import java.rmi.NotBoundException;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import lab02e01.servidor.RMINewsServer;

/**
 *
 * @author fkrahe
 */
public class MainClient {

    public static void main(String[] args) {
        try {
            // Obtém o registro
            Registry registry = LocateRegistry.getRegistry(1099);

            // 1- Pesquisa o serviço
            // 2- Faz cast para a interface remota
            RMINewsServer newsServer = (RMINewsServer) registry.lookup("NewsServer");//Naming.lookup("rmi://127.0.0.1/NewsServer");


            // Instancia e registra clientes
            for (int i = 0; i < 5; i++) {
                // Instancia o cliente e registra
                Remote clientStub = UnicastRemoteObject.exportObject(new NewsClient(), 0);
                registry.bind("Client" + i, clientStub);

                // Informa o endereço do cliente ao servidor e publica uma News
                newsServer.registerClient("Client" + i);
                newsServer.addNews("Cliente [" + i + "] adicionado!");
            }


        } catch (NotBoundException | RemoteException | AlreadyBoundException e) {
            System.err.println("Client exception: " + e.toString());
            e.printStackTrace();
        }
    }
}
