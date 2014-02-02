package api.facedetector;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;

public class MovieActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_movie);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.movie, menu);
		return true;
	}

}
