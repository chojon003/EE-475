package com.example.drinkingbuddyapplication;

import static android.preference.PreferenceManager.getDefaultSharedPreferences;

import android.app.Dialog;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGattCharacteristic;
import android.content.Context;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Toast;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.navigation.ui.AppBarConfiguration;
import androidx.navigation.ui.NavigationUI;

import com.clj.fastble.BleManager;
import com.clj.fastble.data.BleDevice;
import com.example.drinkingbuddyapplication.dashboard.DashboardFragment;
import com.example.drinkingbuddyapplication.databinding.ActivityMainBinding;
import com.google.android.material.bottomnavigation.BottomNavigationView;

import java.util.Calendar;

public class MainActivity extends AppCompatActivity implements BluetoothLeUart.Callback{

    private ActivityMainBinding binding;
    private AlertDialog.Builder dialogBuilder;

    final private int REQUEST_CODE_PERMISSION_LOCATION = 0;

    // Bluetooth LE UART instance.  This is defined in BluetoothLeUart.java.
    private BluetoothLeUart uart;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Initialize UART.
        uart = new BluetoothLeUart(getApplicationContext());

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        BottomNavigationView navView = findViewById(R.id.nav_view);
        // Passing each menu ID as a set of Ids because each
        // menu should be considered as top level destinations.
        AppBarConfiguration appBarConfiguration = new AppBarConfiguration.Builder(
                R.id.navigation_home, R.id.navigation_dashboard, R.id.navigation_notifications, R.id.navigation_profile)
                .build();
        NavController navController = Navigation.findNavController(this, R.id.nav_host_fragment_activity_main);
        NavigationUI.setupActionBarWithNavController(this, navController, appBarConfiguration);
        NavigationUI.setupWithNavController(binding.navView, navController);
    }

    public void onSend() {
        uart.send("1");
    }

    // OnResume, called right before UI is displayed.  Connect to the bluetooth device.
    @Override
    protected void onResume() {
        super.onResume();
        // instantiate saved variables
        SharedPreferences pref = this.getPreferences(Context.MODE_PRIVATE);

        // check if first time opening app
        if (pref.getBoolean("my_first_time", true)) {
            //the app is being launched for first time, do something
            // initial dialogs
            AlertDialog.Builder builder = new AlertDialog.Builder(this, R.style.MyDialogTheme);

            builder.setTitle("First Time Setup");
            builder.setIcon(R.drawable.ic_launcher_foreground);
            builder.setMessage("Make sure water bottle only contains water, and is attached securely.");
            builder.setCancelable(false);
            builder.setPositiveButton("Complete", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialogInterface, int i) {
                    onSend();
                }
            });

            builder.create();

            // record the fact that the app has been started at least once
            pref.edit().putBoolean("my_first_time", true).commit();
        }
        uart.registerCallback(this);
        uart.connectFirstAvailable();

        // determine if it is new day, if it is shift data down by one
        SharedPreferences settings = getDefaultSharedPreferences(this);
        int lastTimeStarted = settings.getInt("last_time_started", -1);
        Calendar calendar = Calendar.getInstance();
        int today = calendar.get(Calendar.DAY_OF_YEAR);
        DashboardFragment frag = (DashboardFragment) getSupportFragmentManager().findFragmentById(R.id.dashboard);

        if (today != lastTimeStarted && frag != null) {
            frag.shiftData();

            SharedPreferences.Editor editor = settings.edit();
            editor.putInt("last_time_started", today);
            editor.commit();
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        BleManager.getInstance().disconnectAllDevice();
        BleManager.getInstance().destroy();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.bottom_nav_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.navigation_profile) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    // UART Callback event handlers.

    @Override
    public void onConnected(BluetoothLeUart uart) {
        // Called when UART device is connected and ready to send/receive data.
        this.runOnUiThread(new Runnable() {
            public void run() {
                Toast.makeText(getApplicationContext(), "Connected to DrinkingBuddy!.", Toast.LENGTH_LONG).show();
            }
        });
    }

    @Override
    public void onConnectFailed(BluetoothLeUart uart) {
        // Called when some error occured which prevented UART connection from completing.
        this.runOnUiThread(new Runnable() {
            public void run() {
                Toast.makeText(getApplicationContext(), "Error connecting to DrinkingBuddy!", Toast.LENGTH_LONG).show();
            }
        });
    }

    @Override
    public void onDisconnected(BluetoothLeUart uart) {
        // Called when the UART device disconnected.
        this.runOnUiThread(new Runnable() {
            public void run() {
                Toast.makeText(getApplicationContext(), "Uh oh! DrinkingBuddy Disconnected...", Toast.LENGTH_LONG).show();
            }
        });
    }

    @Override
    public void onReceive(BluetoothLeUart uart, BluetoothGattCharacteristic rx) {
        // Called when data is received by the UART.

        // data comes in string format with 3 numbers seperated by a space
        // Example: "1234 0 75" ("measWeight isWater batteryPct")
        String data = rx.getStringValue(0);

        String[] delimitedData = data.split(" ");

        SharedPreferences pref = this.getPreferences(Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = pref.edit();

        int prevMeasWeight = pref.getInt("prevMeasWeight", 0);
        int measWeight = Integer.parseInt(delimitedData[0]);

        // if water was consumed
        if (prevMeasWeight > measWeight) {
            int amountDrankSinceLastReading = prevMeasWeight - measWeight;
            int totalAmountWaterDrank = pref.getInt("totalAmountWaterDrank", 0);
            int updatedAmountWater = amountDrankSinceLastReading + totalAmountWaterDrank;
            editor.putInt("totalAmountWaterDrank", updatedAmountWater);
        }
        editor.putInt("prevMeasWeight", measWeight);
        editor.putInt("isWater", Integer.parseInt(delimitedData[1]));
        editor.putInt("batteryPct", Integer.parseInt(delimitedData[2]));
        editor.apply();
    }

    @Override
    public void onDeviceFound(BluetoothDevice device) {
//        // Called when a UART device is discovered (after calling startScan).
    }

    @Override
    public void onDeviceInfoAvailable() {
//        uart.getDeviceInfo();
    }
}
