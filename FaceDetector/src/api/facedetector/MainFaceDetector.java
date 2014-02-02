package api.facedetector;

import android.os.Build;
import android.os.Bundle;
import android.annotation.TargetApi;
import android.app.Activity;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.TaskStackBuilder;
import android.content.Context;
import android.content.Intent;
import android.support.v4.app.NotificationCompat;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Button;

public class MainFaceDetector extends Activity {
	 private NotificationManager notificationManager;
	 private int notificationID = 100;
	 private int numMessages = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main_face_detector);
        
        //bouton pour creer la notification
        Button start = (Button) findViewById(R.id.start);
        start.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				displayNotification();
			}
		});
        
        //bouton pour supprimer la notification
        Button cancel = (Button) findViewById(R.id.cancel);
        cancel.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				cancelNotification();
			}
		});
        
        
        //bouton pour lancer la connection entre le l'appli et l'appli pc
        Button socketLaunch = (Button) findViewById(R.id.socketLaunch);
        socketLaunch.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				openSocket();
			}
		});
       
        //juste pour tester l'affichage d'une image
        Button openMovie = (Button) findViewById(R.id.openMovie);
        start.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				OpenMovie();
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
    	Intent connectionActivity = new Intent(this, ConnectionActivity.class);
    	this.setIntent(connectionActivity);
    }
    
    
    protected void OpenMovie() {
    	Intent MovieActivity = new Intent(this, MovieActivity.class);
    	this.setIntent(MovieActivity);
    }
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main_face_detector, menu);
        return true;
    }
    
}
