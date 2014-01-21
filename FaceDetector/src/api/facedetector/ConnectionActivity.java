package api.facedetector;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;

import org.jwebsocket.api.WebSocketClientEvent;
import org.jwebsocket.api.WebSocketClientListener;
import org.jwebsocket.api.WebSocketClientTokenListener;
import org.jwebsocket.api.WebSocketPacket;
import org.jwebsocket.client.plugins.rpc.Rpc;
import org.jwebsocket.client.plugins.rpc.RpcListener;
import org.jwebsocket.client.plugins.rpc.Rrpc;
import org.jwebsocket.client.token.BaseTokenClient;
import org.jwebsocket.token.Token;

public class ConnectionActivity extends Activity implements WebSocketClientListener {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_connection);
		
		BaseTokenClient tocken_client = new BaseTokenClient();
		tocken_client.addListener(this);
		tocken_client.addListener(new RpcListener());
		
		//set token_client as rpc and rrpc default base token 
		Rpc.setDefaultBaseTokenClient(tocken_client);
		Rrpc.setDefaultBaseTokenClient(tocken_client);
		try{
			System.out.println("try the connection");
			tocken_client.open("ws://192.168.178.3:8787/jWebSocket/jWebSocket");
			
		}catch(Exception e){
			e.printStackTrace();
		}
		
		
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.connection, menu);
		return true;
	}

	@Override
	public void processClosed(WebSocketClientEvent arg0) {
		System.out.println("client deconnecte");
	}

	@Override
	public void processOpened(WebSocketClientEvent arg0) {
		System.out.println("client connecte");
	}

	@Override
	public void processOpening(WebSocketClientEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void processPacket(WebSocketClientEvent arg0, WebSocketPacket arg1) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void processReconnecting(WebSocketClientEvent arg0) {
		// TODO Auto-generated method stub
		
	}

}
