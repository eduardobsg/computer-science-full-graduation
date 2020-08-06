package br.com.ufrgs.pdp.localization;

import android.location.Criteria;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.app.Activity;
import android.content.Context;
import android.util.Log;
import android.view.Menu;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity implements LocationListener {

	private static final String TAG = " MainActivity ";
	private TextView txtLatitude;
	private TextView txtLongitude;
	private TextView txtAltitude;
	private LocationManager locationManager;
	private String provider;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		txtLatitude = (TextView) findViewById(R.id.txtLatitude);
		txtLongitude = (TextView) findViewById(R.id.txtLongitude);
		txtAltitude = (TextView) findViewById(R.id.txtAltitude);

		locationManager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);
		
		Criteria criteria = new Criteria();
		provider = locationManager.getBestProvider(criteria, false);

		Location location = locationManager.getLastKnownLocation(provider);

		if (location != null) {
			Log.d(TAG, " Provider " + provider + " foi selecionado.");
			Log.d(TAG, "Longitude: "+location.getLongitude()
					+" Latitude: "+location.getLatitude()
					+" Altitude: "+location.getAltitude());
			onLocationChanged(location);
		} else {
			txtLatitude.setText(R.string.location_not_available);
			txtLongitude.setText(R.string.location_not_available);
			txtAltitude.setText(R.string.location_not_available);
		}
	}

	@Override
	protected void onResume() {
		super.onResume();
		locationManager.requestLocationUpdates(provider,400,1,this);
	}
	
	@Override
	protected void onPause() {
		super.onPause();
	 	locationManager.removeUpdates(this);
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public void onLocationChanged(Location location) {
		double lat = location.getLatitude();
		double lng = location.getLongitude();
		txtLatitude.setText(String.valueOf(lat));
		txtLongitude.setText(String.valueOf(lng));
		txtAltitude.setText(String.valueOf(location.getAltitude()));
	}

	@Override
	public void onProviderDisabled(String provider) {
		Toast.makeText(this," Provider desabilitado " + provider,Toast.LENGTH_SHORT).show();
	}

	@Override
	public void onProviderEnabled(String provider) {
		Toast.makeText(this," Novo provider " + provider,Toast.LENGTH_SHORT).show();
	}

	@Override
	public void onStatusChanged(String provider , int status , Bundle extras) {
		// TODO Auto-generated method stub

	}

}
