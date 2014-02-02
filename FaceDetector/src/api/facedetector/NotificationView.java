package api.facedetector;

import java.io.File;
import java.text.SimpleDateFormat;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.annotation.SuppressLint;
import android.annotation.TargetApi;
import android.app.Activity;
import android.content.Intent;
import android.support.v4.app.NavUtils;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;

@TargetApi(Build.VERSION_CODES.HONEYCOMB)
public class NotificationView extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_notification_view);
		
		// Make sure we're running on Honeycomb or higher to use ActionBar APIs
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
            // Show the Up button in the action bar.
            getActionBar().setDisplayHomeAsUpEnabled(true);
        }

	}
	
	//focntion to go back to the parent activity or home
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
        case android.R.id.home:
            NavUtils.navigateUpFromSameTask(this);
            return true;
        case R.id.save_movie:
	        save_movie();
	        return true;
        case R.id.delete_movie:
            delete_movie();
            return true;
        case R.id.call_police:
        	call_police();
            return true;
        case R.id.send_message:
        	send_texto();
        return true;
        default:
            return super.onContextItemSelected(item);
        }
        //return super.onOptionsItemSelected(item);
    }
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.movie, menu);
        return true;
    }
    
  	public void save_movie()
  	{
  		Intent intent = new Intent(MediaStore.ACTION_VIDEO_CAPTURE); 	
        Uri fileUri = getOutputMediaFileUri(2);
         
        // set the image file name 
        intent.putExtra(MediaStore.EXTRA_OUTPUT, fileUri); 
         
        // set the video image quality to high
        intent.putExtra(MediaStore.EXTRA_VIDEO_QUALITY, 1);

        // start the Video Capture Intent
        startActivityForResult(intent, 200);
  		
  	}
  	
    /** Create a file Uri for saving an image or video */
    private static Uri getOutputMediaFileUri(int type){
         
          return Uri.fromFile(getOutputMediaFile(type));
    }
    
    /** Create a File for saving an image or video */
    @SuppressLint("SimpleDateFormat")
	private static File getOutputMediaFile(int type){
         
        // Check that the SDCard is mounted
        File mediaStorageDir = new File(Environment
        		.getExternalStoragePublicDirectory(
                  Environment.DIRECTORY_PICTURES), "FaceDetector");
        // Create the storage directory(MyCameraVideo) if it does not exist
        if (! mediaStorageDir.exists()){
             
            if (!mediaStorageDir.mkdirs()){  
                //output.setText("Failed to create directory MyCameraVideo.");
                return null;
            }
        }     
        // Create a media file name
         
        // For unique file name appending current timeStamp with file name
        java.util.Date date= new java.util.Date();
        String timeStamp = new SimpleDateFormat("yyyyMMdd_HHmmss")
                             .format(date.getTime());
        File mediaFile;
         
        if(type == 2) {             
            // For unique video file name appending current timeStamp with file name
            mediaFile = new File(mediaStorageDir.getPath() + File.separator +
            "VID_"+ timeStamp + ".mp4");
             
        } else {
            return null;
        }
 
        return mediaFile;
    }
     
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == 200) {
             
            if (resultCode == RESULT_OK) {
                // Video captured and saved to fileUri specified in the Intent
                Toast.makeText(this, "Video saved to:" +
                         data.getData(), Toast.LENGTH_LONG).show();
                 
            } else if (resultCode == RESULT_CANCELED) {
                // User cancelled the video capture
                Toast.makeText(this, "User cancelled the video capture.",
                        Toast.LENGTH_LONG).show();
                 
            } else {
                // Video capture failed, advise user
                Toast.makeText(this, "Video capture failed.",
                        Toast.LENGTH_LONG).show();
            }
        }
    }
     
    
  	public void delete_movie()
  	{
  		
  	}
  	
  	//call the police by default. But can call other personnes
  	public void call_police()
  	{
  		Uri number = Uri.parse("tel:17");
  		Intent callIntent = new Intent(Intent.ACTION_DIAL, number);
  		startActivity(callIntent);
  	}
  	
  	//send movie by email or message or somthing else in the menu
  	public void send_texto()
  	{
  		Intent sendIntent = new Intent();
  		sendIntent.setAction(Intent.ACTION_SEND);
  		
  		//faut envoyer la video apres en parametre grace a ca.
  		//sendIntent.putExtra(Intent.EXTRA_TEXT, "This is my text to send.");
  		
  		sendIntent.setType("text/plain");
  		startActivity(sendIntent);
  	}



}
