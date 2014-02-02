package api.facedetector;

import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Build;
import android.os.Bundle;
import android.annotation.TargetApi;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.TaskStackBuilder;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.support.v4.app.NotificationCompat;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainFaceDetector extends Activity {
	 private NotificationManager notificationManager;
	 private int notificationID = 100;
	 private int numMessages = 0;
	 private View connectDialog;
	 LayoutInflater layout;
	 AlertDialog.Builder adb;
	 EditText urlEdit;
	 WebSocketClient client;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main_face_detector);
        
        // WebSocket
        WebSocketClient client = new WebSocketClient();
        client.execute("");
        layout = LayoutInflater.from(this);
        connectDialog = layout.inflate(R.layout.connectdialog, null);
        adb = new AlertDialog.Builder(this);
        adb.setView(connectDialog);
        adb.setTitle("Connection to the server.");
        adb.setIcon(android.R.drawable.ic_dialog_alert);
        adb.setPositiveButton("OK", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int which) {
 
            	//Lorsque l'on cliquera sur le bouton "OK", on récupère l'EditText correspondant à notre vue personnalisée (cad à alertDialogView)
            	urlEdit = (EditText)connectDialog.findViewById(R.id.EditText1);
 
            	//On affiche dans un Toast le texte contenu dans l'EditText de notre AlertDialog
            	Toast.makeText(MainFaceDetector.this, urlEdit.getText(), Toast.LENGTH_SHORT).show();
          } });
 
        //On crée un bouton "Annuler" à notre AlertDialog et on lui affecte un évènement
        adb.setNegativeButton("Annuler", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int which) {
            	
          } });
        
        
        
        
        //bouton pour creer la notif
        Button start = (Button) findViewById(R.id.start);
        start.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				displayNotification();
			}
		});
        
        //bouton pour supprimer la notif
        Button cancel = (Button) findViewById(R.id.cancel);
        cancel.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				cancelNotification();
			}
		});
        
        
        //bouton pour supprimer la notif
        Button socketLaunch = (Button) findViewById(R.id.socketLaunch);
        socketLaunch.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				openSocket();
			}
		});
    }

    @TargetApi(Build.VERSION_CODES.JELLY_BEAN) protected void displayNotification()
    {
    	Log.i("start", "start notification");
    	NotificationCompat.Builder notifBuilder = 
    			new NotificationCompat.Builder(this)
    			.setContentTitle("notification d'une nouvelle video")
    			.setContentText("Vous avez reçu une nouvelle video")
    			.setTicker("nouvelle video enregistrée")
    			.setSmallIcon(R.drawable.ic_launcher); //icon a changer apres
    	
    	//augmente le nombre de notif a chaque fois qu'on recoit une nouvelle video
    	notifBuilder.setNumber(++numMessages);
    	
    	//create intent for the movie ativity
    		
		Intent movieActivityIntent = new Intent(this, NotificationView.class);
    	
		TaskStackBuilder stacktBuilder = TaskStackBuilder.create(this);
    	stacktBuilder.addParentStack(NotificationView.class);
   
    	stacktBuilder.addNextIntent(movieActivityIntent);
    	PendingIntent 	resulPendingIntent = stacktBuilder
    			.getPendingIntent(0, PendingIntent.FLAG_UPDATE_CURRENT);
    	
    	notifBuilder.setContentIntent(resulPendingIntent);
    	
    	notificationManager = 
    		(NotificationManager) getSystemService(
    				Context.NOTIFICATION_SERVICE);
    	notificationManager.notify(notificationID, notifBuilder.build());
    		
    }

    protected void cancelNotification() {
        Log.i("Cancel", "notification");
        notificationManager.cancel(notificationID);
    }
    
    protected void openSocket() {
    	adb.show();
    	//Intent connectionActivity = new Intent(this, ConnectionActivity.class);
    	//this.setIntent(connectionActivity);
    }
    
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main_face_detector, menu);
        return true;
    }
}
