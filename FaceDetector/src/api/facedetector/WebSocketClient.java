package api.facedetector;

import org.jwebsocket.api.WebSocketClientEvent;
import org.jwebsocket.api.WebSocketClientTokenListener;
import org.jwebsocket.api.WebSocketPacket;
import org.jwebsocket.client.plugins.rpc.Rpc;
import org.jwebsocket.client.plugins.rpc.RpcListener;
import org.jwebsocket.client.plugins.rpc.Rrpc;
import org.jwebsocket.client.token.BaseTokenClient;
import org.jwebsocket.token.Token;

import android.os.AsyncTask;

public class WebSocketClient extends AsyncTask<String, Integer, Long> implements WebSocketClientTokenListener{

	private BaseTokenClient btc;
	
	
	public WebSocketClient() {
		System.out.println("Creating a new websocket client");
		btc = new BaseTokenClient();
		btc.addListener(this);
		btc.addListener(new RpcListener());
		Rpc.setDefaultBaseTokenClient(btc);
		Rrpc.setDefaultBaseTokenClient(btc);
	}
	
	public void startConnection(String url)
	{
		
	}
	
	@Override
	public void processClosed(WebSocketClientEvent arg0) {
		System.out.println("Connection closed : " + arg0.getData());
		
	}

	@Override
	public void processOpened(WebSocketClientEvent arg0) {
		System.out.println("Connection success !");
		
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

	@Override
	public void processToken(WebSocketClientEvent arg0, Token arg1) {
		// TODO Auto-generated method stub
		
	}

	@Override
	protected Long doInBackground(String... params) {
		try
		{
			String url;
			url = "ws://192.168.0.16:8082";
			System.out.println("Connection requested for url : " + url);
			if (!btc.isConnected())
			{
				btc.close();
				btc.open(url);
			}
		}catch(Exception e)
		{
			System.out.println("Exception : CONNECTION FAILED");
			e.printStackTrace();
		}
		System.out.println("attempt succeed");
		return 0L;
	}


}
